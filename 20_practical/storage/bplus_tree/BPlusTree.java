import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Random;
import java.util.TreeMap;

/**
 * B+ tree map: values live only in the leaves, and the leaves are linked in
 * key order so a range scan walks them without going back up the tree.
 * Internal nodes hold separator keys only: child i holds the keys k with
 * keys[i-1] <= k < keys[i].
 *
 * A node may hold at most maxKeys keys. Inserting into a full node splits it
 * in two. A leaf split copies the right half's first key up as the separator;
 * an internal split moves its middle key up. When the root splits, a new root
 * is created, so the tree grows at the top and all leaves stay at one depth.
 */
public class BPlusTree<K extends Comparable<K>, V> {

    private abstract static sealed class Node<K, V> permits Leaf, Internal {
        final List<K> keys = new ArrayList<>();
    }

    private static final class Leaf<K, V> extends Node<K, V> {
        final List<V> values = new ArrayList<>();
        Leaf<K, V> next;
    }

    private static final class Internal<K, V> extends Node<K, V> {
        final List<Node<K, V>> children = new ArrayList<>();
    }

    /** Result of a split: the key to insert in the parent and the new right node. */
    private record Split<K, V>(K separator, Node<K, V> right) {}

    private final int maxKeys;
    private Node<K, V> root = new Leaf<>();
    private int size;

    public BPlusTree(int maxKeys) {
        if (maxKeys < 3) throw new IllegalArgumentException("maxKeys must be at least 3");
        this.maxKeys = maxKeys;
    }

    public V get(K key) {
        Leaf<K, V> leaf = findLeaf(key);
        int i = Collections.binarySearch(leaf.keys, key);
        return i >= 0 ? leaf.values.get(i) : null;
    }

    /** Inserts or replaces the value for key. */
    public void put(K key, V value) {
        Objects.requireNonNull(key, "key");
        Split<K, V> split = insert(root, key, value);
        if (split != null) {
            Internal<K, V> newRoot = new Internal<>();
            newRoot.keys.add(split.separator());
            newRoot.children.add(root);
            newRoot.children.add(split.right());
            root = newRoot;
        }
    }

    /** Entries with from <= key < to, in key order. */
    public List<Map.Entry<K, V>> range(K from, K to) {
        List<Map.Entry<K, V>> out = new ArrayList<>();
        Leaf<K, V> leaf = findLeaf(from);
        int i = lowerBound(leaf.keys, from);
        while (leaf != null) {
            for (; i < leaf.keys.size(); i++) {
                K k = leaf.keys.get(i);
                if (k.compareTo(to) >= 0) return out;
                out.add(Map.entry(k, leaf.values.get(i)));
            }
            leaf = leaf.next;
            i = 0;
        }
        return out;
    }

    public int size() {
        return size;
    }

    public int height() {
        int h = 1;
        for (Node<K, V> n = root; n instanceof Internal<K, V> in; n = in.children.get(0)) h++;
        return h;
    }

    private Leaf<K, V> findLeaf(K key) {
        Node<K, V> n = root;
        while (n instanceof Internal<K, V> in) n = in.children.get(childIndex(in, key));
        return (Leaf<K, V>) n;
    }

    private Split<K, V> insert(Node<K, V> node, K key, V value) {
        return switch (node) {
            case Leaf<K, V> leaf -> insertIntoLeaf(leaf, key, value);
            case Internal<K, V> in -> {
                int c = childIndex(in, key);
                Split<K, V> split = insert(in.children.get(c), key, value);
                if (split == null) yield null;
                in.keys.add(c, split.separator());
                in.children.add(c + 1, split.right());
                yield in.keys.size() > maxKeys ? splitInternal(in) : null;
            }
        };
    }

    private Split<K, V> insertIntoLeaf(Leaf<K, V> leaf, K key, V value) {
        int i = Collections.binarySearch(leaf.keys, key);
        if (i >= 0) {
            leaf.values.set(i, value);
            return null;
        }
        i = -i - 1;
        leaf.keys.add(i, key);
        leaf.values.add(i, value);
        size++;
        return leaf.keys.size() > maxKeys ? splitLeaf(leaf) : null;
    }

    private Split<K, V> splitLeaf(Leaf<K, V> leaf) {
        int mid = leaf.keys.size() / 2;
        Leaf<K, V> right = new Leaf<>();
        moveTail(leaf.keys, mid, right.keys);
        moveTail(leaf.values, mid, right.values);
        right.next = leaf.next;
        leaf.next = right;
        return new Split<>(right.keys.get(0), right); // copied up: the key stays in the leaf
    }

    private Split<K, V> splitInternal(Internal<K, V> in) {
        int mid = in.keys.size() / 2;
        K separator = in.keys.get(mid);
        Internal<K, V> right = new Internal<>();
        moveTail(in.keys, mid + 1, right.keys);
        moveTail(in.children, mid + 1, right.children);
        in.keys.remove(mid); // moved up: the key leaves this level
        return new Split<>(separator, right);
    }

