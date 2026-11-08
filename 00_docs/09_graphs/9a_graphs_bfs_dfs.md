# Graphs, BFS and DFS

## What a graph is, and how it's stored

Nodes (vertices, `V`) connected by edges (`E`). A tree is a graph with no cycles and exactly `V − 1` edges; everything in [`7a_binary_trees.md`](../07_trees/7a_binary_trees.md) is the special case where each node has at most two neighbours and there is no way to revisit a node.

Edges may be **directed** (one-way) or **undirected**, **weighted** or not. Those two axes decide which algorithm applies, so establish them before writing anything.

### Adjacency list — the default

```python
graph = {0: [1, 2], 1: [2], 2: [0], 3: []}
```

```
0 ──→ 1
│ ↖   │
↓   ╲ ↓
2 ────┘        3  (isolated)
```

Space O(V + E). Listing a node's neighbours is O(degree). This is the right representation for essentially every interview problem, because real graphs are sparse.

### Adjacency matrix

```
     0  1  2  3
 0 [ 0  1  1  0 ]
 1 [ 0  0  1  0 ]
 2 [ 1  0  0  0 ]
 3 [ 0  0  0  0 ]
```

Space O(V²). Checking "is there an edge u→v" is O(1), but listing a node's neighbours costs O(V) even if it has one. Worth it only when the graph is dense or when edge lookups dominate.

### Edge list

`[(0,1), (0,2), (1,2), (2,0)]`. Useless for traversal, but it is the input format problems usually hand you, and it is what Kruskal's algorithm and union-find consume directly. Converting an edge list to an adjacency list is the standard first three lines:

```python
from collections import defaultdict
graph = defaultdict(list)
for u, v in edges:
    graph[u].append(v)
    graph[v].append(u)      # omit this line for a directed graph
```

## Complexity: O(V + E), and why it isn't O(V·E)

Both traversals visit each node once and examine each edge once (twice for undirected, once from each end). So

> **BFS = DFS = O(V + E) time, O(V) space**

The `V` term covers nodes with no edges; the `E` term covers the neighbour scanning. Writing O(E) alone is wrong because isolated nodes still cost a visit. With an adjacency *matrix* both become O(V²), since finding neighbours is a full row scan.

For a grid of `R × C` cells, `V = R·C` and each cell has at most 4 edges, so `E ≤ 4·R·C` and the traversal is **O(R·C)** — the constant 4 vanishes.

The `visited` set is what makes this linear rather than infinite. A graph has cycles; without marking, traversal loops forever. Mark a node when you *enqueue* it in BFS, not when you dequeue it, or the same node gets added by several neighbours and the queue grows quadratically.

## DFS — go deep

Follow one path as far as it goes, then back up and try the next branch.

```
        0
       / \        DFS from 0:  0 → 1 → 3 → 4 → 2
      1   2       (fully explores 1's subtree before touching 2)
     / \
    3   4
```

```python
def dfs(node, seen):
    seen.add(node)
    for nxt in graph[node]:
        if nxt not in seen:
            dfs(nxt, seen)
```

Recursive is the natural form; the call stack *is* the path back. Iterative uses an explicit stack (see [`2b_stacks.md`](../02_data_structures/2b_stacks.md)) and is the fix when depth may exceed the recursion limit — O(V) frames on a path graph.

Use DFS for: connected components, cycle detection, topological sort, flood fill, anything asking about *existence* of a path, and anything where a node's answer depends on its subtree.

## BFS — go wide

Visit all nodes at distance 1, then all at distance 2, and so on.

```
        0
       / \        BFS from 0:  0 | 1, 2 | 3, 4
      1   2       (level by level)
     / \
    3   4
```

```python
from collections import deque

def bfs(start):
    seen = {start}
    q = deque([start])
    dist = 0
    while q:
        for _ in range(len(q)):        # one full level
            node = q.popleft()
            for nxt in graph[node]:
                if nxt not in seen:
                    seen.add(nxt)      # mark on enqueue
                    q.append(nxt)
        dist += 1
```

**BFS finds shortest paths in unweighted graphs, and DFS does not.** The reason is the visiting order: BFS reaches every node in order of increasing distance from the source, so the first time it arrives at a node it has arrived by a shortest route. DFS may reach the same node by a long detour first and mark it visited, locking in the wrong distance.

