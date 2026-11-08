# LRU Cache

A cache with a fixed capacity that evicts the least recently used entry when full.

## Stages

1. **LRU.** `get(key)` returns the value or null, and counts as a use. `put(key, value)` inserts or replaces, and also counts as a use. When a new key arrives and the cache is full, the least recently used entry is evicted. Both operations are O(1).
2. **Time to live.** `put(key, value, ttlMillis)` sets an expiry time. An entry is expired from `now >= insert time + ttl` and is then treated as absent. When the cache is full, an expired entry is evicted before any live one. The clock must be injectable for testing.
3. **Resize.** `resize(capacity)` changes the capacity and evicts least recently used entries until the cache fits.

## Design notes

A hash map gives O(1) lookup of a node, and a doubly linked list keeps the nodes in recency order, so moving a node to the front or removing the last one is O(1). Two sentinel nodes at the ends remove every null check from the list code. Expired entries are removed lazily, on access or when space is needed, instead of with a background timer. Finding an expired entry at eviction time scans from the old end, which is O(n) in the worst case; a second structure ordered by expiry time (a heap) would make it O(log n).

## Changes from the original version

The original used a doubly linked list class that was never defined, so it did not compile. This version writes the list inline with sentinel nodes, and adds expiry and resizing.

## Files

`LruCache.java`: the solution, with checks for each stage in `main`. Run with `java LruCache.java` (Java 21+).
