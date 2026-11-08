# Dijkstra's Algorithm

## What it solves

Dijkstra finds the **shortest path from one source to every other node** in a graph whose edges have **non-negative weights**. The weight can be time, cost, distance, or any quantity that adds up along a path. The graph can be directed or undirected.

BFS already solves this when every edge has the same weight: it visits nodes in order of hop count, so the first visit is the shortest. With weights, hop count stops being the measure. Three edges of weight 1 beat one edge of weight 10, and BFS would pick the single edge because it has fewer hops ([`11a_graphs_bfs_dfs.md`](11a_graphs_bfs_dfs.md)). Dijkstra keeps the BFS idea and changes the order: instead of a FIFO queue, it uses a **min-heap keyed by distance from the source**, so it always expands the closest unfinished node next.

## How it works

Keep a `dist` array, the best known distance to each node, starting at `∞` everywhere except `dist[source] = 0`.

1. Push `(0, source)` into a min-heap.
2. Pop the entry with the smallest distance `d`, for node `u`.
3. If `d > dist[u]`, the entry is stale (see below). Skip it.
4. Otherwise `d` is final. For each edge `u → v` with weight `w`, if `d + w < dist[v]`, set `dist[v] = d + w` and push `(dist[v], v)`. This update is called **relaxing** the edge.
5. Repeat until the heap is empty.

```
edges: 0→1 (4)   0→2 (1)   2→1 (2)   1→3 (1)   2→3 (5)

pop (0,0)   relax 0→1: 4     relax 0→2: 1      heap [(1,2) (4,1)]
pop (1,2)   relax 2→1: 3<4   relax 2→3: 6      heap [(3,1) (4,1) (6,3)]
pop (3,1)   relax 1→3: 4<6                     heap [(4,1) (4,3) (6,3)]
pop (4,1)   4 > dist[1] = 3 → stale, skip
pop (4,3)   node 3 has no outgoing edges
pop (6,3)   6 > dist[3] = 4 → stale, skip

dist: 0:0  1:3  2:1  3:4
```

The direct edge `0→1` costs 4, but `0→2→1` costs 3. Node 1 is first discovered at 4 and improved to 3 before it is popped.

### Stale entries

C++ `priority_queue`, Python `heapq` and Java `PriorityQueue` have no way to lower the priority of an element already in the heap (no "decrease-key"). Dijkstra works around this with **lazy deletion**: when `dist[v]` improves, push a new entry and leave the old one in the heap ([`2g_heaps_and_priority_queues.md`](../02_data_structures/2g_heaps_and_priority_queues.md)). A node can then sit in the heap several times. The `d > dist[u]` check discards every entry except the one matching the current best distance.

Without that check, the algorithm still gives correct distances. However, each stale pop re-relaxes all of the node's edges, and on dense graphs this repeated work dominates the running time. A `visited` set, marked when a node is popped, does the same job as the `d > dist[u]` check.

### Why the popped distance is final

When `u` is popped with distance `d`, every other entry in the heap has distance `≥ d`. Any other route to `u` has to leave the set of finished nodes through some node still in the heap, which is already at `≥ d`, and then add non-negative edges. It cannot come back below `d`. So `d` is the true shortest distance, and `u` never needs to be processed again.

That argument uses non-negative weights in its last step, and it fails without them (see "When it's the wrong tool").

### Template

```cpp
vector<long long> dijkstra(int n, vector<vector<pair<int,int>>> &adj, int src) {
  vector<long long> dist(n, LLONG_MAX);
  priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
  dist[src] = 0;
  pq.push({0, src});

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;             // stale entry
    for (auto [v, w] : adj[u])
      if (d + w < dist[v]) {
        dist[v] = d + w;
        pq.push({dist[v], v});
      }
  }
  return dist;                             // LLONG_MAX = unreachable
}
```

The heap entry is `(distance, node)` with distance first, because `pair` compares its first field first. `greater<>` turns C++'s default max-heap into a min-heap.

### Complexity

Each edge can push at most one entry, so the heap holds O(E) entries, and every push and pop costs O(log E). Since `E ≤ V²`, `log E ≤ 2 log V`, so the total is **O((V + E) log V)** time and O(V + E) space.

On a **dense graph**, where E is close to V², the heap adds overhead for nothing. The array version scans `dist` for the smallest unfinished node in O(V), V times, for **O(V²)** total with no heap. That beats O(V² log V) when every pair of nodes is connected.

## Worked example: Network Delay Time (743)

A signal starts at node `k` and travels along directed edges `(u, v, time)`. Return how long until every node has received it, or `-1` if some node never does.

A node receives the signal at its shortest-path distance from `k`. Every node has received it once the *farthest* node has. The answer is therefore `max(dist)` after one run of Dijkstra from `k`, or `-1` if any `dist` is still `∞`.

```
times = [[2,1,1], [2,3,1], [3,4,1]],  n = 4,  k = 2

dist: 1:1  2:0  3:1  4:2      answer = max = 2
```

Nodes are labelled `1..n`, so `dist` has size `n + 1`, and the maximum must skip index 0. Index 0 stays at `∞` and would turn every answer into `-1`.

## Variants

**Path reconstruction.** Dijkstra returns distances, not paths. Store `prev[v] = u` whenever relaxing `u → v` improves `dist[v]`. Afterwards, walk `prev` back from the target to the source and reverse the result.

