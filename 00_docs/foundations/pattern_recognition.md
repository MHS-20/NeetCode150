# Recognising Which Pattern a Problem Wants

The other lessons explain the tools. This one is about picking the right one up. Most of the time you lose on a problem is spent here, not on writing the code — once the pattern is named, the implementation is usually short.

## Start with the constraints

Before reading the problem twice, read the constraint block. It narrows the answer more reliably than the prose does, because the setter chose those numbers to admit exactly one class of solution.

Assume roughly 10⁸ simple operations per second.

| `n` up to | Complexity that fits | Likely technique |
|---|---|---|
| 10–12 | O(n!) | permutations, brute-force backtracking |
| 15–20 | O(2ⁿ) | subsets, bitmask DP |
| 100–500 | O(n³) | interval DP, Floyd-Warshall, triple loop |
| 2,000–5,000 | O(n²) | 2D DP, all pairs, nested scan |
| 10⁵–10⁶ | O(n log n) | sorting, heap, binary search, divide and conquer |
| 10⁶–10⁸ | O(n) or O(log n) | one pass, two pointers, sliding window, hash map, math |

Read it in both directions. `n ≤ 20` is close to an announcement that exponential enumeration is expected, so stop hunting for a clever polynomial solution. `n ≤ 10⁵` rules out O(n²) and tells you a nested loop must become a sort, a hash map, or a monotonic structure.

Other constraints carry as much information:

- **"The array is sorted"** — binary search or two pointers, almost always. Sortedness is never mentioned idly.
- **"Values are in range 0..n"** or a small alphabet — counting sort, an index-as-key trick, or a fixed-size array instead of a hash map.
- **"Return the answer modulo 10⁹+7"** — the count is astronomically large, so the answer is a counting DP, not an enumeration.
- **"Do it in O(1) extra space"** — in-place pointer manipulation, index-as-storage tricks, or Floyd's cycle detection. It rules out the hash map you were about to reach for.
- **"Without using division"**, "in one pass", "in place" — these are pointing directly at a specific trick.

## Then match the question's shape

What the problem *asks for* narrows the technique more than what it is about.

| The question asks for | Technique | File |
|---|---|---|
| **All** solutions, every combination/permutation/arrangement | backtracking | [`backtracking.md`](../techniques/backtracking.md) |
| **How many ways**, count of arrangements | DP (counting) | [`dynamic_programming.md`](../dynamic_programming/dynamic_programming.md) |
| **Minimum / maximum** value over a sequence of choices | DP, or greedy if a safe rule exists | [`dynamic_programming.md`](../dynamic_programming/dynamic_programming.md), [`greedy.md`](../techniques/greedy.md) |
| **Fewest steps / shortest path**, unweighted | BFS | [`graphs_bfs_dfs.md`](../graphs/graphs_bfs_dfs.md) |
| **Shortest path with weights** | Dijkstra (heap) | [`heaps_and_priority_queues.md`](../data_structures/heaps_and_priority_queues.md) |
| **Is it possible / can it reach** | DFS, or greedy feasibility | [`graphs_bfs_dfs.md`](../graphs/graphs_bfs_dfs.md) |
| **Kth largest / smallest, top K** | bounded heap or quickselect | [`heaps_and_priority_queues.md`](../data_structures/heaps_and_priority_queues.md) |
| **Best contiguous subarray/substring** | sliding window, or Kadane's | [variable-size windows](../sliding_window/02_variable_size.md), [`greedy.md`](../techniques/greedy.md) |
| **A pair or triple summing to a target** | sort + two pointers, or a hash map | [two pointers](../two_pointers/01_opposite_ends.md), [`hashing.md`](../data_structures/hashing.md) |
| **Next greater / smaller element, spans** | monotonic stack | [`stacks.md`](../data_structures/stacks.md) |
| **Max/min over a moving window** | monotonic deque | [window maximum](../sliding_window/03_window_max_and_min.md), [`queues_and_deques.md`](../data_structures/queues_and_deques.md) |
| **Merge, overlap, schedule, rooms** | sort intervals, sweep | [`intervals.md`](../techniques/intervals.md) |
| **Prefix matching, dictionary of words** | trie | [`tries.md`](../data_structures/tries.md) |
| **Ordering under dependencies** | topological sort | [`graphs_bfs_dfs.md`](../graphs/graphs_bfs_dfs.md) |
| **Are these connected / how many groups** | DFS, BFS, or union-find | [`graphs_bfs_dfs.md`](../graphs/graphs_bfs_dfs.md) |
| **Seen this before, counts, grouping** | hash map / hash set | [`hashing.md`](../data_structures/hashing.md) |

## Keyword triggers

Phrases that reliably point somewhere. Not proof, but a strong first guess.

**"Contiguous" / "substring" / "subarray"** → sliding window or prefix sums. Contiguity is what makes a window valid; if the problem says *subsequence* instead, the window is wrong and it is usually DP.

**"Subsequence"** → DP. The elements need not be adjacent, so no window can track them.

**"Sorted array" + "find"** → binary search. If it is sorted and the expected complexity is better than O(n), there is no other candidate.

