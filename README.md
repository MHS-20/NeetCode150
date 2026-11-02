# Lessons

To pick a technique for a new problem, start with [pattern recognition](docs/foundations/pattern_recognition.md). It maps problem signals to the lessons below.

## Foundations

- [Complexity analysis](docs/foundations/complexity_analysis.md): Big-O, the common complexity classes, and how to analyse your own solutions.
- [P, NP, NP-hard and NP-complete](docs/foundations/p_np_nphard_npcomplete.md): the complexity classes, reductions, and pseudo-polynomial algorithms.
- [Pattern recognition](docs/foundations/pattern_recognition.md): which technique a problem wants, from its constraints and wording.

## Data structures

- [Hashing](docs/data_structures/hashing.md): hash maps and sets, collisions, load factor, and the ordered versions.
- [Linked lists](docs/data_structures/linked_lists.md): dummy heads, fast and slow pointers, and in-place reversal.
- [Stacks](docs/data_structures/stacks.md): LIFO, matching brackets, and monotonic stacks.
- [Queues and deques](docs/data_structures/queues_and_deques.md): FIFO, BFS queues, and monotonic deques for sliding windows.
- [Heaps and priority queues](docs/data_structures/heaps_and_priority_queues.md): binary heaps, top-K, two-heap medians, and lazy deletion.
- [Binary trees](docs/data_structures/binary_trees.md): traversals, recursion on trees, and binary search trees.
- [Tries](docs/data_structures/tries.md): prefix trees for word and prefix lookups.

## Sorting and searching

- [Sorting](docs/sorting_and_searching/sorting.md): the comparison-sort lower bound, stability, counting and radix sort, and quickselect.
- [Binary search](docs/sorting_and_searching/binary_search.md): monotonic predicates, boundary searches, floor vs. ceiling, binary search on the answer, and rotated arrays.
- [Bucket sort](docs/sorting_and_searching/bucket_sort.md): sorting by using the key as an index, as in Top K Frequent Elements.

## Techniques

- [Greedy](docs/techniques/greedy.md): when a locally best choice is globally optimal, and how to find a counterexample.
- [Intervals](docs/techniques/intervals.md): sort, then sweep: merging, inserting, and counting overlaps.
- [Backtracking](docs/techniques/backtracking.md): choose, explore, undo: subsets, permutations, and pruning.
- [Bit manipulation](docs/techniques/bit_manipulation.md): bit tricks, XOR, and bitmask subsets and DP.
- [Math and geometry](docs/techniques/math_and_geometry.md): matrix rotation, overflow, modular arithmetic, and other non-structural problems.
- [Floyd's cycle detection](docs/techniques/floyd_cycle_detection.md): finding a cycle and its entrance in O(1) space, on lists, arrays and number sequences.

## Graphs

- [Graphs, BFS and DFS](docs/graphs/graphs_bfs_dfs.md): representations, traversals, grids, and connected components.
- [Topological sort](docs/graphs/topological_sort.md): ordering a DAG with Kahn's algorithm or DFS post-order, and directed cycle detection.
- [Union-Find](docs/graphs/union_find.md): disjoint sets with path compression and union by size, for connectivity and undirected cycles.
- [Dijkstra](docs/graphs/dijkstra.md): single-source shortest paths with non-negative weights, and its variants.
- [Bellman-Ford](docs/graphs/bellman_ford.md): shortest paths with negative weights, negative cycles, and paths with at most `k` edges.
- [Minimum spanning tree](docs/graphs/minimum_spanning_tree.md): Prim and Kruskal, and how an MST differs from shortest paths.
- [Eulerian paths and Hierholzer's algorithm](docs/graphs/hierholzer_eulerian_path.md): using every edge exactly once.

## Dynamic programming

- [Dynamic programming](docs/dynamic_programming/dynamic_programming.md): memoization, tabulation, and the common state shapes.
- [1D vs 2D DP](docs/dynamic_programming/dp_1d_vs_2d.md): how many dimensions the table needs, and how to shrink it.
- [Knapsack](docs/dynamic_programming/knapsack.md): 0/1 and unbounded, counting and min/max variants, and disguised knapsacks.

## Databases

- [SQL query planning and indexes](docs/databases/sql_query_planning_and_indexes.md): how a query becomes an execution plan, and how indexes change it.