    /** Index of the child whose range contains key: the number of separators <= key. */
    private int childIndex(Internal<K, V> in, K key) {
        int i = Collections.binarySearch(in.keys, key);
        return i >= 0 ? i + 1 : -i - 1;
    }

    private static <K extends Comparable<K>> int lowerBound(List<K> keys, K key) {
        int i = Collections.binarySearch(keys, key);
        return i >= 0 ? i : -i - 1;
    }

    private static <T> void moveTail(List<T> from, int start, List<T> to) {
        List<T> tail = from.subList(start, from.size());
        to.addAll(tail);
        tail.clear();
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
        BPlusTree<Integer, String> t = new BPlusTree<>(4);
        eq(t.get(1), null, "empty tree");
        t.put(3, "c");
        t.put(1, "a");
        t.put(2, "b");
        eq(t.get(1), "a", "get 1");
        eq(t.get(3), "c", "get 3");
        eq(t.get(4), null, "missing key");
        eq(t.height(), 1, "one leaf");
    }

    static void stage2() {
        BPlusTree<Integer, Integer> t = new BPlusTree<>(4);
        for (int k = 1; k <= 5; k++) t.put(k, k);
        eq(t.height(), 2, "fifth key splits the root leaf");
        TreeMap<Integer, Integer> expected = new TreeMap<>();
        List<Integer> keys = new ArrayList<>();
        for (int k = 0; k < 5000; k++) keys.add(k);
        Collections.shuffle(keys, new Random(42));
        t = new BPlusTree<>(4);
        for (int k : keys) {
            t.put(k, k * 10);
            expected.put(k, k * 10);
        }
        for (int k = -1; k <= 5000; k++) eq(t.get(k), expected.get(k), "get " + k);
        eq(t.size(), 5000, "size");
        t.checkInvariants();
        if (t.height() > 8) throw new AssertionError("tree too tall: " + t.height());
    }

    static void stage3() {
        BPlusTree<Integer, Integer> t = new BPlusTree<>(3);
        for (int k = 0; k < 100; k += 2) t.put(k, k); // even keys only
        eq(keysOf(t.range(10, 20)), List.of(10, 12, 14, 16, 18), "range with existing bounds");
        eq(keysOf(t.range(11, 17)), List.of(12, 14, 16), "range with missing bounds");
        eq(keysOf(t.range(95, 200)), List.of(96, 98), "range past the end");
        eq(keysOf(t.range(50, 50)), List.of(), "empty range");
        eq(t.range(-10, 1000).size(), 50, "whole tree via the leaf chain");
    }

    static void stage4() {
        BPlusTree<String, Integer> t = new BPlusTree<>(3);
        for (String s : List.of("d", "a", "c", "b", "e")) t.put(s, 1);
        t.put("c", 2);
        t.put("a", 3);
        eq(t.get("c"), 2, "replaced c");
        eq(t.get("a"), 3, "replaced a");
        eq(t.size(), 5, "replacing does not add entries");
        t.checkInvariants();
    }

    /** Sorted keys, node sizes, one leaf depth, separators bounding their children. */
    void checkInvariants() {
        int[] leafDepth = {-1};
        check(root, null, null, 1, leafDepth);
        List<K> chained = new ArrayList<>();
        Node<K, V> n = root;
        while (n instanceof Internal<K, V> in) n = in.children.get(0);
        for (Leaf<K, V> l = (Leaf<K, V>) n; l != null; l = l.next) chained.addAll(l.keys);
        if (chained.size() != size) throw new AssertionError("leaf chain misses keys");
        for (int i = 1; i < chained.size(); i++)
            if (chained.get(i - 1).compareTo(chained.get(i)) >= 0) throw new AssertionError("leaf chain unsorted");
    }

    private void check(Node<K, V> n, K low, K high, int depth, int[] leafDepth) {
        if (n.keys.size() > maxKeys) throw new AssertionError("overfull node");
        if (n != root && n.keys.isEmpty()) throw new AssertionError("empty node");
        for (K k : n.keys) {
            if (low != null && k.compareTo(low) < 0) throw new AssertionError("key below its range: " + k);
            if (high != null && k.compareTo(high) >= 0) throw new AssertionError("key above its range: " + k);
        }
        if (n instanceof Internal<K, V> in) {
            if (in.children.size() != in.keys.size() + 1) throw new AssertionError("child count");
            for (int i = 0; i < in.children.size(); i++) {
                K lo = i == 0 ? low : in.keys.get(i - 1);
                K hi = i == in.keys.size() ? high : in.keys.get(i);
                check(in.children.get(i), lo, hi, depth + 1, leafDepth);
            }
        } else if (leafDepth[0] == -1) {
            leafDepth[0] = depth;
        } else if (leafDepth[0] != depth) {
            throw new AssertionError("leaves at different depths");
        }
    }

    static List<Integer> keysOf(List<Map.Entry<Integer, Integer>> entries) {
        return entries.stream().map(Map.Entry::getKey).toList();
    }

    static void eq(Object got, Object expected, String what) {
        if (!Objects.equals(got, expected))
            throw new AssertionError(what + ": expected " + expected + ", got " + got);
    }
}
