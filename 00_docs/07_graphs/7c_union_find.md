# Union-Find

## What it is

Union-Find, also called Disjoint Set Union (DSU), keeps track of how a set of elements is split into **non-overlapping groups**. It supports two operations:

- **find(x)** returns the group x belongs to, as one representative element of that group (the root).
- **union(x, y)** merges x's group with y's group.

Two elements are in the same group exactly when `find(x) == find(y)`. That is all it answers. It does not store edges, paths or distances. It stores group membership, and it updates that membership in near-constant time each time two groups merge.

## How it works

Each group is a tree stored in a single `parent` array:

- Every element points to a parent. A root points to itself.
- **find** follows parent pointers up to the root.
- **union** finds both roots and points one at the other.

```
groups {0, 1, 2}  {3, 4}  {5}

parent: [0, 0, 1, 3, 3, 5]
index:   0  1  2  3  4  5

    0         3      5
    |         |
    1         4
    |
    2

find(2): 2 → 1 → 0      root 0
find(4): 4 → 3          root 3
union(2, 4): parent[3] = 0  →  {0, 1, 2, 3, 4}  {5}
```

A union only rewrites one entry, the root of one tree. Every element below that root changes group automatically, because its find now walks one step further and ends at the new root.

### Why the naive version degrades

Without any balancing, the shape of the trees depends on the order of the unions, and a bad order produces a chain. Take nodes 1..5 and process the edges `(4,5), (3,4), (2,3), (1,2)`, attaching the second root under the first:

```
union(4,5): parent[5] = 4
union(3,4): parent[4] = 3
union(2,3): parent[3] = 2
union(1,2): parent[2] = 1

1 ← 2 ← 3 ← 4 ← 5        find(5) walks 4 steps
```

With `n` nodes, the chain makes find O(n), and processing `n` edges becomes O(n²). On small inputs this goes unnoticed. On 10⁵ nodes in a line it times out.

### The two optimisations

**Union by size (or rank).** Attach the root of the smaller tree under the root of the larger one. A node only gets deeper when its tree is merged into one at least as large, so every time its depth grows by 1, the size of its group at least doubles. A group can only double `log₂ n` times, so no tree is ever taller than `log₂ n`. Rank works the same way using an upper bound on tree height instead of the element count. Size is simpler, and it doubles as the "how big is this group" answer.

**Path compression.** During a find, point every node visited directly at the root. The next find from any of them takes one step. The tree flattens as a side effect of being queried.

```
before find(5):   1 ← 2 ← 3 ← 4 ← 5
after  find(5):   1 ← 2,  1 ← 3,  1 ← 4,  1 ← 5
```

Each optimisation on its own gives O(log n) amortised per operation. Together they give **O(α(n))** amortised, where α is the inverse Ackermann function. α(n) is at most 4 for any n that fits in memory, so in practice each operation is constant time ([`1a_complexity_analysis.md`](../01_foundations/1a_complexity_analysis.md)).

### Template

```cpp
class DSU {
  vector<int> parent, size;

public:
  int components;

  DSU(int n) : parent(n), size(n, 1), components(n) {
    iota(parent.begin(), parent.end(), 0);  // every node is its own root
  }

  int find(int x) {
    while (parent[x] != x) {
      parent[x] = parent[parent[x]];        // path halving
      x = parent[x];
    }
    return x;
  }

  bool unite(int a, int b) {                // false if already connected
    a = find(a), b = find(b);
    if (a == b) return false;
    if (size[a] < size[b]) swap(a, b);
    parent[b] = a;                          // smaller under larger
    size[a] += size[b];
    components--;
    return true;
  }
};
```

`parent[x] = parent[parent[x]]` is **path halving**. Each visited node skips to its grandparent, which halves the path on every find without recursion or a second pass, and keeps the same O(α(n)) bound as full path compression. The recursive form, `return parent[x] = find(parent[x]);`, compresses the path fully but uses one stack frame per level. On a long chain that has not been compressed yet, that can overflow the stack.

Two return values cover most problems. `unite` returning `false` means the edge connected two nodes already in the same group, which is the cycle signal. `components` starts at `n` and drops by one on each successful union, so the component count is available at every step without another pass.

## Worked examples

### Redundant Connection (684)

A tree on nodes `1..n` has one extra edge added. Return the edge that, if removed, leaves a tree. When there are several candidates, return the one that appears last in the input.

Process the edges in input order and union each pair of endpoints. The first edge whose endpoints already share a root closes a cycle, because a path between them already exists through earlier edges. That edge is the answer, and since every edge before it was cycle-free, it is also the last edge of that cycle in input order.

```
edges: [1,2] [1,3] [2,3]

[1,2]  find(1)=1, find(2)=2   different → union     {1,2} {3}
[1,3]  find(1)=1, find(3)=3   different → union     {1,2,3}
[2,3]  find(2)=1, find(3)=1   same root → return [2,3]
```

A DFS solution has to search for a path between `u` and `v` before adding each edge, which is O(n) per edge and O(n²) overall. Union-Find answers the same question in O(α(n)) per edge.

