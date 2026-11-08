# Eulerian Paths and Hierholzer's Algorithm

## What it solves

An **Eulerian path** uses **every edge of a graph exactly once**. An **Eulerian circuit** is an Eulerian path that ends where it started. Nodes can be visited any number of times. Only the edges are limited to one use each.

That one rule separates this problem from every other traversal in these docs. BFS, DFS, Dijkstra and topological sort mark *nodes* as visited and never enter a visited node twice. Here a node is entered once per incoming edge, and what gets used up is the edges. The classic picture is drawing a figure without lifting the pen and without tracing any line twice.

Typical problems:

- **Reconstruct Itinerary (332):** use every plane ticket once, starting from JFK.
- **Valid Arrangement of Pairs (2097):** order pairs `[a, b]` so each pair's `b` equals the next pair's `a`.
- **Cracking the Safe (753):** the shortest string containing every `n`-digit code. This is an Eulerian circuit on a graph whose edges are the codes, and its answer is called a de Bruijn sequence.

Do not confuse this with a **Hamiltonian path**, which visits every *node* exactly once. Hamiltonian path is NP-hard, and the only known exact algorithms are exponential ([`1c_p_np_nphard_npcomplete.md`](../01_foundations/1c_p_np_nphard_npcomplete.md)). Eulerian path runs in O(E).

## When one exists

Whether a path exists can be decided by counting degrees, before running any search. In every case, all edges must also be in one connected piece. Nodes with no edges at all can be ignored.

**Directed graphs.** Compare each node's out-degree with its in-degree:

| Situation | Result |
|---|---|
| every node has `out == in` | Eulerian **circuit**, start anywhere with an edge |
| exactly one node has `out = in + 1`, exactly one has `in = out + 1`, all others `out == in` | Eulerian **path** from the first node to the second |
| anything else | no Eulerian path |

**Undirected graphs.** Count the nodes with an odd degree:

| Odd-degree nodes | Result |
|---|---|
| 0 | circuit, start anywhere with an edge |
| 2 | path, which must start at one odd node and end at the other |
| any other number | none |

The reason: every time the path passes *through* a node, it uses one edge to arrive and one to leave. That keeps in-degree and out-degree balanced (or keeps the degree even). Only the first node can have one extra departure, and only the last node can have one extra arrival.

The same counts tell you where to start. In a directed graph with a path but no circuit, the start must be the node with `out = in + 1`. Starting anywhere else gets stuck before using all edges.

## Hierholzer's algorithm

Run a DFS from the start node. At each node, **remove** an unused edge and follow it. When a node has no unused edges left, append it to the output **after** its recursive calls return, which is post-order. At the end, reverse the output.

```cpp
void dfs(const string &u) {
  while (!adj[u].empty()) {
    string v = adj[u].back();
    adj[u].pop_back();          // use the edge: it can never be taken again
    dfs(v);
  }
  path.push_back(u);            // post-order: u has no unused edges left
}

// dfs(start); reverse(path.begin(), path.end());
```

The edge is removed from the adjacency list as it is taken. There is no `visited` array, because a node must stay enterable as long as it still has unused edges.

O(E) time: each edge is popped once, and each pop leads to one `dfs` call. The graph uses O(V + E) space, and the recursion is as deep as the path, up to E.

### Why post-order is correct

In a graph that has an Eulerian path, a walk that keeps taking unused edges can only get stuck at the **end node**. Every other node it enters has a spare outgoing edge, because arrivals and departures there balance.

The walk does reach the end node, but it may get there before using every edge. Some edges are left behind on nodes the walk already passed, forming **detours**: closed loops that start and end at the same node. Post-order puts these detours in the right place:

1. The first node appended is the dead end, which is the real end of the path.
2. The recursion then unwinds back along the walk. When it reaches a node that still has unused edges, the `while` loop continues from there. Because the degrees around that loop balance, it returns to the same node, and gets appended before that node does.
3. After reversing, each detour appears in the middle of the path, at the node where it starts and ends.

A plain pre-order DFS, which appends nodes on arrival, cannot do this. It would list the dead end in the middle of the path, followed by the detour, which is no longer reachable from where the path stopped.

### Trace: a detour

```
tickets: JFK→KUL   JFK→NRT   NRT→JFK

dfs(JFK)
  take JFK→KUL   dfs(KUL)
                   KUL has no edges        append KUL     ← dead end = real end
  take JFK→NRT   dfs(NRT)
                   take NRT→JFK   dfs(JFK)
                                    no edges left   append JFK
                   NRT has no edges left            append NRT
  JFK has no edges left                             append JFK

post-order: KUL JFK NRT JFK
reversed:   JFK NRT JFK KUL
```

