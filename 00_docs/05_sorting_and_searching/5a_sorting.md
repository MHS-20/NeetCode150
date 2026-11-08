# Sorting

## Why it matters when you never write one

You will almost never implement a sort. You will constantly *use* one, and three things about it affect your answers: the O(n log n) it adds to your complexity, whether it is stable, and the fact that sorting is itself the solution to a surprising number of problems.

Sorting converts an unstructured array into one where binary search, two pointers, and single-pass sweeps all become available. Paying O(n log n) up front to make the rest of the algorithm O(n) or O(log n) is one of the most common trades in the whole field — every problem in [`8c_intervals.md`](../08_techniques/8c_intervals.md) and half of [`8b_greedy.md`](../08_techniques/8b_greedy.md) opens with a sort.

## The O(n log n) barrier

No comparison-based sort can beat O(n log n) in the worst case, and the reason is a counting argument rather than a failure of cleverness.

There are `n!` possible orderings of `n` elements. Each comparison has two outcomes, so a sequence of `k` comparisons can distinguish at most `2ᵏ` cases. To identify one ordering out of `n!`, you need

```
2ᵏ ≥ n!    →    k ≥ log₂(n!)    ≈    n log₂ n
```

A sort that only ever compares elements cannot learn enough from fewer comparisons than that. Any claim of an O(n) general-purpose sort must therefore be using information beyond comparisons — which is exactly what counting and radix sort do.

## The algorithms

| Algorithm | Average | Worst | Space | Stable | Note |
|---|---|---|---|---|---|
| Merge sort | O(n log n) | O(n log n) | O(n) | yes | predictable, needs a buffer |
| Quicksort | O(n log n) | **O(n²)** | O(log n) | no | fastest constant in practice |
| Heapsort | O(n log n) | O(n log n) | O(1) | no | in place, poor cache behaviour |
| Insertion sort | O(n²) | O(n²) | O(1) | yes | **O(n) on nearly-sorted data** |
| Counting sort | O(n + k) | O(n + k) | O(k) | yes | small integer range only |
| Radix sort | O(d·(n + k)) | same | O(n + k) | yes | fixed-width keys |

**Merge sort** splits in half, sorts each half, and merges the two sorted halves in linear time. The recursion is `log n` deep and each level does O(n) merging work. The merge step is the part worth remembering on its own — it is the same two-pointer walk used in Merge Two Sorted Lists and in the merge-k-lists heap solution.

**Quicksort** picks a pivot, partitions everything smaller to its left and larger to its right, and recurses on both sides. Average O(n log n), but a pivot that always lands at an extreme gives partitions of size `n-1` and `0`, producing `n` levels of O(n) work — O(n²). Randomising the pivot makes that case astronomically unlikely rather than merely rare. Quicksort still wins in practice because partitioning is a tight in-place scan with excellent locality.

**Heapsort** builds a heap in O(n), then pops `n` times at O(log n) each (see [`2e_heaps_and_priority_queues.md`](../02_data_structures/2e_heaps_and_priority_queues.md)). Worst-case O(n log n) with O(1) extra space, which sounds ideal, but jumping around the heap array misses cache constantly and it loses to quicksort on real data.

**Insertion sort** is O(n²) and still matters: on an array that is already nearly sorted, each element moves a constant distance and the whole thing runs in O(n). Every production sort switches to it for subarrays below roughly 16 elements, where the recursion overhead exceeds the quadratic cost.

Real library sorts combine these. **Timsort** (Python's `sorted`/`.sort()`, Java's `Arrays.sort` for objects) detects already-sorted runs and merges them, giving O(n) on sorted input and stability throughout. **Introsort** (C++ `std::sort`) runs quicksort, counts its recursion depth, and switches to heapsort if it goes too deep — keeping quicksort's speed while capping the worst case at O(n log n).

## Beating n log n: counting and radix

The lower bound applies only to comparison sorts. If the keys are small integers, you can use the key *as an index* rather than comparing it.

**Counting sort.** Tally how many times each value appears, then write the values back out in order.

```
input: [2, 5, 3, 0, 2, 3, 0]        range 0..5

counts:  [2, 0, 2, 2, 0, 1]
index:    0  1  2  3  4  5

output: 0 0 2 2 3 3 5
```