That guarantee dies the moment edges carry different weights — three cheap edges can beat one expensive one, and BFS counts hops, not cost. Weighted shortest paths need Dijkstra, which is BFS with a min-heap in place of the queue so that the *cheapest* frontier node is expanded next rather than the nearest in hops (see [`2e_heaps_and_priority_queues.md`](../02_data_structures/2e_heaps_and_priority_queues.md)).

Use BFS for: shortest path / minimum steps in an unweighted graph or grid, level-order processing, and multi-source spread (rotting oranges, walls and gates — seed the queue with *all* sources before the loop and the level count is the answer for every one of them at once).

## Choosing between them

| Question asked | Use |
|---|---|
| Is there a path? Are these connected? | either — DFS is shorter to write |
| **Fewest** steps / shortest unweighted path | BFS |
| Shortest path with weights | Dijkstra (min-heap) |
| All nodes in a component, component count | either |
| Cycle detection, topological order | DFS |
| Something per level / per distance | BFS |
| Deep graph, recursion limit a risk | BFS, or iterative DFS |

Space differs in the worst case: DFS holds one path (O(V) on a chain, O(log V) on a balanced tree), BFS holds a whole level (O(V) on a wide graph). Neither dominates.

## The patterns worth recognising

**Connected components / islands.** Loop over every node; when you find an unvisited one, run a traversal from it and increment a counter. The traversal consumes the whole component, so the outer loop stays O(V) overall.

```python
count = 0
for node in range(V):
    if node not in seen:
        dfs(node, seen)
        count += 1
```

**Grids are graphs.** A cell `(r, c)` has neighbours `(r±1, c)` and `(r, c±1)`. No adjacency list is needed — generate neighbours on the fly and bounds-check.

```python
for dr, dc in ((1,0), (-1,0), (0,1), (0,-1)):
    nr, nc = r + dr, c + dc
    if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] == '1':
        ...
```

Mutating the grid in place (`grid[r][c] = '0'`) is a legitimate O(1)-space substitute for a `visited` set when the problem permits destroying the input.

**Cycle detection.** In an **undirected** graph, a cycle exists if DFS reaches an already-visited node that is not the parent it came from. In a **directed** graph that test is wrong — a visited node may simply be in a finished branch. Directed cycles need three states:

```
white = unvisited,  grey = on the current recursion path,  black = fully explored

reaching a grey node → back edge → cycle
reaching a black node → fine, that subgraph is already done
```

**Topological sort.** A linear ordering of a DAG where every edge points forward; the answer to "course schedule", "build order", "task dependencies". Two implementations:

- *Kahn's (BFS)*: compute in-degrees, enqueue every node with in-degree 0, and on dequeue decrement each neighbour's in-degree, enqueueing it when it hits 0. If fewer than `V` nodes come out, the graph has a cycle. O(V + E).
- *DFS*: push a node onto an output list *after* its recursion finishes, then reverse the list. Post-order guarantees dependents are emitted before dependencies.

**Union-find (disjoint set union).** Not a traversal — a structure for "are these two in the same group" under a stream of merges. Near O(1) per operation with path compression and union by rank. Reach for it when connectivity queries interleave with edge additions, or for Kruskal's MST; a plain DFS suffices when the edges are all known up front.

**Bipartite / 2-colouring.** BFS or DFS assigning alternating colours; a conflict with an already-coloured neighbour means an odd cycle, so not bipartite.

## Pitfalls

- **Marking visited on dequeue instead of enqueue.** The node gets queued once per incoming edge; correctness survives, the complexity does not.
- **Treating a directed graph as undirected**, or the reverse, when building the adjacency list. One missing line changes every answer.
- **Using BFS for weighted shortest paths.** It returns hop count, which looks like a plausible distance and is wrong.
- **Forgetting isolated nodes.** Traversing from node 0 only visits node 0's component; component counting needs the outer loop over all nodes.
- **Undirected cycle detection without the parent check.** Every single edge looks like a 2-cycle otherwise, since `u → v → u`.
- **Recursion depth.** A 10⁵-node path graph overflows Python's default limit of 1000 frames.
