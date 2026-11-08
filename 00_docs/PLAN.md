# Plan: docs expansion for NeetCode 250

The topics below are what the docs need to cover the 100 problems that NeetCode 250 adds to NeetCode 150, plus three topics outside the list: string algorithms, segment and Fenwick trees, and language specifics. System design and concurrency are out of scope.

## 1. New lessons and sections

Each item gives the page it belongs in: an existing page to extend, or a new page.

### Arrays and hashing (`02_data_structures`)
- [ ] **Boyer-Moore majority voting**, for one majority element (> n/2) and for up to two (> n/3). Majority Element, Majority Element II. Goes in `2b_array_problems`.
- [ ] **Dutch national flag**, three-way partitioning in one pass. Sort Colors. Goes in `2b` or `5a_sorting`.
- [ ] **Indices as a hash set**, cyclic sort, marking with the sign, with O(1) extra space. First Missing Positive. Goes in `2b`.
- [ ] **Building a hash table**: chaining vs open addressing, load factor, resizing. Design HashSet, Design HashMap. Goes in `2a_hashing`.

### Two pointers (`03_two_pointers`)
- [ ] **Rotating an array by reversing it three times.** Rotate Array.
- [ ] **k-Sum as recursion down to 2Sum.** 4Sum.
- [ ] **Merging in place from the back.** Merge Sorted Array.

### Stacks and design (`02_data_structures`)
- [ ] **A stack of partial results for nested input.** Decode String, Simplify Path, Asteroid Collision. Goes in `2d_stacks`.
- [ ] **A queue from two stacks, with amortised O(1); a stack from queues.** Goes in `2f_queues_and_deques`.
- [ ] **Ring buffer.** Design Circular Queue. Goes in `2f`.
- [ ] **A stack per frequency.** Maximum Frequency Stack. Goes in `2d`.
- [ ] **Monotonic stack for spans:** each entry stores its span, and popped spans are added to it. Online Stock Span. Goes in `2e_monotonic_stack`.

### Binary search (`05_sorting_and_searching/5c_binary_search`)
- [ ] **Rotated arrays with duplicates**, and why the worst case becomes O(n). Search in Rotated Sorted Array II.
- [ ] **Mountain arrays:** find the peak, then search each side. Find in Mountain Array.
- [ ] Integer square root as a last-true search. Sqrt(x).

### Linked lists (`06_linked_lists`)
- [ ] **Reversing a sub-range.** Reverse Linked List II. Goes in `6b_reversal`.
- [ ] **LFU cache:** a list per frequency plus a minimum-frequency pointer. Goes in `6d_copy_and_cache`.

### Trees (`07_trees`)
- [ ] **Iterative traversals with an explicit stack** (inorder, preorder, postorder), and Morris traversal for O(1) space. Goes in `7a_basics_and_traversals`.
- [ ] **BST insert and delete**, including the node with two children. Goes in `7c_binary_search_trees`.
- [ ] **Tree DP returning a pair**, take or skip. House Robber III. Goes in `7b_recursion_patterns`.
- [ ] **Quad trees** and building a tree by dividing the grid. Construct Quad Tree.
- [ ] Deleting nodes after the recursion returns (postorder). Delete Leaves With a Given Value.

### Heaps (`02_data_structures/2h_heap_problems`)
- [ ] **Simulation driven by time with a heap.** Single-Threaded CPU, IPO, Meeting Rooms III.
- [ ] **Greedy choice by highest remaining count.** Reorganize String, Longest Happy String.
- [ ] Car Pooling: heap vs difference array.

### Backtracking (`08_backtracking`)
- [ ] **Filling buckets and pruning:** sort descending, skip identical empty buckets. Matchsticks to Square, Partition to K Equal Sum Subsets. Goes in `8c_constraints`.
- [ ] Backtracking with memoization. Word Break II.

### Tries (`02_data_structures/2j_trie_problems`)
- [ ] **Trie plus DP over suffixes.** Extra Characters in a String.

