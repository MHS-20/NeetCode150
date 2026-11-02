# Minimum Spanning Tree: Prim and Kruskal

## What it solves

A **spanning tree** of a connected, undirected graph is a subset of its edges that connects every node and contains no cycle. On `V` nodes it always has exactly `V - 1` edges. A **minimum spanning tree (MST)** is a spanning tree whose total edge weight is as small as possible.

Read it as "connect everything at the lowest total cost": lay cable between buildings, pave roads between towns, link points on a plane. Every node has to be reachable from every other, but nobody cares how long any individual route is. That last part separates it from shortest paths (see "MST and shortest paths" below).

```
edges:  0-1 (1)  1-2 (2)  0-2 (3)  2-3 (4)  1-3 (5)  3-4 (6)  2-4 (7)

MST:    0 ─1─ 1 ─2─ 2 ─4─ 3 ─6─ 4        total 1 + 2 + 4 + 6 = 13

left out: 0-2 (3), 1-3 (5), 2-4 (7) — each would close a cycle
          of cheaper edges already in the tree
```

When all edge weights are distinct, the MST is unique. With ties, there can be several MSTs, all with the same total weight.

## Why greedy works

Both algorithms add edges greedily and never undo a choice. Two properties make that safe.

**Cut property.** Split the nodes into any two non-empty groups. The cheapest edge crossing between the groups belongs to some MST. If an MST left it out, adding it would create a cycle, and that cycle must cross the split a second time through some other edge. Swapping that other edge out for the cheaper one keeps the tree spanning and does not increase its weight.

**Cycle property.** On any cycle, the most expensive edge is not needed. Removing it leaves the nodes connected through the rest of the cycle.

Both algorithms keep choosing a split and taking the cheapest edge across it. They differ in which split they choose. The examples below use the graph above.

**Prim's split: the tree built so far, versus every other node.** Suppose the tree so far is `{0, 1}`:

```
group A (tree): {0, 1}        group B (rest): {2, 3, 4}

edges crossing A–B:  1-2 (2)   0-2 (3)   1-3 (5)
cheapest: 1-2 (2)  → safe, add it
```

Prim's heap holds the edges leaving the tree, so popping the minimum picks the cheapest crossing edge. Every step is the cut property applied to "tree versus rest".

**Kruskal's split: one endpoint's component, versus everything else.** Kruskal walks the edges in weight order, and its pieces are separate components rather than a single tree. When it reaches `2-3 (4)`, the components are `{0, 1, 2}`, `{3}` and `{4}`. Split the nodes into "the component containing 2" and the rest:

```
group A: {0, 1, 2}        group B: {3, 4}

edges crossing A–B:  2-3 (4)   1-3 (5)   2-4 (7)
```

Every cheaper edge has already been processed: it either joined two components or was skipped. So `2-3` is the cheapest edge crossing this split, and the cut property says it is safe.

**Kruskal's rejections are the cycle property.** When Kruskal reaches `0-2 (3)`, nodes 0 and 2 are already connected through `0-1 (1)` and `1-2 (2)`. Adding `0-2` would close the cycle `0-1-2-0`, and as the last edge reached in weight order, it is the most expensive edge on that cycle. The cycle property says such an edge is never needed. The Union-Find check "same component, skip" applies exactly this rule.

In short:

- **Prim** always splits "my tree / the rest" and takes the cheapest edge leaving the tree.
- **Kruskal** goes through the edges cheapest-first. It keeps an edge that joins two separate components (cut property) and drops an edge that would close a cycle, since that edge is the most expensive one on the cycle (cycle property).

## Kruskal: sort the edges, join components

1. Sort all edges by weight, ascending.
2. Walk them in order. For edge `(u, v)`, if `u` and `v` are in different components, keep the edge and merge the components. Otherwise skip it, because it would close a cycle.
3. Stop after keeping `V - 1` edges.

The "different components" test and the merge are exactly what Union-Find provides (`union_find.md`).

