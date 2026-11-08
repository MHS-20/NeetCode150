# Lessons

To pick a technique for a new problem, start with [pattern recognition](00_docs/01_foundations/1b_pattern_recognition.md). It maps problem signals to the lessons below.

## Foundations

- [Complexity analysis](00_docs/01_foundations/1a_complexity_analysis.md): Big-O, the common complexity classes, and how to analyse your own solutions.
- [Pattern recognition](00_docs/01_foundations/1b_pattern_recognition.md): which technique a problem wants, from its constraints and wording.
- [P, NP, NP-hard and NP-complete](00_docs/01_foundations/1c_p_np_nphard_npcomplete.md): the complexity classes, reductions, and pseudo-polynomial algorithms.

## Data structures

- [Hashing](00_docs/02_data_structures/2a_hashing.md): hash maps and sets, collisions, load factor, and the ordered versions.
- [Linked lists](00_docs/02_data_structures/2b_linked_lists.md): dummy heads, fast and slow pointers, and in-place reversal.
- [Stacks](00_docs/02_data_structures/2c_stacks.md): LIFO, matching brackets, undo, and deferred evaluation.
- [Monotonic stack](00_docs/02_data_structures/2d_monotonic_stack.md): nearest greater or smaller element in one pass; Daily Temperatures, Largest Rectangle, Trapping Rain Water, Car Fleet and Max Chunks.
- [Queues and deques](00_docs/02_data_structures/2e_queues_and_deques.md): FIFO, BFS queues, and deques.
- [Heaps and priority queues](00_docs/02_data_structures/2f_heaps_and_priority_queues.md): binary heaps, top-K, two-heap medians, and lazy deletion.
- [Binary trees](00_docs/02_data_structures/2g_binary_trees.md): traversals, recursion on trees, and binary search trees.
- [Tries](00_docs/02_data_structures/2h_tries.md): prefix trees for word and prefix lookups.

## Two pointers

- [Two pointers from opposite ends](00_docs/03_two_pointers/3a_opposite_ends.md): why moving one pointer is safe; Two Sum II, Container With Most Water, 3Sum and Trapping Rain Water.
- [Two pointers in the same direction](00_docs/03_two_pointers/3b_same_direction.md): read/write pointers for in-place filtering, and merging from the back.

## Sliding window

- [Fixed-size sliding windows](00_docs/04_sliding_window/4a_fixed_size.md): add one element, remove one, and track letter counts with a match counter.
- [Variable-size sliding windows](00_docs/04_sliding_window/4b_variable_size.md): longest vs shortest windows, why the cost is O(n), and when a window does not work.
- [Sliding window maximum](00_docs/04_sliding_window/4c_window_max_and_min.md): the monotonic deque, traced step by step.

## Sorting and searching

- [Sorting](00_docs/05_sorting_and_searching/5a_sorting.md): the comparison-sort lower bound, stability, counting and radix sort, and quickselect.
- [Bucket sort](00_docs/05_sorting_and_searching/5b_bucket_sort.md): sorting by using the key as an index, as in Top K Frequent Elements.
- [Binary search](00_docs/05_sorting_and_searching/5c_binary_search.md): monotonic predicates, boundary searches, floor vs. ceiling, binary search on the answer, and rotated arrays.

## Techniques

- [Backtracking](00_docs/06_techniques/6a_backtracking.md): choose, explore, undo: subsets, permutations, and pruning.
- [Greedy](00_docs/06_techniques/6b_greedy.md): when a locally best choice is globally optimal, and how to find a counterexample.
- [Intervals](00_docs/06_techniques/6c_intervals.md): sort, then sweep: merging, inserting, and counting overlaps.
- [Floyd's cycle detection](00_docs/06_techniques/6d_floyd_cycle_detection.md): finding a cycle and its entrance in O(1) space, on lists, arrays and number sequences.

## Graphs

- [Graphs, BFS and DFS](00_docs/07_graphs/7a_graphs_bfs_dfs.md): representations, traversals, grids, and connected components.
- [Topological sort](00_docs/07_graphs/7b_topological_sort.md): ordering a DAG with Kahn's algorithm or DFS post-order, and directed cycle detection.
- [Union-Find](00_docs/07_graphs/7c_union_find.md): disjoint sets with path compression and union by size, for connectivity and undirected cycles.
- [Dijkstra](00_docs/07_graphs/7d_dijkstra.md): single-source shortest paths with non-negative weights, and its variants.
- [Bellman-Ford](00_docs/07_graphs/7e_bellman_ford.md): shortest paths with negative weights, negative cycles, and paths with at most `k` edges.
- [Minimum spanning tree](00_docs/07_graphs/7f_minimum_spanning_tree.md): Prim and Kruskal, and how an MST differs from shortest paths.
- [Eulerian paths and Hierholzer's algorithm](00_docs/07_graphs/7g_hierholzer_eulerian_path.md): using every edge exactly once.

## Dynamic programming

- [Dynamic programming](00_docs/08_dynamic_programming/8a_dynamic_programming.md): memoization, tabulation, and the common state shapes.
- [1D vs 2D DP](00_docs/08_dynamic_programming/8b_dp_1d_vs_2d.md): how many dimensions the table needs, and how to shrink it.
- [Knapsack](00_docs/08_dynamic_programming/8c_knapsack.md): 0/1 and unbounded, counting and min/max variants, and disguised knapsacks.
- [String DP](00_docs/08_dynamic_programming/8d_string_dp.md): two-sequence tables for LCS, Edit Distance, Distinct Subsequences, Interleaving String and Regex Matching.
- [Interval DP](00_docs/08_dynamic_programming/8e_interval_dp.md): answers for every range `[i, j]`, filled by length; shrink-the-ends and split-point recurrences.

## Bit manipulation

- [Integer representation](00_docs/09_bit_manipulation/9a_integer_representation.md): bit positions, two's complement, and integer type limits in each language.
- [Overflow](00_docs/09_bit_manipulation/9b_overflow.md): what each language does on overflow, negating the smallest value, and division of negative numbers.
- [Operators and shifts](00_docs/09_bit_manipulation/9c_operators_and_shifts.md): `& | ^ ~`, logical and arithmetic shifts, oversized shifts, and precedence.
- [Masking](00_docs/09_bit_manipulation/9d_masking.md): single-bit and multi-bit masks, 32-bit masking in Python, and an integer as a set.
- [Bit tricks](00_docs/09_bit_manipulation/9e_tricks.md): XOR cancellation, `x & (x - 1)`, `x & -x`, and step-by-step walkthroughs of the bit problems.

## Math and geometry

- [Math and geometry](00_docs/10_math_and_geometry/10a_math_and_geometry.md): matrix rotation, overflow, modular arithmetic, and other non-structural problems.

## Databases

- [SQL query planning and indexes](00_docs/11_databases/11a_sql_query_planning_and_indexes.md): how a query becomes an execution plan, and how indexes change it.