### Graphs (`11_graphs`)
- [ ] **BFS over states**, where nodes are configurations. Open the Lock. Goes in `11a`.
- [ ] **Union-Find with weights**, storing the ratio to the parent. Evaluate Division. Goes in `11c`.
- [ ] **Union-Find over shared keys:** emails (Accounts Merge) and prime factors (GCD Traversal). Goes in `11c`.
- [ ] **Trimming leaves layer by layer to find the centre.** Minimum Height Trees. Goes in `11b`.
- [ ] **Reachability for every pair:** Floyd-Warshall, or BFS from each node. Course Schedule IV. New page `11h_floyd_warshall`.
- [ ] **Two topological sorts, one per axis.** Build a Matrix With Conditions. Goes in `11b`.
- [ ] **Dijkstra where the cost is the path's largest edge**, and when binary search plus BFS does the same job. Path With Minimum Effort. Goes in `11d`.
- [ ] **Critical and pseudo-critical MST edges**, by forcing an edge in or leaving it out. Goes in `11f`.
- [ ] In-degree and out-degree counting. Find the Town Judge.

### Dynamic programming (`12_dynamic_programming`)
- [ ] **Game DP and minimax:** score difference, the opponent playing optimally. Stone Game I, II and III. New page `12f_game_dp`.
- [ ] **Turning a problem into a knapsack.** Last Stone Weight II (split into two groups with the smallest difference). Goes in `12c_knapsack`.
- [ ] **Combinations vs permutations in unbounded knapsack** (loop order). Combination Sum IV vs Coin Change II. Goes in `12c`.
- [ ] Perfect Squares and Integer Break as unbounded knapsack, plus the math shortcut for Integer Break.

### Greedy (`09_greedy/9b_problems`)
- [ ] **Circular Kadane:** the total minus the minimum subarray, and the case where every number is negative. Maximum Sum Circular Subarray.
- [ ] **Two passes, left then right.** Candy.
- [ ] **Greedy with queues**, taking turns. Dota2 Senate.
- [ ] Jump Game VII: reachability with a sliding window or a prefix count.
- [ ] Longest Turbulent Subarray as a variant of Kadane.

### Math and bits (`14_math_and_geometry`, `13_bit_manipulation`)
- [ ] **Base 26 with no zero digit.** Excel Sheet Column Title. Goes in `14b_integer_formulas`.
- [ ] **GCD of strings:** concatenation commutes exactly when there is a common base. Goes in `14c_number_theory`.
- [ ] Roman numerals: subtract when a smaller value comes before a larger one.
- [ ] **Bitwise AND of a range** is the common binary prefix. Goes in `13e_tricks`.
- [ ] **Placing bits into the zero positions of a mask.** Minimum Array End. Goes in `13d_masking`.
- [ ] Adding binary strings with a carry. Add Binary.

## 2. Topics outside the list

### String algorithms (new folder `16_strings`)
- [ ] `16a_string_basics`: immutable strings and what building one costs in each language (StringBuilder, `join`, `strings.Builder`); comparing characters; counting with a fixed array of 26 or 128 entries.
- [ ] `16b_pattern_matching`: naive search; the KMP prefix function; the Z-function.
- [ ] `16c_rolling_hash`: Rabin-Karp, choosing the base and modulus, collisions, double hashing.
- [ ] `16d_palindromes`: expanding from the centre (already used in 150), and Manacher in O(n).

### Segment trees and Fenwick trees (`02_data_structures`, new pages)
- [ ] `2k_fenwick_trees`: prefix sums with point updates, `i & -i` (links to `13e`), range updates via difference arrays.
- [ ] `2l_segment_trees`: range queries with point updates, lazy propagation, and when a Fenwick tree is enough.
- [ ] Practice problems: Range Sum Query Mutable (307), Count of Smaller Numbers After Self (315), My Calendar (729/731).