```
sorted:  0-1(1)  1-2(2)  0-2(3)  2-3(4)  1-3(5)  3-4(6)  2-4(7)

0-1 (1)   different → keep    {0,1} {2} {3} {4}
1-2 (2)   different → keep    {0,1,2} {3} {4}
0-2 (3)   same      → skip
2-3 (4)   different → keep    {0,1,2,3} {4}
1-3 (5)   same      → skip
3-4 (6)   different → keep    {0,1,2,3,4}       4 edges = V - 1, stop
```

```cpp
// edges: {w, u, v}
long long kruskal(int n, vector<array<int,3>> &edges) {
  sort(edges.begin(), edges.end());
  DSU dsu(n);                                  // template in union_find.md
  long long total = 0;
  int used = 0;
  for (auto [w, u, v] : edges) {
    if (!dsu.unite(u, v)) continue;            // would close a cycle
    total += w;
    if (++used == n - 1) break;
  }
  return used == n - 1 ? total : -1;           // -1: graph not connected
}
```

**O(E log E)** for the sort. The Union-Find work is O(E · α(V)) and does not change the bound. Kruskal takes the input as a plain edge list and never needs an adjacency list.

## Prim: grow one tree from a start node

1. Start with any one node in the tree.
2. Push every edge leaving it into a min-heap keyed by **edge weight**.
3. Pop the cheapest edge. If its far end is already in the tree, skip it. Otherwise add that node, add the edge's weight to the total, and push the new node's edges to nodes outside the tree.
4. Stop when all `V` nodes are in the tree.

```
start at 0                                    heap (weight, node)
pop (1,1)   add 1   push 1-2(2) 1-3(5)        (2,2) (3,2) (5,3)
pop (2,2)   add 2   push 2-3(4) 2-4(7)        (3,2) (4,3) (5,3) (7,4)
pop (3,2)   2 already in tree → skip
pop (4,3)   add 3   push 3-4(6)               (5,3) (6,4) (7,4)
pop (5,3)   3 already in tree → skip
pop (6,4)   add 4                             all 5 nodes in, stop

total = 1 + 2 + 4 + 6 = 13
```

Both algorithms pick the same four edges here, because the weights are distinct and the MST is unique. They pick them in a different order.

```cpp
long long prim(int n, vector<vector<pair<int,int>>> &adj) {   // adj[u] = {v, w}
  vector<bool> inTree(n, false);
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;  // {w, node}
  pq.push({0, 0});
  long long total = 0;
  int added = 0;
  while (!pq.empty() && added < n) {
    auto [w, u] = pq.top(); pq.pop();
    if (inTree[u]) continue;                   // reached more cheaply already
    inTree[u] = true;
    total += w;
    added++;
    for (auto [v, wt] : adj[u])
      if (!inTree[v]) pq.push({wt, v});
  }
  return added == n ? total : -1;              // -1: graph not connected
}
```

**O(E log V)** with the heap. The adjacency list must contain each undirected edge in both directions, or some nodes become unreachable from the start.

### Prim on a dense graph: O(V²) with no heap

When almost every pair of nodes is connected, E is close to V²/2, and the heap only adds overhead. Keep `best[v]`, the cheapest edge from the tree to `v`. At each step, scan for the cheapest node outside the tree, add it, and update `best` for its neighbours. That is V scans of O(V) each, **O(V²)** in total, with no heap and no edge list.

## Worked example: Min Cost to Connect All Points (1584)

Given up to 1000 points on a plane, connect them all at minimum total cost. Connecting points `i` and `j` costs their Manhattan distance, `|xi - xj| + |yi - yj|`.

Every pair of points can be connected, so the graph is complete: about 500,000 edges for 1000 points. Both algorithms are correct here, but they cost different amounts:

| Algorithm | Work | Memory |
|---|---|---|
| Kruskal | build and sort ~500k edges, O(E log E) | O(E) edge list |
| Prim with heap | O(E log V), up to E heap entries | O(E) heap |
| Prim, dense O(V²) | 10⁶ steps | O(V), compute each distance on the fly |

The dense version never stores an edge. It computes `dist(u, v)` from the coordinates when it needs it:

```cpp
int minCostConnectPoints(vector<vector<int>> &points) {
  int n = points.size();
  vector<int> best(n, INT_MAX);                // cheapest edge from tree to v
  vector<bool> inTree(n, false);
  best[0] = 0;
  int total = 0;
  for (int step = 0; step < n; step++) {
    int u = -1;
    for (int v = 0; v < n; v++)                // cheapest node outside the tree
      if (!inTree[v] && (u == -1 || best[v] < best[u])) u = v;
    inTree[u] = true;
    total += best[u];
    for (int v = 0; v < n; v++)
      if (!inTree[v]) {
        int d = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
        best[v] = min(best[v], d);
      }
  }
  return total;
}
```

## Kruskal or Prim

- **Kruskal** when the input is an **edge list**, the graph is **sparse**, or you are already using Union-Find. It is also the natural choice when edges need special handling during the sweep, for example forcing one edge in first, or finding the critical edges whose removal raises the MST weight (1489).
- **Prim** when the input is an **adjacency list** or the graph is **dense** or complete. The O(V²) array version is the standard answer for "connect all points" problems.
- On sparse graphs, both are O(E log V), since `log E ≤ 2 log V`. Pick whichever matches the input format.

## MST and shortest paths

Prim's loop is Dijkstra's loop with a different heap key (`dijkstra.md`). Dijkstra pushes `dist[u] + w`, the total distance from the source. Prim pushes `w`, the cost of the single edge that attaches `v` to the tree.

The two produce different trees:

```
0-1 (2)   1-2 (2)   0-2 (3)

MST:                    0-1, 1-2      total 4
shortest paths from 0:  0-1, 0-2      dist[2] = 3, not 4
```

The MST minimises the total weight of the tree. The path from 0 to 2 inside it costs 4, more than the direct edge. A shortest-path tree minimises each node's distance from one source, and its total weight can be higher.

**Bottleneck paths.** Between any two nodes, the path through the MST minimises the *largest* edge on the path, over every possible path. So "find a route whose worst edge is as small as possible" can be answered with an MST. It can also be answered by processing edges in Kruskal order until the two nodes join, or with minimax Dijkstra (problems 1631 and 778 in `dijkstra.md`).

## How to spot it

- **"Connect all X at minimum total cost"**: cables, roads, pipes, or points on a plane.
- The answer is **one number, the total weight**, and every node must be reachable, but individual distances do not matter.
- The graph is **undirected** and weighted.
- Variants ask for the **maximum** spanning tree (sort descending, or negate the weights), or for the minimum-cost way to connect once some edges are already fixed (start the Union-Find with those edges merged).

## When it's the wrong tool

- **Directed graphs.** An MST is defined for undirected graphs. The directed version, a minimum spanning arborescence, needs Edmonds' (Chu-Liu) algorithm, and Prim or Kruskal give wrong answers.
- **Shortest routes between specific nodes.** Use Dijkstra. The MST path between two nodes can be much longer than the shortest path, as in the 0-1-2 example above.
- **Connecting only some of the nodes.** Connecting a chosen subset at minimum cost, possibly through other nodes, is the Steiner tree problem, which is NP-hard. An MST over the whole graph spends edges on nodes that do not need connecting.

## Pitfalls

- **Prim with Dijkstra's key.** Pushing `dist[u] + w` instead of `w` builds a shortest-path tree, and the total comes out too high.
- **Marking a node in the tree when it is pushed.** A node's first push may not be its cheapest connecting edge. Mark it on pop, exactly as in Dijkstra.
- **Adding undirected edges in one direction only.** Kruskal does not care, but Prim cannot reach nodes whose only edges point inward.
- **Not checking connectivity.** If the graph is disconnected, Kruskal finishes with fewer than `V - 1` edges and Prim with fewer than `V` nodes. Both return a minimum spanning *forest* instead of a tree. Check the count and return `-1`, or whatever the problem asks for.
- **Overflow in the total.** `V - 1` edges with weights near 10⁹ exceed 32-bit `int`. Use `long long` for the sum.
- **Building every edge of a complete graph when the dense version is enough.** It works, but memory goes to O(V²) for no gain.
