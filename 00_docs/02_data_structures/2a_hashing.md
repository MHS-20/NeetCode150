# Hash Maps, Sets, and Their Ordered Versions

## The idea

A hash map turns a key into an array index by running it through a **hash function**, then stores the value at that slot. No searching, no comparing — the key computes its own address.

```
key "cat"  →  hash("cat") = 8391027  →  8391027 % 8 = 3
                                              ↓
buckets:  [ _ ][ _ ][ _ ][ cat:1 ][ _ ][ _ ][ _ ][ _ ]
            0    1    2      3      4    5    6    7
```

A **set** is the same structure storing only keys, with the value dropped. Every complexity and every caveat below applies identically to both; a set is a map whose values are all `True`.

## Complexity, and what "average" is hiding

| Operation | Average | Worst case |
|---|---|---|
| insert | O(1) | O(n) |
| lookup / `in` | O(1) | O(n) |
| delete | O(1) | O(n) |
| iterate all | O(n) | O(n) |
| find min / max | **O(n)** | O(n) |
| space | O(n) | O(n) |

The O(1) is *average*, not guaranteed, and it rests on two assumptions: the hash function spreads keys evenly across buckets, and the table has enough buckets that most contain one entry. Break either and a lookup degrades toward scanning a whole bucket.

Note the `O(n)` on min/max. A hash table has no ordering whatsoever — keys land wherever their hash sends them — so "smallest key" means checking every one. If a problem needs both fast lookup *and* order, that is what the ordered variants at the bottom of this file are for.

## Collisions

Two different keys can hash to the same bucket. This is unavoidable: the key space is unbounded and the bucket count is not. Two standard resolutions.

**Chaining.** Each bucket holds a list of entries. On collision, append; on lookup, scan the short list comparing keys for real equality.

```
bucket 3:  [ cat:1 ] → [ act:7 ] → [ tac:9 ]
```

**Open addressing.** Keep one entry per bucket; on collision, probe forward for the next free slot. Lookup probes the same sequence until it finds the key or an empty slot. CPython's `dict` uses this.

```
insert "act", also hashing to 3:
  slot 3 taken → try 4 → free → store there
  [ _ ][ _ ][ _ ][ cat:1 ][ act:7 ][ _ ]
```

Either way, the cost of an operation is the length of the collision chain or probe sequence. With a good hash function that averages a small constant.

**The worst case is all n keys in one bucket**, which makes every lookup an O(n) scan and turns an O(n) algorithm into O(n²). In practice this happens only with adversarial input (deliberately crafted colliding keys — a real denial-of-service vector, which is why Python randomises string hashing per process) or a badly written custom `hashCode`. It is not something an interview input will trigger, but stating the worst case when asked is the difference between knowing the structure and reciting it.

## Load factor and resizing

The **load factor** is `entries / buckets`. As it rises, collisions rise with it. Implementations keep it under a threshold — roughly 0.66 for CPython, 0.75 for Java — by **resizing**: allocate a table two to four times larger and reinsert every entry.

Reinsertion is required because the bucket index is `hash % capacity`, and changing the capacity changes every index. That makes a resize O(n).

Resizes happen after 1, 2, 4, 8, … doublings of content, so the copying across `n` inserts sums to less than `2n`, and the per-insert cost stays **O(1) amortised** — the same argument as array doubling in [`2d_stacks.md`](2d_stacks.md). The practical consequence: a single insert can occasionally be slow, which matters for latency-sensitive code and never for interview complexity. If the final size is known, presizing the table skips the rehashing entirely.

## What can be a key

A key must be **hashable**, which in practice means **immutable**. The reason is mechanical: the object's hash determines which bucket it sits in, so mutating a key after insertion leaves it filed under an address that no longer matches it. It becomes unfindable — still consuming memory, never returned by a lookup.

```python
d = {}
d[(1, 2)] = "ok"        # tuple — immutable, hashable
d[[1, 2]] = "boom"      # TypeError: unhashable type: 'list'
d[frozenset({1, 2})]    # frozenset is the hashable set
```

Two rules that must hold together for any custom key type:

1. Equal objects must have equal hashes. Otherwise equal keys land in different buckets and the map holds duplicates.
2. Unequal objects *may* share a hash. That is just a collision, handled by the equality check.

In Python, defining `__eq__` without `__hash__` makes a class unhashable by default — the language forcing rule 1 rather than letting you violate it silently. Java's contract is the same: override `equals`, override `hashCode`.

A common trick follows from this: to key on a multiset, use a canonical immutable form. Grouping anagrams uses the sorted string or a 26-length tuple of counts as the key.

## What they're actually for

The recurring move is **trading space for time**: replace a scan with a lookup, turning O(n²) into O(n).

**Seen-before.** Two Sum, Contains Duplicate, Longest Consecutive Sequence. One pass, checking membership of something already computed.

```python
seen = {}
for i, x in enumerate(nums):
    if target - x in seen:        # O(1) instead of scanning the prefix
        return [seen[target - x], i]
    seen[x] = i
```

**Counting.** Frequency maps for Valid Anagram, Top K Frequent, Group Anagrams. `collections.Counter` is a dict subclass with counting built in.

