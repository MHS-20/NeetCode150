import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.function.LongSupplier;

/**
 * LRU cache with optional per-entry time-to-live.
 *
 * A hash map finds an entry's node in O(1). The nodes form a doubly linked
 * list ordered by recency, between two sentinel nodes so that no operation
 * needs a null check: head.next is the most recently used entry and
 * tail.prev the least recently used. The clock is injected so that expiry
 * can be tested without sleeping.
 */
public class LruCache<K, V> {
    public static final long NO_TTL = -1;

    private final class Node {
        K key;
        V value;
        long expiresAt;
        Node prev, next;
    }

    private final Map<K, Node> index = new HashMap<>();
    private final Node head = new Node(), tail = new Node();
    private final LongSupplier clock;
    private int capacity;

    public LruCache(int capacity, LongSupplier clock) {
        if (capacity <= 0) throw new IllegalArgumentException("capacity must be positive");
        this.capacity = capacity;
        this.clock = clock;
        head.next = tail;
        tail.prev = head;
    }

    public LruCache(int capacity) {
        this(capacity, System::currentTimeMillis);
    }

    /** Returns the value, or null if absent or expired; marks the entry as most recently used. */
    public V get(K key) {
        Node n = index.get(key);
        if (n == null) return null;
        if (expired(n)) {
            remove(n);
            return null;
        }
        moveToFront(n);
        return n.value;
    }

    public void put(K key, V value) {
        put(key, value, NO_TTL);
    }

    /** Inserts or replaces; the entry expires ttlMillis after now, or never with NO_TTL. */
    public void put(K key, V value, long ttlMillis) {
        long expiresAt = ttlMillis == NO_TTL ? Long.MAX_VALUE : clock.getAsLong() + ttlMillis;
        Node n = index.get(key);
        if (n == null) {
            if (index.size() == capacity) evictOne();
            n = new Node();
            n.key = key;
            index.put(key, n);
        } else {
            unlink(n);
        }
        n.value = value;
        n.expiresAt = expiresAt;
        linkFront(n);
    }

    /** Changes the capacity, evicting least recently used entries if needed. */
    public void resize(int newCapacity) {
        if (newCapacity <= 0) throw new IllegalArgumentException("capacity must be positive");
        capacity = newCapacity;
        while (index.size() > capacity) evictOne();
    }

    /** Entries currently stored, including expired ones not yet removed. */
    public int storedEntries() {
        return index.size();
    }

    /** Evicts an expired entry if there is one, otherwise the least recently used. */
    private void evictOne() {
        long now = clock.getAsLong();
        for (Node n = tail.prev; n != head; n = n.prev) {
            if (n.expiresAt <= now) {
                remove(n);
                return;
            }
        }
        remove(tail.prev);
    }

    private boolean expired(Node n) {
        return n.expiresAt <= clock.getAsLong();
    }

    private void moveToFront(Node n) {
        unlink(n);
        linkFront(n);
    }

    private void remove(Node n) {
        unlink(n);
        index.remove(n.key);
    }

    private void unlink(Node n) {
        n.prev.next = n.next;
        n.next.prev = n.prev;
    }

    private void linkFront(Node n) {
        n.next = head.next;
        n.prev = head;
        head.next.prev = n;
        head.next = n;
    }

    // ---- checks -------------------------------------------------------------

    public static void main(String[] args) {
        stage1();
        stage2();
        stage3();
        System.out.println("all checks passed");
    }

    static void stage1() {
        LruCache<Integer, String> c = new LruCache<>(2);
        c.put(1, "a");
        c.put(2, "b");
        eq(c.get(1), "a", "get 1"); // 1 is now most recent
        c.put(3, "c"); // evicts 2
        eq(c.get(2), null, "2 evicted");
        c.put(1, "A"); // update moves 1 to the front
        c.put(4, "d"); // evicts 3
        eq(c.get(3), null, "3 evicted");
        eq(c.get(1), "A", "1 updated and kept");
        eq(c.get(4), "d", "4 present");
    }

    static void stage2() {
        long[] now = {1000};
        LruCache<String, Integer> c = new LruCache<>(2, () -> now[0]);
        c.put("x", 1, 100); // expires at 1100
        c.put("y", 2);
        now[0] = 1099;
        eq(c.get("x"), 1, "before expiry");
        now[0] = 1100;
        eq(c.get("x"), null, "expired exactly at its deadline");
        eq(c.storedEntries(), 1, "expired entry removed on access");

        c.put("x", 1, 50); // x expires at 1150, y is the LRU entry
        now[0] = 1200;
        c.put("z", 3); // full: the expired x goes first, not the LRU y
        eq(c.get("y"), 2, "live y kept over expired x");
        eq(c.get("z"), 3, "z inserted");
    }

    static void stage3() {
        LruCache<Integer, Integer> c = new LruCache<>(4);
        for (int i = 1; i <= 4; i++) c.put(i, i);
        c.get(1);
        c.resize(2); // order by recency: 1, 4, 3, 2 -> keep 1 and 4
        eq(c.storedEntries(), 2, "size after shrink");
        eq(c.get(1), 1, "most recent kept");
        eq(c.get(4), 4, "second most recent kept");
        eq(c.get(2), null, "evicted by resize");
        c.resize(3);
        c.put(5, 5);
        eq(c.storedEntries(), 3, "grown capacity used");
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }
}
