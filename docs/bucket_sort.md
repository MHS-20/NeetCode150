# Bucket Sort

## The idea

Bucket sort replaces comparisons with array indexing. You compute a bucket number from each element's key, drop the element into that slot, and read the slots back in index order. The slot order is the sorted order, so nothing is ever compared with anything else.

This is how it gets under the O(n log n) bound from `sorting.md`. That bound only applies to sorts that learn the order through comparisons. Bucket sort learns it from the key's numeric value, so it needs extra information: the keys have to fall into a range small enough to allocate one slot per value, or per group of values.

```
keys:     3  1  3  0  2  1  3        range 0..3

bucket 0: [0]
bucket 1: [1, 1]
bucket 2: [2]
bucket 3: [3, 3, 3]

read 0 → 3:  0 1 1 2 3 3 3
```

Counting sort (`sorting.md`) is the special case where the buckets hold only a tally. Bucket sort keeps the elements themselves. You need that when the key is not the whole element, for example when you sort values *by their frequency* and want the values back, not the frequencies.

## Two flavours

**One bucket per key value.** Use this when the key is an integer in a known range `0..R`. You allocate `R + 1` buckets, and each one holds every element with that exact key. No sorting happens inside a bucket because all of its elements share the same key. The cost is O(n + R) time and O(n + R) space. Interview problems almost always use this flavour.

**One bucket per range of values.** This is the textbook version for real numbers spread over an interval, such as floats in `[0, 1)`. You split the interval into `n` equal-width buckets, put each value into bucket `floor(value * n)`, sort each bucket with insertion sort, and concatenate. If the values are uniformly distributed, each bucket gets about one element and the total cost is O(n) on average. If they cluster, most values land in one bucket and the cost falls back to whatever that bucket's sort costs, which is O(n²) with insertion sort. The O(n) is a claim about the input distribution, not a worst-case guarantee.

## Worked example: Top K Frequent Elements (347)

Given `nums` and `k`, return the `k` values that occur most often.

The first step is the same in every solution: count frequencies in a hash map. The solutions differ in how they order the `m` distinct values by count.

```
nums = [1, 1, 1, 2, 2, 3],  k = 2

freq:  1 → 3,  2 → 2,  3 → 1
```

What makes bucketing possible is a bound on the key. A value cannot appear more often than there are elements, so every frequency lies in `1..n`. Use the frequency as the bucket index:

```
bucket index = frequency       size n + 1 = 7

[0]  [ ]
[1]  [3]
[2]  [2]
[3]  [1]
[4]  [ ]
[5]  [ ]
[6]  [ ]

scan 6 → 0, collect until k = 2:   1, 2
```

```cpp
vector<vector<int>> buckets(nums.size() + 1);  // frequency can be n
for (auto &[val, cnt] : freq)
    buckets[cnt].push_back(val);

vector<int> res;
for (int f = buckets.size() - 1; f >= 0 && res.size() < k; f--)
    for (int val : buckets[f]) {
        res.push_back(val);
        if (res.size() == k) break;
    }
```

Building the buckets is O(m). The scan visits `n + 1` buckets and at most `m` values, so the whole thing is O(n) time and O(n) space. The other ways of ordering the counts compare like this:

| Ordering step | Time | Extra space | Note |
|---|---|---|---|
| Sort `(value, count)` pairs | O(m log m) | O(m) | simplest to write |
| Max-heap of all `m`, pop `k` | O(m log m) build by pushes (O(m) with heapify) + O(k log m) | O(m) | |
| Min-heap capped at size `k` | O(m log k) | O(k) | best when `k` is small and memory matters |
| Buckets indexed by frequency | **O(n)** | O(n) | linear, independent of `k` |

`m ≤ n` throughout, and the counting pass adds O(n) to every row.

The same pattern solves Sort Characters By Frequency (451): count the characters, bucket them by count, then read the buckets from high to low and write each character `count` times.

## When to reach for it

Use buckets when **the key you are ordering by is a small non-negative integer with a bound you can prove**. Check for these signals:

- The key is a **count, length, or index** derived from the input. Frequencies are bounded by `n`, string lengths by the longest string, and positions by the array size.
- The problem states a **small fixed range**: ages 0..150, scores 0..100, lowercase letters 0..25.
- You need the **whole input grouped by key**, not only the extremes. A heap gives you the top few cheaply. Buckets give you every group in order for the same O(n).
- The interviewer asks for **better than O(n log n)** and the key has a bound. That combination almost always means buckets or counting.

A different use of the same machinery is **bucketing to compare only neighbours**. Contains Duplicate III (220) asks for two values within distance `t`. It uses buckets of width `t + 1`, keyed by `value / (t + 1)` in a hash map. Two values in the same bucket are always close enough. Values in adjacent buckets need one explicit check, and values further apart never qualify. Maximum Gap (164) uses `n - 1` buckets over `[min, max]`. By the pigeonhole principle, the largest gap cannot fall inside one bucket, so it only compares each bucket's maximum with the next non-empty bucket's minimum. In both problems you never sort the buckets. You keep just enough per bucket (a single value, or a min and max) to answer the question in O(n).

## When not to

- **The range is large or sparse.** If the key spans `0..10⁹` but there are only 1,000 elements, a bucket array has a billion slots, nearly all empty. Allocating them costs more than the sort you were avoiding. A hash map of buckets fixes the allocation, but then you have to sort its keys to read them in order, and you are back to O(m log m).
- **The data streams in or is too large to store.** A Top K over a stream wants the size-`k` min-heap: O(k) memory and an answer available at any moment. Buckets need the final counts before they can be read.
- **`k` is tiny and memory is tight.** O(n) buckets to find the top 1 is wasteful. One pass that tracks the maximum is O(1) space.
- **The keys are floats with an unknown distribution.** The range flavour's O(n) depends on uniform spread. With clustered data it is quadratic.

## Pitfalls

- **Size the array `max_key + 1`, not `max_key`.** In 347 a frequency can equal `n` (when every element is the same value), so `n` buckets overflow by one. That off-by-one shows up only on the all-equal input.
- **Read in the direction of the question.** "Most frequent" scans from the highest index down. Starting at 0 returns the least frequent values instead, and the code still runs.
- **Stop at `k` inside the inner loop.** One bucket can hold several values. Checking `k` only between buckets returns more than `k` results when ties straddle the cutoff.
- **Order within a bucket is the insertion order.** If you fill buckets from an unordered hash map, ties come out in arbitrary order. That is fine when the problem accepts any order, and wrong when it asks for a specific tie-break. In that case, sort the bucket or fill it from an ordered source.
- **Space is O(range), not O(k).** The answer may be two numbers, but the bucket array still has `n + 1` slots. Count that in the complexity you state.
- **Many small lists cost real memory.** `vector<vector<int>>` with `n + 1` mostly-empty vectors means `n + 1` headers, about 24 bytes each in C++. For large `n`, a flat counting-sort layout (counts, prefix sums, one output array) avoids this.
