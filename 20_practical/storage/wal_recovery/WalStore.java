import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.zip.CRC32;

/**
 * Transactional key-value store made durable by a write-ahead log.
 *
 * Every change is appended to the log before it takes effect, and a commit is
 * durable once its COMMIT record is in the log. The in-memory table is lost
 * in a crash; recovery rebuilds it from the last checkpoint plus the log,
 * replaying only transactions whose COMMIT record made it to the log.
 * Uncommitted changes are never applied to the table (no-steal), so recovery
 * needs only redo, no undo.
 *
 * Disk is the state that survives a crash: a checkpoint snapshot and the log
 * lines. Each log line carries a CRC32 of its content, so a record torn by a
 * crash in the middle of a write is detected and cut off.
 */
public class WalStore {

    /** What survives a crash. */
    public static final class Disk {
        final Map<String, String> checkpoint = new HashMap<>();
        long checkpointNextTxId = 1;
        final List<String> log = new ArrayList<>();
    }

    private enum Type { BEGIN, SET, DEL, COMMIT, ABORT }

    private record Record(Type type, long txId, String key, String value) {
        String encode() {
            String body = String.join("\t", type.name(), Long.toString(txId), key == null ? "" : key, value == null ? "" : value);
            return crc(body) + "\t" + body;
        }

        /** Returns null for a torn or corrupt line. */
        static Record decode(String line) {
            int tab = line.indexOf('\t');
            if (tab < 0) return null;
            String body = line.substring(tab + 1);
            if (!line.substring(0, tab).equals(crc(body))) return null;
            String[] f = body.split("\t", -1);
            if (f.length != 4) return null;
            return new Record(Type.valueOf(f[0]), Long.parseLong(f[1]), f[2].isEmpty() ? null : f[2], f[3].isEmpty() ? null : f[3]);
        }

        static String crc(String s) {
            CRC32 c = new CRC32();
            c.update(s.getBytes(StandardCharsets.UTF_8));
            return Long.toHexString(c.getValue());
        }
    }

    private final Disk disk;
    private final Map<String, String> table = new HashMap<>();
    private final Map<Long, Map<String, String>> pending = new HashMap<>(); // txId -> buffered writes, null = delete
    private long nextTxId;

    /** Opens the store on a disk, running recovery. */
    public WalStore(Disk disk) {
        this.disk = disk;
        recover();
    }

    public long begin() {
        long tx = nextTxId++;
        append(new Record(Type.BEGIN, tx, null, null));
        pending.put(tx, new LinkedHashMap<>());
        return tx;
    }

    public void set(long tx, String key, String value) {
        validate(key);
        validate(Objects.requireNonNull(value, "value"));
        writes(tx).put(key, value);
        append(new Record(Type.SET, tx, key, value));
    }

    public void delete(long tx, String key) {
        validate(key);
        writes(tx).put(key, null);
        append(new Record(Type.DEL, tx, key, null));
    }

    /** The transaction's own write if any, otherwise the committed value. */
    public String get(long tx, String key) {
        Map<String, String> w = writes(tx);
        return w.containsKey(key) ? w.get(key) : table.get(key);
    }

    public void commit(long tx) {
        Map<String, String> w = writes(tx);
        append(new Record(Type.COMMIT, tx, null, null)); // durable from here
        apply(w);
        pending.remove(tx);
    }

    public void abort(long tx) {
        writes(tx);
        append(new Record(Type.ABORT, tx, null, null));
        pending.remove(tx);
    }

    /** Committed value, outside any transaction. */
    public String read(String key) {
        return table.get(key);
    }

    /**
     * Saves the committed table as the new checkpoint and shortens the log to
     * the records of transactions still open, which recovery still needs.
     */
    public void checkpoint() {
        disk.checkpoint.clear();
        disk.checkpoint.putAll(table);
        disk.checkpointNextTxId = nextTxId;
        List<String> keep = new ArrayList<>();
        for (String line : disk.log) {
            Record r = Record.decode(line);
            if (pending.containsKey(r.txId())) keep.add(line);
        }
        disk.log.clear();
        disk.log.addAll(keep);
    }

    private void recover() {
        table.putAll(disk.checkpoint);
        nextTxId = disk.checkpointNextTxId;
        Map<Long, Map<String, String>> open = new HashMap<>();
        int valid = 0;
        for (String line : disk.log) {
            Record r = Record.decode(line);
            if (r == null) break; // torn write: nothing after it can be trusted
            valid++;
            nextTxId = Math.max(nextTxId, r.txId() + 1); // never reuse an id that appears in the log
            switch (r.type()) {
                case BEGIN -> open.put(r.txId(), new LinkedHashMap<>());
                case SET, DEL -> open.get(r.txId()).put(r.key(), r.value());
                case COMMIT -> apply(open.remove(r.txId()));
                case ABORT -> open.remove(r.txId());
            }
        }
        disk.log.subList(valid, disk.log.size()).clear(); // drop the torn tail before appending again
        // transactions still open were cut off by the crash: their records stay
        // in the log but they never commit, so they are ignored by every recovery
    }