**Grouping.** `defaultdict(list)` keyed by some canonical form — the sorted string for anagrams, `(row//3, col//3)` for Sudoku boxes.

**Memoization.** Every top-down DP cache is a hash map from state tuple to answer (see [`10a_dynamic_programming.md`](../10_dynamic_programming/10a_dynamic_programming.md)).

**Visited tracking.** Graph traversal, cycle detection, backtracking (see [`9a_graphs_bfs_dfs.md`](../09_graphs/9a_graphs_bfs_dfs.md)).

**Sliding window state.** A count map of the current window, updated as it moves rather than recomputed.

**Adjacency lists.** `defaultdict(list)` is the usual graph representation.

Sets specifically: membership testing, deduplication, and intersection/union/difference in O(min(n, m)) rather than nested loops.

```python
a & b    # intersection
a | b    # union
a - b    # difference
```

## Ordered versions

"Ordered" means two genuinely different things, implemented differently, with different complexity. Confusing them is the main source of wrong answers here.

### Insertion-ordered — still a hash table

Keys come back in the order they were first inserted. This is not sorting, and it costs nothing asymptotically: the implementation is a hash table plus a doubly linked list threading the entries in insertion order, or (in CPython) a compact array of entries with the hash table storing indices into it.

```
hash table (indices)          entries array (insertion order)
  [ _ ][ 2 ][ 0 ][ _ ][ 1 ]     0: ("cat", 1)
                                1: ("dog", 2)
                                2: ("fox", 3)
```

Lookups still go through the hash table, so they stay O(1). Iteration walks the entries array, which is also why iterating a modern Python dict is faster and more cache-friendly than iterating a chained one.

- **Python**: `dict` preserves insertion order as a language guarantee since 3.7. `collections.OrderedDict` adds `move_to_end()` and `popitem(last=False)`, which is why it is still the natural base for an LRU cache.
- **Java**: `LinkedHashMap` / `LinkedHashSet`. Its `accessOrder` constructor flag reorders on *access* rather than insertion, giving an LRU cache with an overridable `removeEldestEntry`.
- **C++**: no standard equivalent; combine `unordered_map` with a `list` manually.

An LRU cache is exactly this structure: a hash map for O(1) lookup, plus a linked list for O(1) eviction of the least recently used end. Both halves are needed — the map alone cannot tell you what is oldest, and the list alone cannot find a key.

### Sorted — not a hash table at all

Keys come back in comparison order. This cannot be done with hashing, because a hash deliberately destroys the relationship between a key's value and its location. A sorted map is a **balanced binary search tree** (red-black, typically), so every operation walks the tree height.

| Operation | Hash map | Sorted map |
|---|---|---|
| insert / lookup / delete | O(1) avg | **O(log n)** |
| min / max | O(n) | **O(1)–O(log n)** |
| predecessor / successor | not supported | **O(log n)** |
| range query `[lo, hi]` | O(n) | **O(log n + k)** |
| iterate in sorted order | O(n log n) — must sort | **O(n)** |

- **C++**: `std::map` / `std::set` are the sorted, tree-backed ones; `std::unordered_map` / `unordered_set` are the hash-backed ones. The shorter name being the slower structure catches people out.
- **Java**: `TreeMap` / `TreeSet`, with `floorKey`, `ceilingKey`, `higherKey`, `subMap`, `headMap`.
- **Python**: nothing in the standard library. Use `sortedcontainers` (`SortedList`, `SortedDict`) where available, or a heap when only the extreme is needed, or `bisect` on a list — which gives O(log n) *search* but O(n) insertion, since the elements shift.

Reach for a sorted map only when the extra operations are actually required: "the smallest key greater than x", "everything in this range", "process in sorted order as items arrive". Paying O(log n) for plain lookups otherwise is a straight loss.

### Which to use

| Need | Structure |
|---|---|
| membership, counting, grouping | hash map / hash set |
| the above, plus stable output order | insertion-ordered map |
| LRU eviction | hash map + doubly linked list |
| smallest/largest only | heap ([`2g_heaps_and_priority_queues.md`](2g_heaps_and_priority_queues.md)) |
| predecessor, successor, range queries | sorted map / balanced BST |
| all keys sorted, built once | hash map, then sort at the end |

That last row is worth noting: if order is needed only for the final output, a hash map plus one O(n log n) sort at the end usually beats maintaining a tree throughout.

## Pitfalls

- **Claiming O(1) worst case.** It is average. Say so when asked.
- **Mutating a key after insertion.** The entry becomes unreachable, with no error raised.
- **`defaultdict` creating entries on read.** Merely checking `d[k]` inserts a default value, which silently changes the map's size and its iteration.
- **Modifying a map while iterating it.** `RuntimeError` in Python, `ConcurrentModificationException` in Java, undefined behaviour in C++. Collect keys first, then mutate.
- **Relying on `set` iteration order.** Python's `dict` guarantees insertion order; `set` does not guarantee anything.
- **Assuming a sorted map is a hash map.** `std::map` is O(log n), not O(1); a loop doing a million lookups will feel the difference.
- **Hashing a mutable object as a key.** Freeze it first — `tuple(list)`, `frozenset(set)`, `str(sorted(...))`.