**Single target.** If only `dist[target]` matters, return as soon as the target is *popped*, not when it is first pushed. A push only means "a path was found", and a cheaper one may still be discovered later.

**Multiple sources.** Push every source at distance 0 before the loop starts. The result is each node's distance to its nearest source. This is the weighted version of multi-source BFS.

**Minimax paths.** Some problems score a path by its worst edge instead of the sum of its edges, as in Path With Minimum Effort (1631) and Swim in Rising Water (778). Replace `d + w` with `max(d, w)`. The proof still works because `max` never decreases along a path, which is the property non-negative weights gave the sum.

**State-augmented Dijkstra.** If a path's validity depends on more than the node it is at, add that information to the node. The graph's nodes become `(node, extra)` pairs. Examples are remaining fuel, number of stops used, or keys collected. Dijkstra then runs unchanged on the larger graph of states. The cost is that the state count multiplies V.

**0-1 BFS.** When every weight is 0 or 1, a deque replaces the heap. Push 0-weight edges to the front and 1-weight edges to the back. The deque stays sorted by distance, and the total is O(V + E).

## When it's the wrong tool

**Negative edge weights.** The proof's last step, "adding edges never lowers the distance", is false. Take:

```
0→1 (2)    0→2 (3)    2→1 (-2)
```

Dijkstra pops node 1 at distance 2 and marks it final. The true distance is `3 + (-2) = 1`, through node 2, which is popped later. A version with a `visited` set never revisits node 1 and returns 2.

The lazy version without `visited` happens to fix this example, because it relaxes `2→1` and pushes node 1 again. It then behaves like a label-correcting search, and its worst case is exponential. Use **Bellman-Ford** instead, which takes O(V · E) and also detects negative cycles ([`11e_bellman_ford.md`](11e_bellman_ford.md)).

**A limit on the number of edges.** Cheapest Flights Within K Stops (787) asks for the cheapest route with at most `k` stops. Plain Dijkstra finalises each city at its cheapest cost, whatever the number of stops. A cheap path with too many stops can then block a more expensive path that fits the limit:

```
0→1 (1)   1→2 (1)   0→2 (5)   2→3 (1)      src 0, dst 3, k = 1

Dijkstra finalises 2 at cost 2 via 0→1→2 (already 1 stop).
0→2→3 = 6 uses 1 stop and is the answer, but the entry (5, 2) is stale and gets skipped.
Only 0→1→2→3 = 3 reaches 3, and it uses 2 stops.
```

There are two correct fixes:

- **Bellman-Ford limited to `k + 1` rounds**, each reading a copy of the previous round's distances.
- **BFS by level**, one level per flight, stopping after `k + 1` levels.

[`11e_bellman_ford.md`](11e_bellman_ford.md) covers both, with code and a trace of what goes wrong without the copy.

Augmented Dijkstra on `(city, stops)` also works, at the cost of `V · (k + 2)` states.

**Unweighted graphs.** Plain BFS gives the same answer in O(V + E) without the log factor.

**All-pairs shortest paths.** Running Dijkstra from every node costs O(V · (V + E) log V). For small dense graphs, roughly V ≤ 400, Floyd-Warshall's O(V³) triple loop is shorter to write, and it also handles negative edges.

## Dijkstra and Prim

Prim's minimum spanning tree algorithm is the same loop with a different key. Dijkstra pushes `dist[u] + w`, the total distance from the source. Prim pushes `w` alone, the cost of the single edge that would attach `v` to the tree. Dijkstra produces a shortest-path tree from one source. Prim produces the tree of minimum total weight. These are different trees on the same graph, and swapping the key turns one algorithm into the other.

## How to spot it

- The question asks for the **minimum total cost, time or distance** between nodes, and the edges have different, non-negative weights.
- The input is a **weighted edge list** `(u, v, w)`, or a grid where moving between cells has a cost.
- The question asks **"how long until everything is reached"**, which is the maximum of the shortest distances, as in 743.
- The score of a path is its **worst edge**, which is the minimax variant.
- Validity depends on a **resource** (fuel, stops, keys). Add it to the state, or switch to Bellman-Ford when it is an edge-count limit.

## Pitfalls

- **Marking nodes final when they are pushed.** A node's first push is not its shortest distance, as in the trace above, where node 1 is pushed at 4 and finalised at 3. Mark it finished on pop.
- **No stale-entry check.** Distances stay correct, but every stale pop re-relaxes the node's edges.
- **Overflow in `d + w`.** If `dist` is `INT_MAX` for unreachable nodes and the code ever adds to it, the sum wraps to a negative number and looks like a short path. Only relax from popped nodes, whose distances are finite, or use `long long`.
- **Heap ordered the wrong way.** `priority_queue<pair<int,int>>` in C++ is a max-heap, so it pops the farthest node first. The algorithm still terminates, but distances get revised many times and the running time degrades badly. Use `greater<>`, or push negated distances.
- **`(node, dist)` instead of `(dist, node)`.** The heap then orders by node index, and the algorithm stops being Dijkstra.
- **Treating directed edges as undirected, or the reverse.** Network Delay Time is directed. Grid and road problems are usually undirected, so each edge must be added in both directions.
- **1-indexed nodes.** Size arrays `n + 1`, and leave index 0 out of any `max` or `count` over `dist`.