    private void apply(Map<String, String> writes) {
        writes.forEach((k, v) -> {
            if (v == null) table.remove(k);
            else table.put(k, v);
        });
    }

    private void append(Record r) {
        disk.log.add(r.encode());
    }

    private Map<String, String> writes(long tx) {
        Map<String, String> w = pending.get(tx);
        if (w == null) throw new IllegalStateException("transaction not open: " + tx);
        return w;
    }

    private static void validate(String s) {
        if (s.isEmpty() || s.contains("\t") || s.contains("\n"))
            throw new IllegalArgumentException("keys and values must be non-empty, without tabs or newlines");
    }

    // ---- checks -------------------------------------------------------------

    public static void main(String[] args) {
        stage1();
        stage2();
        stage3();
        stage4();
        System.out.println("all checks passed");
    }

    static void stage1() {
        Disk disk = new Disk();
        WalStore db = new WalStore(disk);
        long t = db.begin();
        db.set(t, "x", "1");
        eq(db.get(t, "x"), "1", "own write");
        eq(db.read("x"), null, "invisible before commit");
        eq(disk.log.size(), 2, "BEGIN and SET logged before commit");
        db.commit(t);
        eq(db.read("x"), "1", "visible after commit");
        long u = db.begin();
        db.delete(u, "x");
        db.abort(u);
        eq(db.read("x"), "1", "aborted delete has no effect");
        throwsEx(IllegalStateException.class, () -> db.set(u, "y", "2"), "use after abort");
    }

    static void stage2() {
        Disk disk = new Disk();
        WalStore db = new WalStore(disk);
        long a = db.begin();
        db.set(a, "x", "1");
        db.set(a, "y", "2");
        db.commit(a);
        long b = db.begin();
        db.set(b, "x", "100");
        db.abort(b);
        long c = db.begin();
        db.delete(c, "y");
        db.commit(c);
        long d = db.begin();
        db.set(d, "x", "999"); // never committed: lost in the crash

        WalStore after = new WalStore(disk); // crash: only the disk survives
        eq(after.read("x"), "1", "committed value recovered, aborted and unfinished ignored");
        eq(after.read("y"), null, "committed delete recovered");
        long e = after.begin();
        if (e <= d) throw new AssertionError("transaction id reused after recovery: " + e);
        after.set(e, "z", "3");
        after.commit(e);
        eq(new WalStore(disk).read("x"), "1", "old unfinished transaction still ignored after another crash");
        eq(new WalStore(disk).read("z"), "3", "new commit recovered");
    }

    static void stage3() {
        Disk disk = new Disk();
        WalStore db = new WalStore(disk);
        for (int i = 0; i < 100; i++) {
            long t = db.begin();
            db.set(t, "k", "v" + i);
            db.commit(t);
        }
        long open = db.begin();
        db.set(open, "k", "uncommitted");
        db.checkpoint();
        eq(disk.log.size(), 2, "log shortened to the open transaction's records");
        db.commit(open); // its COMMIT goes after the checkpoint
        WalStore after = new WalStore(disk);
        eq(after.read("k"), "uncommitted", "transaction open at the checkpoint, committed later");

        Disk disk2 = new Disk();
        WalStore db2 = new WalStore(disk2);
        long t = db2.begin();
        db2.set(t, "a", "1");
        db2.commit(t);
        db2.checkpoint();
        eq(disk2.log.size(), 0, "nothing open: empty log");
        eq(new WalStore(disk2).read("a"), "1", "state comes from the checkpoint alone");
        if (new WalStore(disk2).begin() <= t) throw new AssertionError("id reused after checkpoint");
    }

    static void stage4() {
        Disk disk = new Disk();
        WalStore db = new WalStore(disk);
        long a = db.begin();
        db.set(a, "x", "1");
        db.commit(a);
        long b = db.begin();
        db.set(b, "x", "2");
        db.commit(b);
        String last = disk.log.remove(disk.log.size() - 1); // b's COMMIT, torn mid-write
        disk.log.add(last.substring(0, last.length() / 2));
        WalStore after = new WalStore(disk);
        eq(after.read("x"), "1", "commit with a torn record is not durable");
        eq(disk.log.size(), 5, "torn record cut from the log");
        long c = after.begin();
        after.set(c, "y", "3");
        after.commit(c);
        WalStore again = new WalStore(disk);
        eq(again.read("y"), "3", "records after the cut are readable");
        eq(again.read("x"), "1", "b stays uncommitted");

        Disk disk2 = new Disk();
        WalStore db2 = new WalStore(disk2);
        long t = db2.begin();
        db2.set(t, "x", "1");
        db2.commit(t);
        disk2.log.set(1, disk2.log.get(1).replace("\t1", "\t7")); // corrupt the SET's value
        eq(new WalStore(disk2).read("x"), null, "corrupt record detected by its checksum");
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }

    static void throwsEx(Class<? extends Exception> type, Runnable r, String what) {
        try {
            r.run();
        } catch (Exception e) {
            if (type.isInstance(e)) return;
            throw new AssertionError(what + ": expected " + type.getSimpleName() + ", got " + e);
        }
        throw new AssertionError(what + ": expected " + type.getSimpleName());
    }
}