O(n + k) for a range of size `k`. Excellent when `k` is small — sorting ages, grades, or lowercase letters. Useless when `k` is large: sorting three 64-bit integers would allocate an array of 2⁶⁴ counters.

**Radix sort** applies counting sort digit by digit, from least significant to most, and needs the per-digit sort to be stable so earlier passes are not undone. O(d·n) for `d` digits. Used for fixed-width keys — integers, dates, fixed-length strings.

In interviews, counting sort is the right answer to "sort n values in the range 0..100 in O(n)" and to bucket-based problems like Top K Frequent Elements, where frequencies are bounded by `n` and can be bucketed directly instead of heaped.

## Stability

A stable sort preserves the relative order of elements that compare equal.

```
sort by grade only:

  (Ana, B)  (Bo, A)  (Cy, B)  (Di, A)

stable   →  (Bo, A)  (Di, A)  (Ana, B)  (Cy, B)     Bo still before Di
unstable →  (Di, A)  (Bo, A)  (Cy, B)  (Ana, B)     order among equals lost
```

It matters when you sort by several keys in sequence. Sorting by name and then stably by grade produces "grouped by grade, alphabetical within each grade"; an unstable sort scrambles the second criterion. It also matters when the problem's expected output fixes a tie order.

Python's `sorted` is stable, Java's object sort is stable (its primitive sort is not), and C++'s `std::sort` is not — use `std::stable_sort` when you need it.

## Sorting as the solution

**Custom keys.** Most "sorting problems" are really about choosing the key.

```python
intervals.sort(key=lambda x: x[1])            # by end
people.sort(key=lambda p: (-p.height, p.k))   # height desc, then k asc
words.sort(key=lambda w: ''.join(sorted(w)))  # anagram grouping
```

The tuple key is the idiom for multi-level ordering, and negating a number reverses just that field.

**Sort to enable two pointers.** 3Sum sorts first, then fixes one element and walks two pointers inward — the sorted order is what makes "too big, move left" meaningful. O(n²) overall, with the sort disappearing into it.

**Sort to enable a sweep.** All of [`8c_intervals.md`](../08_techniques/8c_intervals.md).

**Sort as a canonical form.** Sorted characters as an anagram key; sorting both arrays to compare multisets.

**Partial sorting.** When only the top K matter, do not sort everything. A bounded heap is O(n log k) and quickselect averages O(n) — both beat O(n log n). See [`2e_heaps_and_priority_queues.md`](../02_data_structures/2e_heaps_and_priority_queues.md).

## Quickselect

Finding the Kth smallest element without sorting. Partition around a pivot exactly as quicksort does, then recurse into **only the side containing position K**.

```
find 3rd smallest of [7, 2, 9, 4, 1, 8]

pivot 4 → [2, 1] 4 [7, 9, 8]
          left has 2 elements; K=3 is the pivot itself → answer 4
```

Discarding half the array each time gives `n + n/2 + n/4 + ... = 2n`, so the average is **O(n)** — no logarithm, because there is only one branch to follow instead of two. The worst case is O(n²) under adversarial pivots, fixed in practice by random pivot selection.

Use quickselect when the whole array is in memory and you need one order statistic. Use a heap when the data streams in or cannot all be held, since quickselect needs random access and permutes the input.

## Complexity notes for your own solutions

- **Sorting sets a floor.** Any solution that begins with a sort is at least O(n log n); claiming O(n) afterwards is wrong.
- **Sorting inside a loop.** `for x in items: candidates.sort()` is O(n² log n) and is the usual cause of an unexpected timeout.
- **Python's `sorted` copies, `.sort()` mutates.** O(n) extra space for the first, in place for the second.
- **Sorting strings is not O(n log n).** Each comparison costs up to the string length L, so it is O(L · n log n).

## Pitfalls

- Assuming the library sort is stable. It depends on the language and on whether the elements are primitives.
- Using a comparison-based sort where the value range makes counting sort O(n).
- Forgetting that sorting destroys the original indices. Sort `(value, index)` pairs, or sort the indices by value, when the answer needs positions.
- Relying on quicksort's average case in a worst-case analysis. Say O(n²) worst, O(n log n) average, and mention random pivoting.
