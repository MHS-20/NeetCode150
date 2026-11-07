# Bellman-Ford

## What it solves

Bellman-Ford finds the shortest path from one source to every node, like Dijkstra ([`dijkstra.md`](dijkstra.md)), and also handles two cases Dijkstra cannot:

- **Negative edge weights.** It still returns correct distances, and it reports when a **negative cycle** makes some distances undefined.
- **A limit on the number of edges.** "Cheapest route with at most `k` stops" is answered by stopping after `k + 1` rounds.

It is slower than Dijkstra: O(V · E) against O((V + E) log V). Use it when one of those two cases applies, and Dijkstra otherwise.

## How it works

Start with `dist[source] = 0` and `∞` everywhere else. Then repeat `V - 1` times: go through **every edge** `u → v` with weight `w`, and if `dist[u] + w < dist[v]`, set `dist[v] = dist[u] + w`. That update is called **relaxing** the edge. It is the same step Dijkstra uses, but Bellman-Ford applies it to all edges in every round, in any order, instead of choosing nodes with a heap.

```cpp
vector<long long> bellmanFord(int n, vector<array<int,3>> &edges, int src) {
  const long long INF = LLONG_MAX;
  vector<long long> dist(n, INF);
  dist[src] = 0;
  for (int round = 0; round < n - 1; round++) {
    bool changed = false;
    for (auto [u, v, w] : edges)
      if (dist[u] != INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        changed = true;
      }
    if (!changed) break;                      // nothing moved: all final
  }
  return dist;
}
```

The input is a plain edge list. No adjacency list and no heap are needed.

### Trace

Four nodes, one negative edge, with the edges listed in an unhelpful order:

```
edges, in this order:   1→3 (2)   2→1 (-3)   0→1 (4)   0→2 (5)

round     dist[0]  dist[1]  dist[2]  dist[3]
start        0        ∞        ∞        ∞
1            0        4        5        ∞      1→3 and 2→1 read ∞, skipped
2            0        2        5        6      2→1: 5 - 3 = 2;  1→3: 4 + 2 = 6
3            0        2        5        4      1→3: 2 + 2 = 4
```

The path `0 → 2 → 1 → 3` costs `5 - 3 + 2 = 4`. Dijkstra on this graph would finalise node 1 at 4 before seeing the `-3` edge. Bellman-Ford finds 2, because every edge is re-examined in every round.

## Why V − 1 rounds are enough

After round `i`, `dist[v]` is at most the cost of the cheapest path to `v` that uses **at most `i` edges**. Take the cheapest such path, `source → … → x → v`. Its part up to `x` uses at most `i - 1` edges, so `dist[x]` was already that good after round `i - 1`. Round `i` then relaxes `x → v`.

The order of edges within a round can only help. In the trace, round 2 relaxes `2→1` before `1→3`, so `dist[3]` drops to 6 in the same round. That does not break the guarantee, which only says "at least this good after `i` rounds".

Without a negative cycle, a shortest path never repeats a node. If it did, it would contain a cycle of total weight `≥ 0`, and cutting the cycle out would give a path that is no longer. So every shortest path has at most `V - 1` edges, and `V - 1` rounds reach all of them.

**Early exit.** If a whole round changes nothing, the next round would read the same values and change nothing either. Stop there. On many inputs this ends long before `V - 1` rounds. In the trace above, round 3 still lowers `dist[3]`, so all 3 rounds run. With the edges listed in path order (`0→2`, `2→1`, `1→3`, `0→1`), round 1 reaches every final distance, and round 2 changes nothing and stops the loop.

## Negative cycles

A cycle whose total weight is negative can be traversed again and again, lowering the cost each time. Every node reachable from that cycle then has no shortest distance: its cost goes to `-∞`.

Detection takes one more round. After the `V - 1` rounds, run round `V`. If any edge still relaxes, there is a negative cycle reachable from the source. Without one, every distance would already be final.

```
0→1 (1)   1→2 (-1)   2→1 (-1)   2→3 (1)      4 nodes

cycle 1 → 2 → 1 has total weight -2
dist[1], dist[2] and dist[3] keep dropping every round
round 4 still relaxes 1→2 → negative cycle
```

Not every node is affected. A node that cannot be reached from the cycle keeps a correct distance. To mark exactly the affected ones, run another `V` rounds. In each round, set `dist[v] = -∞` whenever an edge `u → v` would still relax, or `dist[u]` is already `-∞`. After `V` rounds, the `-∞` marks have spread to everything reachable from the cycle.

**Undirected graphs.** An undirected edge with a negative weight is already a negative cycle: `u → v → u` costs `2w < 0`. Bellman-Ford on undirected graphs only makes sense with non-negative weights, and then Dijkstra is faster.

## Limiting the number of edges: Cheapest Flights Within K Stops (787)

