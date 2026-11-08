# NeetCode150

Solutions for NeetCode 150 problems, solved in multiple languages (Java, Python, C++, Javascript, Go Rust, C). Detailed lessons about the topics, techniques and algorithms are included.
The repo covers also SQL, Databases, Storage internal data structures and Business logic mocks.

## Lessons

To pick a technique for a new problem, start with [pattern recognition](00_docs/01_foundations/1b_pattern_recognition.md). It maps problem signals to the lessons below.

### Foundations

- [Complexity analysis](00_docs/01_foundations/1a_complexity_analysis.md): Big-O, the common complexity classes, and how to analyse your own solutions.
- [Pattern recognition](00_docs/01_foundations/1b_pattern_recognition.md): which technique a problem wants, from its constraints and wording.
- [P, NP, NP-hard and NP-complete](00_docs/01_foundations/1c_p_np_nphard_npcomplete.md): the complexity classes, reductions, and pseudo-polynomial algorithms.

### Data structures

- [Hashing](00_docs/02_data_structures/2a_hashing.md): hash maps and sets, collisions, load factor, and the ordered versions.
- [Array and hashing problems](00_docs/02_data_structures/2b_array_problems.md): Product Except Self, Longest Consecutive Sequence, length-prefixed encoding, the Sudoku box index, anagram keys, and four ways to find the top K.
- [Prefix sums](00_docs/02_data_structures/2c_prefix_sums.md): range sums with one subtraction, Subarray Sum Equals K with a hash map, prefix products, and 2D prefix sums.
- [Stacks](00_docs/02_data_structures/2d_stacks.md): LIFO, matching brackets, undo, and deferred evaluation.
- [Monotonic stack](00_docs/02_data_structures/2e_monotonic_stack.md): nearest greater or smaller element in one pass; Daily Temperatures, Largest Rectangle, Trapping Rain Water, Car Fleet and Max Chunks.
- [Queues and deques](00_docs/02_data_structures/2f_queues_and_deques.md): FIFO, BFS queues, and deques.
- [Heaps and priority queues](00_docs/02_data_structures/2g_heaps_and_priority_queues.md): binary heaps, top-K, two-heap medians, and lazy deletion.
- [Heap problems](00_docs/02_data_structures/2h_heap_problems.md): a heap kept at size k, Last Stone Weight, Task Scheduler with its formula, two heaps for the median, and merging feeds in Design Twitter.
- [Tries](00_docs/02_data_structures/2i_tries.md): prefix trees for word and prefix lookups.
- [Trie problems](00_docs/02_data_structures/2j_trie_problems.md): Implement Trie, wildcard search that branches at each `.`, and Word Search II with one grid search pruned by the trie.

### Two pointers

- [Two pointers from opposite ends](00_docs/03_two_pointers/3a_opposite_ends.md): why moving one pointer is safe; Two Sum II, Container With Most Water, 3Sum and Trapping Rain Water.
- [Two pointers in the same direction](00_docs/03_two_pointers/3b_same_direction.md): read/write pointers for in-place filtering, and merging from the back.

### Sliding window

- [Fixed-size sliding windows](00_docs/04_sliding_window/4a_fixed_size.md): add one element, remove one, and track letter counts with a match counter.
- [Variable-size sliding windows](00_docs/04_sliding_window/4b_variable_size.md): longest vs shortest windows, why the cost is O(n), and when a window does not work.
- [Sliding window maximum](00_docs/04_sliding_window/4c_window_max_and_min.md): the monotonic deque, traced step by step.

### Sorting and searching

- [Sorting](00_docs/05_sorting_and_searching/5a_sorting.md): the comparison-sort lower bound, stability, counting and radix sort, and quickselect.
- [Bucket sort](00_docs/05_sorting_and_searching/5b_bucket_sort.md): sorting by using the key as an index, as in Top K Frequent Elements.
- [Binary search](00_docs/05_sorting_and_searching/5c_binary_search.md): monotonic predicates, boundary searches, floor vs. ceiling, binary search on the answer, and rotated arrays.

### Linked lists

