# Topological Sort

## What it is

A topological order of a directed graph is a list of its nodes in which **every edge points forward**: for each edge `u → v`, `u` comes before `v`. Read an edge as "u must happen before v" and the order is a valid schedule. Courses before the courses that need them, build targets before the targets that link them, letters before the letters that sort after them.

```
edges:  shirt → tie,  tie → jacket,  pants → shoes,  pants → jacket

valid orders:   shirt  pants  tie  shoes  jacket
                pants  shoes  shirt  tie  jacket
                ...
```

- **An order exists exactly when the graph has no directed cycle** (it is a DAG). If `a → b → c → a`, each of the three would have to come before the next, which is impossible. Both algorithms below detect this as part of the sort, so "is there a valid order?" and "is the graph acyclic?" are the same question.
- **The order is usually not unique.** Any two nodes with no path between them can go in either order. A problem that accepts "any valid order" is fine with whatever the algorithm emits. A problem that wants the *lexicographically smallest* order, or asks whether the order is *unique*, needs an extra rule (see the end of the Kahn section).

## Kahn's algorithm (BFS)

The **in-degree** of a node is the number of edges pointing into it: how many things must happen before it. A node with in-degree 0 has nothing left blocking it and can go next.

1. Count every node's in-degree.
2. Put every node with in-degree 0 in a queue.
3. Pop a node, append it to the output, and "remove" its outgoing edges by decrementing each neighbour's in-degree. A neighbour that drops to 0 joins the queue.
4. When the queue is empty, the output holds every node **if and only if** the graph is acyclic.

```
edges: 0 → 1,  0 → 2,  1 → 3,  2 → 3

in-degree:  0:0  1:1  2:1  3:2

queue [0]       pop 0 → out [0]           1:0 → push, 2:0 → push
queue [1, 2]    pop 1 → out [0,1]         3:1
queue [2]       pop 2 → out [0,1,2]       3:0 → push
queue [3]       pop 3 → out [0,1,2,3]
```

Nodes on a cycle never reach in-degree 0, because each of them is waiting on another member of the cycle. They never enter the queue, so the output comes up short. That shortfall is the cycle check: `out.size() < V` means a cycle exists.

```cpp
vector<int> topoSort(int n, vector<vector<int>> &adj) {
  vector<int> indeg(n, 0);
  for (int u = 0; u < n; u++)
    for (int v : adj[u]) indeg[v]++;

  queue<int> q;
  for (int u = 0; u < n; u++)
    if (indeg[u] == 0) q.push(u);

  vector<int> out;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    out.push_back(u);
    for (int v : adj[u])
      if (--indeg[v] == 0) q.push(v);
  }
  return out.size() == n ? out : vector<int>{};  // empty → cycle
}
```

O(V + E): every node is pushed and popped once, every edge decrements one counter once.

**Variants on the queue.**

- **Lexicographically smallest order:** replace the queue with a min-heap. Whenever several nodes are free at once, the smallest goes first. O((V + E) log V).
- **Is the order unique?** It is unique exactly when the queue never holds more than one node. Two free nodes at once means either could go first.
- **Fewest rounds / parallel scheduling:** pop the queue level by level, as in multi-source BFS. Each level is a set of tasks that can run at the same time, and the number of levels is the minimum number of rounds (Parallel Courses, 1136).

## DFS post-order

Run a DFS. **Append a node to the output when its recursion finishes**, after everything reachable from it has been appended. For an edge `u → v`, `v` is always finished before `u`, so the output lists every edge backwards. Reverse it to get the topological order.

Cycle detection needs **three states** rather than a plain visited flag:

| State | Meaning |
|---|---|
| 0, unvisited | not reached yet |
| 1, on the path | the recursion is currently inside this node |
| 2, done | this node and everything below it is finished |

Reaching a node in state 1 means following an edge back into the current recursion path, which is a cycle. Reaching a node in state 2 is harmless: it was finished from another branch and is already in the output.

```
edges: 0 → 1,  0 → 2,  1 → 3,  2 → 3

dfs(0)
  dfs(1)
    dfs(3)        finish 3     post = [3]
  finish 1                     post = [3, 1]
  dfs(2)
    3 is done → skip
  finish 2                     post = [3, 1, 2]
finish 0                       post = [3, 1, 2, 0]

reversed:  0 2 1 3
```

A two-state visited flag cannot tell these two cases apart. In the example, node 3 is reached a second time from 2, which is fine. In `0 → 1 → 0`, node 0 is reached a second time from 1, which is a cycle. Both look the same with a single `visited` bit.

O(V + E). The recursion is as deep as the longest path. A chain of 10⁵ prerequisites overflows Python's default recursion limit, and can overflow a C++ stack at a few hundred thousand frames. Kahn's has no recursion at all.

### Edge direction decides whether to reverse