**"Minimise the maximum"**, "maximum minimum", "smallest capacity such that…" → **binary search on the answer** ([`binary_search.md`](../sorting_and_searching/binary_search.md)). Rather than searching the array, search the space of possible answers and write a feasibility check. Koko Eating Bananas and Capacity to Ship Packages are this pattern, and it is the one most often missed, because the array being searched never appears in the input.

**"K most/least frequent"**, "top K", "Kth" → heap of size K, or bucket sort when the values are frequencies bounded by n.

**"All permutations/combinations/subsets"**, "generate every" → backtracking.

**"Parentheses", "valid", "nested", "undo"** → stack.

**"Palindrome"** → two pointers from the ends, or expand-around-centre, or interval DP if it is about subsequences.

**"Cycle"** → fast/slow pointers for a linked list or numeric sequence, three-colour DFS for a directed graph, union-find for an undirected one.

**"Prefix"** → trie for words, prefix-sum array for numbers.

**"In place", "O(1) space"** → pointer swapping, index-as-flag, or reusing the input array as storage.

**"Stream" / "as elements arrive"** → heap, or a structure that maintains its invariant incrementally. Anything requiring the full input up front is ruled out.

**"Grid"** → treat cells as graph nodes. BFS for fewest steps, DFS for regions, DP if movement is one-directional.

## The distinctions people get wrong

**Sliding window vs. two pointers.** Both use two indices. A window has a left and right end moving the *same* direction, maintaining a valid region over contiguous elements. Two pointers usually start at opposite ends of a *sorted* array and move toward each other. If the array must be sorted for the logic to work, it is two pointers; if the array's order is given and the question is about contiguous runs, it is a window.

**Backtracking vs. DP.** Same decision tree underneath. Backtracking *lists* the solutions; DP *counts or optimises* over them without listing. If the output is a list of arrangements you must enumerate — exponential is unavoidable. If the output is one number, look for a state that collapses many arrangements into one table cell.

**Greedy vs. DP.** Greedy commits to a choice and never revisits it; DP tries all choices and keeps the best. Try greedy first because it is far simpler, but only after you have spent thirty seconds trying to build a counterexample. If one appears, it is DP. See [`greedy.md`](../techniques/greedy.md).

**BFS vs. DFS.** BFS for *fewest* anything, DFS for *existence*, structure, and per-subtree answers. Weighted edges break BFS's guarantee entirely.

**Heap vs. sorting.** Sorting is O(n log n) and gives you everything; a bounded heap is O(n log k) and gives you only the top K. When K is small relative to n, or the data streams, the heap wins. When you need the whole thing ordered anyway, just sort.

**Hash map vs. sorted map.** Hash for membership and counting. A balanced BST only when the problem needs predecessors, successors, or range queries — the O(log n) is a real cost otherwise. See [`hashing.md`](../data_structures/hashing.md).

**Monotonic stack vs. monotonic deque.** The stack answers "nearest greater/smaller element" over a whole array; the deque answers "max/min inside a moving window". Same popping logic, but a window needs both ends available.

## A procedure when nothing is obvious

1. **Brute force it, out loud.** Write the O(n²) or O(2ⁿ) version in your head and state its complexity. It establishes a correct baseline and often exposes the structure you can exploit.
2. **Name the repeated work.** Faster solutions come from removing repetition. Recomputing a sum over an overlapping range → prefix sums or a sliding window. Rescanning for a value → hash map. Recomputing the same subproblem → memoization. Rescanning for a maximum → heap or monotonic structure.
3. **Ask what you would need to know at each step** to answer in O(1). That question is usually the definition of the DP state, or of what the auxiliary structure should hold.
4. **Try small inputs by hand.** n = 1, 2, 3. Patterns in the answers reveal recurrences, and edge cases reveal themselves before the code does.
5. **Compare to a problem you have solved.** Most problems are a known one with one constraint changed. Identify the base problem, then ask what the change breaks.
6. **Check the constraint table again.** If your solution's complexity does not match the target, you have the wrong pattern, not a slow implementation.

## Common transformations

Recognising that a problem *is* another problem in disguise is half of this skill.

- A **grid** is a graph. A **string** is an array. A **numeric sequence with a `next` function** is a linked list, so cycle detection applies.
- **"Fewest steps between states"** is BFS, even when nothing resembles a graph — the states are the nodes and the legal moves are the edges. Word Ladder and Open the Lock are BFS over strings.
- **"Best sum of a contiguous range"** is a prefix-sum problem. `sum(i..j) = prefix[j] − prefix[i-1]`, which turns a range query into one subtraction.
- **Counting subarrays with a property** is often prefix sums plus a hash map of previously seen prefix values.
- **"Merge K sorted things"** is a heap.
- **"Check against a dictionary at every step"** is a trie.
- **"Minimum capacity/speed/size such that a check passes"** is binary search on the answer.
- **Two sorted halves** is a merge step.

## If you are stuck

Say the brute force, its complexity, and why it is too slow. Then say which of the three sources of speedup you think applies: **precomputation** (prefix sums, a hash map built in one pass), **a better data structure** (heap, trie, monotonic stack), or **avoiding recomputation** (DP). Nearly every optimisation in this problem set is one of those three, and naming them narrows the search enough to make progress.