- [Linked list basics](00_docs/06_linked_lists/6a_basics.md): nodes, the dummy head, why removal needs the previous node, Remove Nth From End and Merge Two Sorted Lists.
- [Reversing a linked list](00_docs/06_linked_lists/6b_reversal.md): the three-pointer loop drawn step by step, the recursive version, and Reverse Nodes in k-Group.
- [Reordering and merging lists](00_docs/06_linked_lists/6c_reorder_and_merge.md): Reorder List, Add Two Numbers, and three ways to Merge k Sorted Lists.
- [Copy list and LRU cache](00_docs/06_linked_lists/6d_copy_and_cache.md): Copy List with Random Pointer with a map or by weaving, and the LRU cache's map plus doubly linked list.
- [Floyd's cycle detection](00_docs/06_linked_lists/6e_floyd_cycle_detection.md): finding a cycle and its entrance in O(1) space, on lists, arrays and number sequences.

### Trees

- [Tree basics and traversals](00_docs/07_trees/7a_basics_and_traversals.md): terms, height in nodes or edges, iterative DFS with a stack, BFS by level, and Right Side View.
- [Recursion on trees](00_docs/07_trees/7b_recursion_patterns.md): passing information down or up, a special return value for Balanced Tree, and Diameter and Max Path Sum.
- [Binary search trees](00_docs/07_trees/7c_binary_search_trees.md): the ordering rule, Validate BST with bounds, Kth Smallest by inorder, and LCA in a BST.
- [Building and serialising trees](00_docs/07_trees/7d_build_and_serialize.md): rebuilding from preorder and inorder, and preorder with null markers.

### Backtracking

- [Backtracking basics](00_docs/08_backtracking/8a_basics.md): choose, explore, undo; the decision tree drawn two ways for Subsets; why paths are copied; and the cost.
- [Combinations, permutations and duplicates](00_docs/08_backtracking/8b_subsets_and_permutations.md): reuse with `i` vs `i + 1`, skipping equal values in Subsets II and Combination Sum II, and permutations by swapping.
- [Backtracking with constraints](00_docs/08_backtracking/8c_constraints.md): pruning in Generate Parentheses, N-Queens diagonals, Word Search marking, and Palindrome Partitioning.

### Greedy

- [Greedy and how to prove it](00_docs/09_greedy/9a_proofs.md): the exchange argument and greedy-stays-ahead, with counterexamples that break wrong greedy rules.
- [Greedy problems](00_docs/09_greedy/9b_problems.md): Kadane, Jump Game I and II, Gas Station, Hand of Straights, Merge Triplets, Partition Labels and Valid Parenthesis String, each proved and traced.

### Intervals

- [Overlap, merging and inserting](00_docs/10_intervals/10a_overlap_and_merge.md): the overlap test, touching intervals, Merge Intervals, Insert Interval in one pass, and Meeting Rooms.
- [Scheduling, rooms and queries](00_docs/10_intervals/10b_scheduling_and_rooms.md): Non-overlapping Intervals, Meeting Rooms II with a heap or a sweep, and offline queries with lazy deletion.

### Graphs

- [Graphs, BFS and DFS](00_docs/11_graphs/11a_graphs_bfs_dfs.md): representations, traversals, grids, and connected components.
- [Topological sort](00_docs/11_graphs/11b_topological_sort.md): ordering a DAG with Kahn's algorithm or DFS post-order, and directed cycle detection.
- [Union-Find](00_docs/11_graphs/11c_union_find.md): disjoint sets with path compression and union by size, for connectivity and undirected cycles.
- [Dijkstra](00_docs/11_graphs/11d_dijkstra.md): single-source shortest paths with non-negative weights, and its variants.
- [Bellman-Ford](00_docs/11_graphs/11e_bellman_ford.md): shortest paths with negative weights, negative cycles, and paths with at most `k` edges.
- [Minimum spanning tree](00_docs/11_graphs/11f_minimum_spanning_tree.md): Prim and Kruskal, and how an MST differs from shortest paths.
- [Eulerian paths and Hierholzer's algorithm](00_docs/11_graphs/11g_hierholzer_eulerian_path.md): using every edge exactly once.

### Dynamic programming

- [Dynamic programming](00_docs/12_dynamic_programming/12a_dynamic_programming.md): memoization, tabulation, and the common state shapes.
- [1D vs 2D DP](00_docs/12_dynamic_programming/12b_dp_1d_vs_2d.md): how many dimensions the table needs, and how to shrink it.
- [Knapsack](00_docs/12_dynamic_programming/12c_knapsack.md): 0/1 and unbounded, counting and min/max variants, and disguised knapsacks.
- [String DP](00_docs/12_dynamic_programming/12d_string_dp.md): two-sequence tables for LCS, Edit Distance, Distinct Subsequences, Interleaving String and Regex Matching.
- [Interval DP](00_docs/12_dynamic_programming/12e_interval_dp.md): answers for every range `[i, j]`, filled by length; shrink-the-ends and split-point recurrences.

### Bit manipulation

- [Integer representation](00_docs/13_bit_manipulation/13a_integer_representation.md): bit positions, two's complement, and integer type limits in each language.
- [Overflow](00_docs/13_bit_manipulation/13b_overflow.md): what each language does on overflow, negating the smallest value, and division of negative numbers.
- [Operators and shifts](00_docs/13_bit_manipulation/13c_operators_and_shifts.md): `& | ^ ~`, logical and arithmetic shifts, oversized shifts, and precedence.
- [Masking](00_docs/13_bit_manipulation/13d_masking.md): single-bit and multi-bit masks, 32-bit masking in Python, and an integer as a set.
- [Bit tricks](00_docs/13_bit_manipulation/13e_tricks.md): XOR cancellation, `x & (x - 1)`, `x & -x`, and step-by-step walkthroughs of the bit problems.

### Math and geometry

- [Math and geometry](00_docs/14_math_and_geometry/14a_math_and_geometry.md): matrix rotation, overflow, modular arithmetic, and other non-structural problems.
- [Integer formulas](00_docs/14_math_and_geometry/14b_integer_formulas.md): splitting a count in halves, ceiling division, an overflow-free midpoint, flattening a grid index, counting formulas, and the k-largest heap rule.
- [Number theory](00_docs/14_math_and_geometry/14c_number_theory.md): Euclid's GCD and why it works, LCM without overflow, modular arithmetic and the modular inverse, fast exponentiation, and primes.

### Databases

- [SQL basics](00_docs/15_sql_databases/15a_basics.md): the example schema, filtering and sorting, undefined order on ties, NULL and three-valued logic, and the order clauses are evaluated in.
- [Joins](00_docs/15_sql_databases/15b_joins.md): inner, outer and self-joins, conditions in ON vs WHERE, anti-joins and the NOT IN trap, and joins that inflate totals.
- [Grouping and aggregates](00_docs/15_sql_databases/15c_grouping.md): GROUP BY, aggregates and NULL, count(*) after a left join, WHERE vs HAVING, and FILTER.
- [Subqueries, CTEs and set operations](00_docs/15_sql_databases/15d_subqueries_and_ctes.md): scalar and correlated subqueries, EXISTS, derived tables, CTE inlining, recursive CTEs, and UNION/EXCEPT.
- [Window functions](00_docs/15_sql_databases/15e_window_functions.md): aggregates next to each row, ranking and top N per group, running totals, lag and lead, and frames.
- [Views and virtual tables](00_docs/15_sql_databases/15f_views_and_virtual_tables.md): views, updatable views and CHECK OPTION, materialized views, temporary tables, VALUES, generate_series and LATERAL.
- [Changing data and transactions](00_docs/15_sql_databases/15g_modifying_data_and_transactions.md): INSERT/UPDATE/DELETE with RETURNING, upserts, constraints, transactions and savepoints, isolation levels and lost updates.
- [Triggers](00_docs/15_sql_databases/15h_triggers.md): BEFORE, AFTER and INSTEAD OF, row and statement level, audit logs, derived counters, recursion, and simpler alternatives.
- [SQL query planning and indexes](00_docs/15_sql_databases/15i_query_planning_and_indexes.md): how a query becomes an execution plan, and how indexes change it.

### Other problem sets

- [SQL problems](19_sql/): LeetCode database problems solved in PostgreSQL, each linked to its lesson.
- [Practical coding problems](20_practical/): staged specs for non-algorithmic interviews, with solutions and tests per stage. Business logic in Python, storage in Java.
- [HackerRank problems](hackerrank/): three HackerRank problems, each with the nearest LeetCode problem.