The walk went to KUL first and got stuck there. The unused loop `JFK → NRT → JFK` was then found while unwinding and placed before the final step to KUL. A greedy walk that just follows the smallest destination and stops when stuck would return `JFK KUL` and leave two tickets unused.

### Iterative version

The recursion depth can reach E. With 10⁵ edges, that overflows Python's default recursion limit, and possibly a native stack. An explicit stack gives the same order:

```cpp
vector<string> st = {start};
while (!st.empty()) {
  string u = st.back();
  if (!adj[u].empty()) {        // an unused edge: follow it
    st.push_back(adj[u].back());
    adj[u].pop_back();
  } else {                      // stuck: u is finished
    path.push_back(u);
    st.pop_back();
  }
}
// reverse(path.begin(), path.end());
```

## Worked example: Reconstruct Itinerary (332)

Every ticket `[from, to]` is a directed edge. The trip starts at JFK and uses every ticket once, and the input guarantees such a trip exists. When several valid trips exist, return the lexicographically smallest one.

The lexicographic rule changes only one thing: at every node, **take the smallest destination first**. Keep each node's destinations in a min-heap, or sort each list in descending order and pop from the back.

```
tickets: JFK→SFO  JFK→ATL  SFO→ATL  ATL→JFK  ATL→SFO

adjacency, smallest first:
  JFK: ATL, SFO     SFO: ATL     ATL: JFK, SFO

dfs(JFK) → ATL → JFK → SFO → ATL → SFO, then stuck at SFO

post-order: SFO ATL SFO JFK ATL JFK
reversed:   JFK ATL JFK SFO ATL SFO
```

This walk used every edge without getting stuck early, so there are no detours. The KUL trace above is the case where taking the smallest destination leads into a dead end too soon. Post-order still produces the correct answer there, and it is the smallest valid one: wherever a smaller destination was taken, it either belongs at that point in the trip, or it was the dead end and post-order moves it to the end.

The same airport can appear on several tickets, such as two tickets `JFK→ATL`. Store destinations in a list or a heap, which keep duplicates, not in a set, which would drop the second ticket.

## Undirected graphs

In an undirected graph, edge `{u, v}` is stored twice: in `adj[u]` and in `adj[v]`. Using it from one side must also remove it from the other, or the walk takes it again in the opposite direction. The standard fix is to give every edge an id and keep a `used` array:

```cpp
// adj[u] holds {v, edgeId}
void dfs(int u) {
  while (!adj[u].empty()) {
    auto [v, id] = adj[u].back();
    adj[u].pop_back();
    if (used[id]) continue;     // already taken from v's side
    used[id] = true;
    dfs(v);
  }
  path.push_back(u);
}
```

## How to spot it

- The problem asks you to use **every edge, ticket, domino, or pair exactly once**, in one continuous chain.
- Consecutive items must **share an endpoint**: the end of one is the start of the next.
- A string or sequence must contain **every combination exactly once**, with overlaps (de Bruijn).
- The question asks whether a figure can be drawn **without lifting the pen**, which only needs the degree check.

## When it's the wrong tool

- **Every node once, not every edge.** That is a Hamiltonian path, which is NP-hard. For small n, roughly n ≤ 16, use bitmask DP or backtracking.
- **A path between two nodes, not through all edges.** Use BFS or Dijkstra.
- **A dependency order.** That is topological sort ([`7b_topological_sort.md`](7b_topological_sort.md)). It shares the post-order-then-reverse step, but it visits each node once and never uses edges up.

## Pitfalls

- **Marking nodes as visited.** A node has to be entered once per incoming edge. With a `visited` array the walk stops early and leaves edges unused. Remove edges instead.
- **Appending nodes on arrival instead of on finish.** Pre-order lists the dead end in the middle of the path. Append after the `while` loop, then reverse.
- **Starting from the wrong node.** In a directed graph with a path but no circuit, start at the node with `out = in + 1`. In an undirected graph, start at an odd-degree node.
- **Skipping the existence check** when the input does not guarantee a path. Check the degrees and connectivity first, or check that the output has `E + 1` nodes.
- **A set of destinations.** Repeated tickets, pairs or dominoes are separate edges. A set keeps only one of them.
- **Removing an undirected edge from one side only.** The walk crosses it again in the other direction.
- **Recursion depth.** The path can be E nodes long. Use the iterative stack version for large inputs.