Course Schedule II (210) gives `[a, b]` meaning "b before a". If the adjacency list stores `a → b` (course → its prerequisite), every edge already points backwards. DFS post-order then finishes the prerequisites first, and the post-order list *is* the answer, with no reversal. If it stores `b → a` (prerequisite → course), the post-order must be reversed.

Getting this wrong produces an order that is exactly backwards, and it looks plausible. Decide once what an edge means, write it as a comment next to where the adjacency list is built, and check that the first element of the output has no prerequisites.

## Kahn's or DFS

Both are O(V + E) and both detect cycles. Pick by what else the problem needs:

- **Kahn's** when you want an iterative solution without recursion depth limits, a lexicographic or level-by-level order, or a uniqueness check. Its cycle check is a single comparison at the end.
- **DFS** when the graph is already being explored by DFS for another reason, or when only the cycle check is needed and the recursion depth is small. Course Schedule (207) needs only "is there a cycle?", and either algorithm answers it.

## Worked example: Alien Dictionary (269)

A list of words is sorted according to an unknown alphabet. Recover an order of the letters, or return `""` if none exists.

The topological sort itself is easy. The work is in **building the graph**, which the problem does not give you.

Compare each pair of *adjacent* words. The first position where they differ gives one edge: the letter in the earlier word comes before the letter in the later word. Everything after that position carries no information, since the words are already ordered by that first difference.

```
words: wrt  wrf  er  ett  rftt

wrt  / wrf     first difference t, f   →  t → f
wrf  / er      first difference w, e   →  w → e
er   / ett     first difference r, t   →  r → t
ett  / rftt    first difference e, r   →  e → r

graph: w → e → r → t → f
order: wertf
```

Rules for building the graph:

- **Only adjacent pairs are needed.** Sorted order is transitive, so comparing `words[i]` with `words[i+1]` already implies every non-adjacent relation.
- **A longer word before its own prefix is invalid.** `abc` before `ab` contradicts every alphabet, because a prefix always sorts first. No edge describes this case, so it must be checked explicitly and return `""`.
- **Every letter that appears belongs in the output**, including letters that never appear in an edge. Register all of them before the sort, give them in-degree 0, and compare the output length with the number of distinct letters, not with 26.

Two pairs of words can produce the same edge `u → v`. Count it the same number of times in both places:

- **Adjacency list with duplicates:** the edge is stored twice and `v`'s in-degree is incremented twice. Kahn's decrements once per stored edge, so `v` still reaches 0.
- **26 × 26 boolean matrix:** the edge is stored once. Increment the in-degree only when the matrix entry goes from `false` to `true`. Incrementing on every occurrence leaves `v` stuck at 1, and the sort reports a cycle that does not exist.

## How to spot it

- The problem lists **dependencies, prerequisites, or "must come before"** relations, and asks for an order, or asks whether an order exists.
- The input is **pairs `(a, b)` with a direction**: build systems, task scheduling, course plans, package installation.
- An ordering must be **inferred from sorted examples**, as in Alien Dictionary or reconstructing a sequence from subsequences (444).
- The question is **"can all of these finish?"**, which is cycle detection in a directed graph.
- **DP on a DAG.** Longest path, number of paths, or earliest finish time in a dependency graph are computed by processing nodes in topological order, so that every predecessor's value is final before its successors use it.

## When it's the wrong tool

- **Undirected graphs.** There is no "before" to order by. For cycles or connectivity in undirected graphs, use DFS with a parent check or Union-Find ([`union_find.md`](union_find.md)).
- **Graphs that are known to contain cycles**, where the cycle is part of the answer rather than a failure. Strongly connected components (Tarjan's or Kosaraju's) group the cycles first, and the resulting graph of components is a DAG that can then be sorted.
- **Shortest paths with weights in a general graph.** Topological order gives O(V + E) shortest paths only in a DAG. Elsewhere, use Dijkstra or Bellman-Ford.

## Pitfalls

- **Reversed edge direction.** `[a, b]` meaning "b before a" stored as `a → b` is the most common bug, and it yields an exactly reversed answer. See the section on edge direction above.
- **Forgetting nodes with no edges.** Isolated nodes have in-degree 0 and must be in the output. Build in-degree for all `V` nodes, not only the ones that appear in an edge.
- **Starting the DFS from one node only.** A topological sort needs the outer loop over every node, or nodes unreachable from the start are missing.
- **Two-state DFS for cycle detection.** A single visited bit reports a cycle wherever two paths meet at the same node, such as the diamond in the DFS example. Use three states.
- **Skipping the length check in Kahn's.** Without `out.size() == V`, a graph with a cycle returns a partial order that looks valid.
- **Counting a duplicate edge more times in the in-degree than in the edge storage.** The node's in-degree never reaches 0, and the sort reports a cycle that does not exist.