### Number of Connected Components (323)

Start with `n` components, one per node. Each union that merges two different roots reduces the count by one. Unions on nodes that are already connected change nothing. The answer is the count after the last edge, O(E · α(n)) overall.

DFS from every unvisited node gives the same O(V + E) result. Union-Find wins only when edges arrive over time and the count is needed after each one, as in Number of Islands II, where land cells are added one at a time.

### Graph Valid Tree (261)

An undirected graph on `n` nodes is a tree exactly when it is connected and has no cycle. Union-Find checks both in one pass:

- any `unite` that returns `false` means a cycle, so return `false` immediately;
- after all edges, the graph is connected only if `components == 1`.

There is also a shortcut. A tree on `n` nodes has exactly `n - 1` edges. If `edges.size() != n - 1`, return `false` before doing any unions. With exactly `n - 1` edges, "no cycle" and "connected" are equivalent, so checking either one is enough.

### Kruskal's minimum spanning tree

Sort the edges by weight. Walk them in ascending order and keep an edge only if `unite(u, v)` succeeds, meaning it joins two components that were still separate. Stop after keeping `V - 1` edges. The sort costs O(E log E), and the unions together cost O(E · α(V)), so the sort dominates. Min Cost to Connect All Points (1584) is this algorithm on a complete graph, with Manhattan distances as weights.

## Elements that are not integers

The array template assumes elements numbered `0..n-1`. Other inputs need a mapping first:

- **Grid cells**: cell `(r, c)` becomes `r * cols + c`. Number of Islands can use this, unioning each land cell with its land neighbours to the right and below.
- **Strings or other keys**: give each new key the next integer from a hash map, or use a `unordered_map<string, string> parent` directly. Accounts Merge (721) unions every email in an account with that account's first email. Each resulting group is then one person.
- **Equality constraints**: Satisfiability of Equality Equations (990) unions the two variables of every `a==b` equation in a first pass. A second pass checks every `a!=b` equation, and the input is unsatisfiable if `find(a) == find(b)` for any of them. The two passes are required. Checking the `!=` equations as they arrive gives wrong answers, because a later `==` can still merge their groups.

A variant stores a weight on each parent edge, the element's value relative to its parent. Evaluate Division (399) uses this to answer `a / b` from `find`, by multiplying the weights along each path to the root.

## How to spot it

Union-Find is a good candidate when:

- **The problem is about groups or connectivity**: "are these two connected?", "how many groups are there?", "how big is the largest group?" The size array answers the last one directly.
- **Connections are only ever added**, never removed. Union-Find can merge groups but cannot split them.
- **Connections arrive one at a time** and an answer is needed after each, as in Redundant Connection: "does this edge join two nodes that were already connected?"
- **The relation is symmetric and transitive**: if a ~ b and b ~ c, then a ~ c. Friend circles, accounts sharing an email and chains of equal variables all have this shape.
- **Undirected cycle detection** and **Kruskal's MST**.

## When it's the wrong tool

- **Directed relationships.** In Course Schedule (207), `a` depending on `b` does not mean `b` depends on `a`. Union-Find puts both in one group and loses the direction. A graph `0 → 1, 0 → 2, 1 → 2` has no cycle, but Union-Find reports the third edge as one, because 1 and 2 are already in the same group. Use DFS with three colours or Kahn's topological sort instead ([`7a_graphs_bfs_dfs.md`](7a_graphs_bfs_dfs.md)).
- **Deleting edges or splitting groups.** No operation undoes a union. If all deletions are known in advance, process the operations in reverse: deletions become additions, and Union-Find applies again.
- **Needing the actual path** between two nodes, or its length. Union-Find only says whether a path exists. For the shortest path, use BFS, or Dijkstra when the edges are weighted.
- **A single static question about a graph whose edges are all known in advance.** For example, "how many components?" with no updates. DFS or BFS is O(V + E), just as fast, and needs no extra structure.

## Pitfalls

- **Assigning `parent[a] = b` instead of `parent[find(a)] = find(b)`.** That re-parents `a` alone and splits it from the rest of its old tree. Union always links roots.
- **Comparing `parent[a] == parent[b]` instead of `find(a) == find(b)`.** Parents are only guaranteed equal right after compression. Two nodes in the same group can have different parents and the same root.
- **Skipping both optimisations.** The code is still correct, but find becomes O(n) on chain-shaped inputs, as in the naive example above. Small tests pass and large ones time out.
- **Initialising the wrong index range.** Nodes labelled `1..n` need `parent` of size `n + 1` with `parent[i] = i` for `i` in `1..n`. Nodes labelled `0..n-1` need `0..n-1`. If any node is never initialised, it points at whatever the array held, often 0, and silently joins node 0's group.
- **Decrementing the component count on every edge.** Only a union that merges two different roots reduces the count.
- **Recursive find on deep trees.** Before compression has flattened anything, a chain of 10⁵ nodes means 10⁵ nested calls. Use the iterative path-halving loop.
