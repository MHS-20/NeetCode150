import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

/**
 * In-memory key-value store with value counts and nested transactions.
 *
 * Writes go straight to {@code data}. Each open transaction keeps an undo log:
 * for every key it changed, the value the key had before the transaction's
 * first change to it (null = the key was absent). Rolling back replays that
 * log; committing discards all logs. Every operation is O(1), and a rollback
 * costs O(keys changed by the transaction).
 */
public class KvStore {
    private final Map<String, String> data = new HashMap<>();
    private final Map<String, Integer> valueCounts = new HashMap<>();
    private final Deque<Map<String, String>> undoLogs = new ArrayDeque<>();

    public String get(String key) {
        return data.get(key);
    }

    public void set(String key, String value) {
        Objects.requireNonNull(value, "value");
        remember(key);
        write(key, value);
    }

    public void delete(String key) {
        if (!data.containsKey(key)) return;
        remember(key);
        write(key, null);
    }

    public int count(String value) {
        return valueCounts.getOrDefault(value, 0);
    }

    public void begin() {
        undoLogs.push(new HashMap<>());
    }

    /** Undoes the innermost open transaction. */
    public void rollback() {
        if (undoLogs.isEmpty()) throw new IllegalStateException("NO TRANSACTION");
        undoLogs.pop().forEach(this::write);
    }

    /** Commits every open transaction: their changes are already in {@code data}. */
    public void commit() {
        if (undoLogs.isEmpty()) throw new IllegalStateException("NO TRANSACTION");
        undoLogs.clear();
    }

    private void remember(String key) {
        Map<String, String> log = undoLogs.peek();
        if (log != null && !log.containsKey(key)) log.put(key, data.get(key));
    }

    /** Sets or removes (value == null) a key and keeps valueCounts in step. */
    private void write(String key, String value) {
        String old = value == null ? data.remove(key) : data.put(key, value);
        if (old != null) valueCounts.computeIfPresent(old, (v, c) -> c == 1 ? null : c - 1);
        if (value != null) valueCounts.merge(value, 1, Integer::sum);
    }

    // ---- checks -------------------------------------------------------------

    public static void main(String[] args) {
        stage1();
        stage2();
        stage3();
        System.out.println("all checks passed");
    }

    static void stage1() {
        KvStore kv = new KvStore();
        eq(kv.get("a"), null, "missing key");
        kv.set("a", "1");
        kv.set("a", "2");
        eq(kv.get("a"), "2", "overwrite");
        kv.delete("a");
        kv.delete("a"); // deleting a missing key is a no-op
        eq(kv.get("a"), null, "deleted");
    }

    static void stage2() {
        KvStore kv = new KvStore();
        kv.set("a", "x");
        kv.set("b", "x");
        kv.set("c", "y");
        eq(kv.count("x"), 2, "two keys hold x");
        kv.set("a", "y"); // moves one count from x to y
        eq(kv.count("x"), 1, "x after overwrite");
        eq(kv.count("y"), 2, "y after overwrite");
        kv.delete("b");
        eq(kv.count("x"), 0, "x after delete");
        eq(kv.count("z"), 0, "unknown value");
    }

    static void stage3() {
        KvStore kv = new KvStore();
        kv.set("a", "1");
        kv.begin();
        kv.set("a", "2");
        kv.set("b", "2");
        kv.begin();
        kv.delete("a");
        kv.set("b", "3");
        kv.set("b", "4"); // the undo log keeps only the value before the first change
        eq(kv.count("2"), 0, "inside inner tx");
        kv.rollback();
        eq(kv.get("a"), "2", "inner rollback restores a");
        eq(kv.get("b"), "2", "inner rollback restores b");
        eq(kv.count("2"), 2, "counts restored");
        kv.rollback();
        eq(kv.get("a"), "1", "outer rollback");
        eq(kv.get("b"), null, "outer rollback removes b");
        eq(kv.count("1"), 1, "count after outer rollback");

        kv.begin();
        kv.set("a", "5");
        kv.begin();
        kv.set("c", "6");
        kv.commit(); // commits both levels
        eq(kv.get("a"), "5", "committed a");
        eq(kv.get("c"), "6", "committed c");
        throwsIse(kv::rollback, "rollback after commit");
        throwsIse(kv::commit, "commit with no transaction");
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }

    static void throwsIse(Runnable r, String what) {
        try {
            r.run();
        } catch (IllegalStateException e) {
            return;
        }
        throw new AssertionError(what + ": expected IllegalStateException");
    }
}
