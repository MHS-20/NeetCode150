# Intervals: Scheduling, Rooms and Queries

These problems ask more than "do two intervals overlap". They ask which intervals to keep, how many overlap at the busiest moment, or which interval covers a given point. Each one adds a second tool to the sort-and-scan from [overlap and merge](10a_overlap_and_merge.md): a greedy rule, a min-heap of end times, or a list of events.

The examples follow the C++ solutions in `16_intervals/`. Every trace was produced by running the same steps on the input shown.

## Non-overlapping Intervals (435)

The task: remove the fewest intervals so that the rest do not overlap. Touching intervals, like `[1, 2]` and `[2, 3]`, do not overlap.

Removing the fewest is the same as keeping the most, which is **interval scheduling**. The greedy rule that solves it is to keep the interval that ends earliest, then repeat on what is left. The exchange-argument proof is in [greedy proofs](../09_greedy/9a_proofs.md#example-interval-scheduling).

### The repo's version: sort by start, keep the earlier end

The repo sorts by **start** instead, and fixes up its choice as it goes. When a new interval overlaps the last kept one, only one of the two can stay, and it keeps the one that **ends earlier**:

```cpp
sort(intervals.begin(), intervals.end());
for (auto &cur : intervals) {
    if (result.empty() || result.back()[1] <= cur[0]) {
        result.push_back(cur);                 // no overlap: keep
        continue;
    }
    if (result.back()[1] > cur[1]) {           // overlap: keep the earlier end
        result.pop_back();
        result.push_back(cur);
    }
}
return intervals.size() - result.size();
```

Replacing the kept interval by one that ends earlier never hurts. The new one ends sooner, so it leaves at least as much room for every interval after it. This is the same choice as the sort-by-end rule, made one overlap at a time.

For `[[1, 100], [11, 22], [1, 11], [2, 12]]`, sorted by start to `[[1, 11], [1, 100], [2, 12], [11, 22]]`:

```
interval    last kept    overlap?       action
[1, 11]        —            —           keep
[1, 100]    [1, 11]      1 < 11: yes    100 > 11: drop [1, 100]
[2, 12]     [1, 11]      2 < 11: yes    12 > 11: drop [2, 12]
[11, 22]    [1, 11]      11 >= 11: no   keep
```

Two intervals are kept, so two are removed.

### What goes wrong with "keep the first one"

Keeping whichever interval came first and dropping the new one gives a wrong answer. In the sorted list above, if `[1, 100]` had been first, it would block `[11, 22]`, and only one interval would be kept. The repo's comparison `result.back()[1] > cur[1]` is what prevents this: a long interval is always replaced by a shorter overlapping one.

## Meeting Rooms II (253)

The task: find the smallest number of rooms that can hold every meeting. That is the largest number of meetings in progress at the same moment.

### With a min-heap of end times

Sort the meetings by start. The heap holds the end times of the meetings in progress, so its size is the number of rooms in use. For each meeting, first remove every meeting that has ended by its start time, then add its own end:

```cpp
sort by start;
priority_queue<int, vector<int>, greater<>> minHeap;     // smallest end on top
for (const auto &m : intervals) {
    while (!minHeap.empty() && minHeap.top() <= m.start)
        minHeap.pop();                                    // that room is free again
    minHeap.push(m.end);
    mx = max(mx, (int)minHeap.size());
}
```

The heap keeps the earliest end on top, so finished meetings are found without searching. A meeting that ends exactly when another starts frees its room (`<=`).

For `[[0, 30], [5, 10], [15, 20]]`:

```
meeting    ends removed   heap (end times)   rooms in use   max
[0, 30]        —            30                    1          1
[5, 10]        —            10, 30                2          2
[15, 20]       10           20, 30                2          2
```

The answer is 2. The sort and the `n` heap operations each cost O(n log n). Heaps are covered in [heaps](../02_data_structures/2g_heaps_and_priority_queues.md).

### With a sweep over events

Split every meeting into two **events**: `+1` at its start and `-1` at its end. Sort all events by time and add them up in order. The running total is the number of meetings in progress, and its maximum is the answer:

```
meetings:  [0, 30]  [5, 10]  [15, 20]

time     0    5    10    15    20    30
event   +1   +1    -1    +1    -1    -1
total    1    2     1     2     1     0
              ↑ maximum: 2 rooms
```

When an end and a start happen at the same time, the `-1` has to come first if a room can be reused immediately. Otherwise the total briefly counts both meetings.

The sweep costs O(n log n) for sorting the `2n` events, the same as the heap. It also answers related questions directly: the busiest moment, the capacity needed for car pooling, the year with the most people alive.

## Minimum Interval to Include Each Query (1851)

The task: for each query point `q`, find the size of the smallest interval `[l, r]` with `l <= q <= r`, or -1 if none. The size of `[l, r]` is `r - l + 1`.

Checking every interval for every query costs O(n · q). The solution processes the queries **offline**: in increasing order instead of the order given, which lets it reuse work between queries. It writes each answer back to the query's original position.

With queries in increasing order and intervals sorted by start:

1. **Add** every interval whose start is at most `q` to a min-heap of `(size, end)`. These are the intervals that start in time for `q`. An interval added for an earlier query stays, because it also starts in time for every later query.
2. **Remove** from the top of the heap every interval whose end is less than `q`. It ended before `q`, and every later query is larger, so it can never cover a later query either.
3. The top of the heap is the smallest interval that covers `q`.

```cpp
sort(intervals.begin(), intervals.end());
// idx = query indices sorted by query value
for (int j : idx) {
    int q = queries[j];
    while (i < n && intervals[i][0] <= q) {
        minHeap.push({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
        i++;
    }
    while (!minHeap.empty() && minHeap.top().second < q)
        minHeap.pop();
    result[j] = minHeap.empty() ? -1 : minHeap.top().first;
}
```

Step 2 only removes intervals from the **top**. An interval that has ended can stay deeper in the heap. It does no harm there: if it ever reaches the top, step 2 removes it then. This is called **lazy deletion**.

For intervals `[[1, 4], [2, 4], [3, 6], [4, 4]]` and queries `[2, 3, 4, 5]`:

```
q   added                 removed from top          heap (size, end)                  answer
2   [1,4] [2,4]           —                         (3,4) (4,4)                         3
3   [3,6]                 —                         (3,4) (4,4) (4,6)                   3
4   [4,4]                 —                         (1,4) (3,4) (4,4) (4,6)             1
5   —                     (1,4) (3,4) (4,4)         (4,6)                               4
```

The answers are `[3, 3, 1, 4]`. At `q = 5`, the three intervals that end at 4 come off the top one after another, and `[3, 6]` covers 5.

Sorting costs O(n log n + q log q). Each interval enters and leaves the heap at most once, for O(n log n). The total is O((n + q) log n + q log q).