### Language specifics (new folder `17_language_specifics`)
One page per language, covering the same points:
- [ ] Standard containers and their costs: ordered vs hashed maps, heaps, deques.
- [ ] The heap's direction, and how to get the other one (for example, `heapq` is a min-heap only).
- [ ] Custom comparators and sort stability.
- [ ] Integer sizes and overflow (link to `13b_overflow`), division and modulo of negatives (link to `14b`).
- [ ] Building strings and what it costs.
- [ ] Recursion depth limits (Python's default is 1000) and when to switch to iteration.
- [ ] Pitfalls: Java `Integer` and `==`; C++ `map[key]` inserting a missing key; Go maps iterating in random order; Rust ownership in graph and tree code; JavaScript's default `sort` comparing as strings.

Pages: `17a_cpp`, `17b_c`, `17c_go`, `17d_java`, `17e_javascript`, `17f_python`, `17g_rust`.

## 3. Problems NeetCode 250 adds to NeetCode 150

Arrays and Hashing (13)
- 1929. Concatenation of Array
- 14. Longest Common Prefix
- 27. Remove Element
- 169. Majority Element
- 705. Design HashSet
- 706. Design HashMap
- 912. Sort an Array
- 75. Sort Colors
- 304. Range Sum Query 2D Immutable
- 122. Best Time to Buy and Sell Stock II
- 229. Majority Element II
- 560. Subarray Sum Equals K
- 41. First Missing Positive

Two Pointers (8)
- 344. Reverse String
- 680. Valid Palindrome II
- 1768. Merge Strings Alternately
- 88. Merge Sorted Array
- 26. Remove Duplicates from Sorted Array
- 18. 4Sum
- 189. Rotate Array
- 881. Boats to Save People

Sliding Window (3)
- 219. Contains Duplicate II
- 209. Minimum Size Subarray Sum
- 658. Find K Closest Elements

Stack (8)
- 682. Baseball Game
- 225. Implement Stack using Queues
- 232. Implement Queue using Stacks
- 735. Asteroid Collision
- 901. Online Stock Span
- 71. Simplify Path
- 394. Decode String
- 895. Maximum Frequency Stack

Binary Search (7)
- 35. Search Insert Position
- 374. Guess Number Higher or Lower
- 69. Sqrt(x)
- 1011. Capacity to Ship Packages Within D Days
- 81. Search in Rotated Sorted Array II
- 410. Split Array Largest Sum
- 1095. Find in Mountain Array

Linked List (3)
- 92. Reverse Linked List II
- 622. Design Circular Queue
- 460. LFU Cache

Trees (8)
- 94. Binary Tree Inorder Traversal
- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
- 701. Insert into a Binary Search Tree
- 450. Delete Node in a BST
- 427. Construct Quad Tree
- 337. House Robber III
- 1325. Delete Leaves With a Given Value

Heap / Priority Queue (5)
- 1834. Single-Threaded CPU
- 767. Reorganize String
- 1405. Longest Happy String
- 1094. Car Pooling
- 502. IPO

Backtracking (7)
- 1863. Sum of All Subset XOR Totals
- 77. Combinations
- 47. Permutations II
- 473. Matchsticks to Square
- 698. Partition to K Equal Sum Subsets
- 52. N-Queens II
- 140. Word Break II

Tries (1)
- 2707. Extra Characters in a String

Graphs (8)
- 463. Island Perimeter
- 953. Verifying an Alien Dictionary
- 997. Find the Town Judge
- 752. Open the Lock
- 1462. Course Schedule IV
- 721. Accounts Merge
- 399. Evaluate Division
- 310. Minimum Height Trees

Advanced Graphs (4)
- 1631. Path With Minimum Effort
- 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
- 2392. Build a Matrix With Conditions
- 2709. Greatest Common Divisor Traversal

1-D Dynamic Programming (5)
- 1137. N-th Tribonacci Number
- 377. Combination Sum IV
- 279. Perfect Squares
- 343. Integer Break
- 1406. Stone Game III

2-D Dynamic Programming (5)
- 63. Unique Paths II
- 64. Minimum Path Sum
- 1049. Last Stone Weight II
- 877. Stone Game
- 1140. Stone Game II

Greedy (6)
- 860. Lemonade Change
- 918. Maximum Sum Circular Subarray
- 978. Longest Turbulent Subarray
- 1871. Jump Game VII
- 649. Dota2 Senate
- 135. Candy

Intervals (1)
- 2402. Meeting Rooms III

Math and Geometry (5)
- 168. Excel Sheet Column Title
- 1071. Greatest Common Divisor of Strings
- 2807. Insert Greatest Common Divisors in Linked List
- 867. Transpose Matrix
- 13. Roman to Integer

Bit Manipulation (3)
- 67. Add Binary
- 201. Bitwise AND of Numbers Range
- 3133. Minimum Array End

Total: 100.