Find the cheapest price from `src` to `dst` using at most `k` stops, which is at most `k + 1` flights. Plain Dijkstra fails here ([`dijkstra.md`](dijkstra.md) has a counterexample). Bellman-Ford fits directly: after round `i`, `dist` covers every path of at most `i` edges, so **`k + 1` rounds** give the answer.

That only holds if a round cannot chain several new edges. In the trace above, round 2 used `2→1` and then `1→3` in the same pass, which helps when the number of edges does not matter. With a limit, the same effect breaks it:

```
0→1 (100)   1→2 (100)   0→2 (500)      src 0, dst 2, k = 0 (direct flights only)

one round, updating dist in place:
  0→1   dist[1] = 100
  1→2   dist[2] = 100 + 100 = 200     uses dist[1] from this same round
  0→2   500 is not < 200

answer 200: two flights, which breaks k = 0. The correct answer is 500.
```

The fix is to read from a **copy** of the previous round's distances, so each round extends paths by exactly one edge:

```cpp
int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
  const int INF = INT_MAX;
  vector<int> dist(n, INF);
  dist[src] = 0;
  for (int round = 0; round <= k; round++) {        // k + 1 flights
    vector<int> next = dist;                        // writes go here
    for (auto &f : flights) {
      int u = f[0], v = f[1], w = f[2];
      if (dist[u] != INF && dist[u] + w < next[v])  // reads from last round
        next[v] = dist[u] + w;
    }
    dist = move(next);
  }
  return dist[dst] == INF ? -1 : dist[dst];
}
```

With the copy, the trace's single round reads `dist[1] = ∞` for `1→2`, skips it, and `0→2` sets `dist[2] = 500`.

O(k · E) time and O(V) space. A BFS that goes one level per flight solves the same problem. Each queue entry carries its own cost, and an entry is only pushed if it beats the best known cost for that city. That pruning is safe because BFS reaches cities through fewer flights first, so anything it drops uses at least as many flights and costs more.

## Variants

**Path reconstruction.** Store `prev[v] = u` whenever relaxing `u → v` lowers `dist[v]`, then walk `prev` back from the target. With a negative cycle, start at any node that relaxed in round `V` and follow `prev` `V` times. That is guaranteed to land on the cycle. Keep following `prev` until the node repeats to list the cycle.

**SPFA (queue-based).** Only an edge out of a node whose distance just changed can relax anything. So keep a queue of such nodes and relax only their outgoing edges, instead of all edges every round. On typical inputs this is much faster, but the worst case is still O(V · E). For negative cycle detection, count how many times each node is enqueued, and treat `V` or more as a cycle. SPFA does not respect an edge limit, because it does not process the graph in rounds.

## Choosing a shortest-path algorithm

| Situation | Algorithm | Time |
|---|---|---|
| Unweighted edges | BFS | O(V + E) |
| Weights 0 or 1 | 0-1 BFS with a deque | O(V + E) |
| Non-negative weights | Dijkstra | O((V + E) log V) |
| Negative weights, or negative cycle detection | Bellman-Ford | O(V · E) |
| At most `k` edges per path | Bellman-Ford, `k + 1` rounds with a copy, or BFS by level | O(k · E) |
| Every pair of nodes, small V | Floyd-Warshall | O(V³) |
| DAG, any weights | relax in topological order ([`topological_sort.md`](topological_sort.md)) | O(V + E) |

## How to spot it

- The edges can have **negative weights**: refunds, rewards, energy gained, or costs that can go down.
- The question asks whether a **negative cycle** exists, often phrased as an arbitrage loop or "can the cost become arbitrarily small".
- The path has a **hard limit on the number of edges**, stops, or transfers.
- The input is an **edge list**, and `V · E` is small: a few hundred nodes and a few thousand edges.

## Pitfalls

- **`INF + w` with negative weights.** With `dist[u] = INT_MAX` and `w = -3`, the sum is `INT_MAX - 3`, which is less than `INT_MAX`. An unreachable node then looks reachable, and the error spreads. Always check `dist[u] != INF` before relaxing.
- **Updating in place when the number of edges is limited.** One round chains several edges, as in the 787 trace above. Read from the previous round's copy.
- **`k` rounds instead of `k + 1`.** `k` stops means `k + 1` flights, and each round adds one flight.
- **Skipping the `V`-th round.** After `V - 1` rounds with a negative cycle, the distances look like ordinary numbers. Only the extra round shows that they are not final.
- **Early exit combined with the copy.** Set the `changed` flag when a write to `next` lowers a value. If no write in the round lowers anything, `next` equals `dist`, and every later round would be the same.
- **Reporting every distance as undefined when a negative cycle exists.** Only nodes reachable from the cycle are affected. Mark them as described above when the problem asks for per-node answers.
