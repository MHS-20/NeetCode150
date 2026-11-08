# Lessons

To pick a technique for a new problem, start with [pattern recognition](00_docs/foundations/pattern_recognition.md). It maps problem signals to the lessons below.

## Foundations

- [Complexity analysis](00_docs/foundations/complexity_analysis.md): Big-O, the common complexity classes, and how to analyse your own solutions.
- [P, NP, NP-hard and NP-complete](00_docs/foundations/p_np_nphard_npcomplete.md): the complexity classes, reductions, and pseudo-polynomial algorithms.
- [Pattern recognition](00_docs/foundations/pattern_recognition.md): which technique a problem wants, from its constraints and wording.

## Data structures

- [Hashing](00_docs/data_structures/hashing.md): hash maps and sets, collisions, load factor, and the ordered versions.
- [Linked lists](00_docs/data_structures/linked_lists.md): dummy heads, fast and slow pointers, and in-place reversal.
- [Stacks](00_docs/data_structures/stacks.md): LIFO, matching brackets, and monotonic stacks.
- [Queues and deques](00_docs/data_structures/queues_and_deques.md): FIFO, BFS queues, and monotonic deques for sliding windows.
- [Heaps and priority queues](00_docs/data_structures/heaps_and_priority_queues.md): binary heaps, top-K, two-heap medians, and lazy deletion.
- [Binary trees](00_docs/data_structures/binary_trees.md): traversals, recursion on trees, and binary search trees.
- [Tries](00_docs/data_structures/tries.md): prefix trees for word and prefix lookups.

## Sorting and searching

- [Sorting](00_docs/sorting_and_searching/sorting.md): the comparison-sort lower bound, stability, counting and radix sort, and quickselect.
- [Binary search](00_docs/sorting_and_searching/binary_search.md): monotonic predicates, boundary searches, floor vs. ceiling, binary search on the answer, and rotated arrays.
- [Bucket sort](00_docs/sorting_and_searching/bucket_sort.md): sorting by using the key as an index, as in Top K Frequent Elements.

## Techniques

- [Two pointers from opposite ends](00_docs/two_pointers/01_opposite_ends.md): why moving one pointer is safe; Two Sum II, Container With Most Water, 3Sum and Trapping Rain Water.
- [Two pointers in the same direction](00_docs/two_pointers/02_same_direction.md): read/write pointers for in-place filtering, and merging from the back.
- [Fixed-size sliding windows](00_docs/sliding_window/01_fixed_size.md): add one element, remove one, and track letter counts with a match counter.
- [Variable-size sliding windows](00_docs/sliding_window/02_variable_size.md): longest vs shortest windows, why the cost is O(n), and when a window does not work.
- [Sliding window maximum](00_docs/sliding_window/03_window_max_and_min.md): the monotonic deque, traced step by step.
- [Greedy](00_docs/techniques/greedy.md): when a locally best choice is globally optimal, and how to find a counterexample.
- [Intervals](00_docs/techniques/intervals.md): sort, then sweep: merging, inserting, and counting overlaps.
- [Backtracking](00_docs/techniques/backtracking.md): choose, explore, undo: subsets, permutations, and pruning.
- [Integer representation](00_docs/bit_manipulation/01_integer_representation.md): bit positions, two's complement, and integer type limits in each language.
- [Overflow](00_docs/bit_manipulation/02_overflow.md): what each language does on overflow, negating the smallest value, and division of negative numbers.
- [Operators and shifts](00_docs/bit_manipulation/03_operators_and_shifts.md): `& | ^ ~`, logical and arithmetic shifts, oversized shifts, and precedence.
- [Masking](00_docs/bit_manipulation/04_masking.md): single-bit and multi-bit masks, 32-bit masking in Python, and an integer as a set.
- [Bit tricks](00_docs/bit_manipulation/05_tricks.md): XOR cancellation, `x & (x - 1)`, `x & -x`, and step-by-step walkthroughs of the bit problems.
- [Math and geometry](00_docs/techniques/math_and_geometry.md): matrix rotation, overflow, modular arithmetic, and other non-structural problems.
- [Floyd's cycle detection](00_docs/techniques/floyd_cycle_detection.md): finding a cycle and its entrance in O(1) space, on lists, arrays and number sequences.

## Graphs

- [Graphs, BFS and DFS](00_docs/graphs/graphs_bfs_dfs.md): representations, traversals, grids, and connected components.
- [Topological sort](00_docs/graphs/topological_sort.md): ordering a DAG with Kahn's algorithm or DFS post-order, and directed cycle detection.
- [Union-Find](00_docs/graphs/union_find.md): disjoint sets with path compression and union by size, for connectivity and undirected cycles.
- [Dijkstra](00_docs/graphs/dijkstra.md): single-source shortest paths with non-negative weights, and its variants.
- [Bellman-Ford](00_docs/graphs/bellman_ford.md): shortest paths with negative weights, negative cycles, and paths with at most `k` edges.
- [Minimum spanning tree](00_docs/graphs/minimum_spanning_tree.md): Prim and Kruskal, and how an MST differs from shortest paths.
- [Eulerian paths and Hierholzer's algorithm](00_docs/graphs/hierholzer_eulerian_path.md): using every edge exactly once.

## Dynamic programming

- [Dynamic programming](00_docs/dynamic_programming/dynamic_programming.md): memoization, tabulation, and the common state shapes.
- [1D vs 2D DP](00_docs/dynamic_programming/dp_1d_vs_2d.md): how many dimensions the table needs, and how to shrink it.
- [Knapsack](00_docs/dynamic_programming/knapsack.md): 0/1 and unbounded, counting and min/max variants, and disguised knapsacks.
- [String DP](00_docs/dynamic_programming/string_dp.md): two-sequence tables for LCS, Edit Distance, Distinct Subsequences, Interleaving String and Regex Matching.
- [Interval DP](00_docs/dynamic_programming/interval_dp.md): answers for every range `[i, j]`, filled by length; shrink-the-ends and split-point recurrences.

## Databases

- [SQL query planning and indexes](00_docs/databases/sql_query_planning_and_indexes.md): how a query becomes an execution plan, and how indexes change it.
