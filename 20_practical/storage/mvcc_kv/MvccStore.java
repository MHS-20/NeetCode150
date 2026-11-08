import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

/**
 * Key-value store with multi-version concurrency control and snapshot isolation.
 *
 * Each key keeps a list of versions, oldest first, each stamped with the
 * commit timestamp that created it; a deletion is a version whose value is
 * null (a tombstone). A transaction reads the snapshot taken at begin(): for
 * each key, the newest version committed at or before that timestamp. Its
 * own writes are buffered and become new versions at commit. Two transactions
 * that write the same key conflict, and the one that commits second fails
 * (first committer wins), so an update is never silently lost.
 */
public class MvccStore {

    private record Version(long commitTs, String value) {}

    public static class ConflictException extends RuntimeException {
        ConflictException(String key) {
            super("write-write conflict on " + key);
        }
    }

    private final Map<String, List<Version>> versions = new HashMap<>();
    private final Set<Tx> active = new HashSet<>();
    private long lastCommitTs = 0;

    public Tx begin() {
        Tx tx = new Tx(lastCommitTs);
        active.add(tx);
        return tx;
    }

    public final class Tx {
        private final long snapshotTs;
        private final Map<String, String> writes = new HashMap<>(); // null value = delete
        private boolean open = true;

        private Tx(long snapshotTs) {
            this.snapshotTs = snapshotTs;
        }

        public String get(String key) {
            ensureOpen();
            if (writes.containsKey(key)) return writes.get(key);
            return visible(key, snapshotTs);
        }

        public void put(String key, String value) {
            ensureOpen();
            writes.put(key, Objects.requireNonNull(value, "value"));
        }

        public void delete(String key) {
            ensureOpen();
            writes.put(key, null);
        }

        /** Publishes the writes, or aborts and throws if another transaction committed one of the keys first. */
        public void commit() {
            ensureOpen();
            close();
            for (String key : writes.keySet()) {
                List<Version> vs = versions.get(key);
                if (vs != null && vs.get(vs.size() - 1).commitTs() > snapshotTs) throw new ConflictException(key);
            }
            if (writes.isEmpty()) return;
            long ts = ++lastCommitTs;
            writes.forEach((key, value) -> versions.computeIfAbsent(key, k -> new ArrayList<>()).add(new Version(ts, value)));
        }

        public void rollback() {
            ensureOpen();
            close();
        }

        private void close() {
            open = false;
            active.remove(this);
        }

        private void ensureOpen() {
            if (!open) throw new IllegalStateException("transaction is closed");
        }
    }

    /** Value of the newest version with commitTs <= ts, or null. */
    private String visible(String key, long ts) {
        List<Version> vs = versions.get(key);
        if (vs == null) return null;
        for (int i = vs.size() - 1; i >= 0; i--)
            if (vs.get(i).commitTs() <= ts) return vs.get(i).value();
        return null;
    }

    /**
     * Drops versions that no open or future transaction can read: for each key,
     * every version older than the newest one visible to the oldest snapshot.
     * Returns the number of versions removed.
     */
    public int garbageCollect() {
        long horizon = active.stream().mapToLong(tx -> tx.snapshotTs).min().orElse(lastCommitTs);
        int removed = 0;
        var it = versions.entrySet().iterator();
        while (it.hasNext()) {
            List<Version> vs = it.next().getValue();
            int keepFrom = 0;
            for (int i = 0; i < vs.size(); i++) if (vs.get(i).commitTs() <= horizon) keepFrom = i;
            removed += keepFrom;
            vs.subList(0, keepFrom).clear();
            if (vs.size() == 1 && vs.get(0).value() == null && vs.get(0).commitTs() <= horizon) {
                it.remove(); // a tombstone that every snapshot sees: the key is simply gone
                removed++;
            }
        }
        return removed;
    }

    int versionCount(String key) {
        List<Version> vs = versions.get(key);
        return vs == null ? 0 : vs.size();
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
        MvccStore db = new MvccStore();
        Tx t1 = db.begin();
        t1.put("x", "10");
        eq(t1.get("x"), "10", "own write visible");
        Tx t2 = db.begin();
        eq(t2.get("x"), null, "uncommitted write invisible");
        t1.commit();
        eq(t2.get("x"), null, "commit after t2's snapshot stays invisible");
        eq(db.begin().get("x"), "10", "new transaction sees the commit");
        Tx t3 = db.begin();
        t3.put("x", "99");
        t3.rollback();
        eq(db.begin().get("x"), "10", "rolled back write discarded");
        throwsEx(IllegalStateException.class, () -> t3.get("x"), "use after rollback");
    }

    static void stage2() {
        MvccStore db = new MvccStore();
        Tx w = db.begin();
        w.put("k", "v");
        w.commit();
        Tx reader = db.begin();
        Tx deleter = db.begin();
        deleter.delete("k");
        eq(deleter.get("k"), null, "own delete visible");
        deleter.commit();
        eq(reader.get("k"), "v", "old snapshot still sees the deleted key");
        eq(db.begin().get("k"), null, "new snapshot sees the delete");
    }

    static void stage3() {
        MvccStore db = new MvccStore();
        Tx init = db.begin();
        init.put("balance", "100");
        init.commit();
        Tx a = db.begin();
        Tx b = db.begin();
        a.put("balance", String.valueOf(Integer.parseInt(a.get("balance")) + 10));
        b.put("balance", String.valueOf(Integer.parseInt(b.get("balance")) + 20));
        a.commit();
        throwsEx(ConflictException.class, b::commit, "second writer of the same key");
        eq(db.begin().get("balance"), "110", "the first commit stands, nothing lost silently");
        throwsEx(IllegalStateException.class, b::commit, "aborted transaction is closed");

        Tx c = db.begin();
        Tx d = db.begin();
        c.put("p", "1");
        d.put("q", "2"); // different keys: no conflict
        c.commit();
        d.commit();
        Tx e = db.begin();
        eq(e.get("p") + e.get("q"), "12", "disjoint writes both commit");
    }

    static void stage4() {
        MvccStore db = new MvccStore();
        for (int i = 1; i <= 3; i++) {
            Tx t = db.begin();
            t.put("x", "v" + i);
            t.commit();
        }
        Tx old = db.begin(); // snapshot sees v3
        Tx t = db.begin();
        t.put("x", "v4");
        t.commit();
        eq(db.garbageCollect(), 2, "v1 and v2 unreadable, v3 kept for the open snapshot");
        eq(db.versionCount("x"), 2, "v3 and v4 left");
        eq(old.get("x"), "v3", "open snapshot unaffected");
        old.rollback();
        eq(db.garbageCollect(), 1, "v3 dropped once no snapshot needs it");
        Tx check = db.begin();
        eq(check.get("x"), "v4", "latest value kept");
        check.rollback(); // an open transaction would keep old versions alive

        Tx del = db.begin();
        del.delete("x");
        del.commit();
        db.garbageCollect();
        eq(db.versionCount("x"), 0, "deleted key removed entirely");
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
