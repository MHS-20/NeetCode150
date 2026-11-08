# Intervals

## The setup

An interval is a pair `[start, end]` — a meeting, a booking, a range of numbers. Problems hand you a list of them, unsorted, and ask about overlaps.

Nearly every one of these problems is solved by the same two steps: **sort, then sweep left to right in one pass.** The sort costs O(n log n) and the sweep costs O(n), so the whole solution is O(n log n) and the sort dominates. If the input arrives already sorted, the problems become O(n).

## When two intervals overlap

Getting this condition right is most of the work.

```
a = [1, 4]      b = [3, 6]          overlap: 3 ≤ 4
   ├────────┤
        ├────────┤

a = [1, 3]      b = [5, 8]          no overlap: 5 > 3
   ├────┤
             ├─────────┤
```

Two intervals `a` and `b` overlap when

```
a.start ≤ b.end   and   b.start ≤ a.end
```

If `a` is known to start no later than `b` — which is what sorting by start guarantees — the first half is automatic and the test collapses to

```
b.start ≤ a.end
```

That single comparison is the core of every merge problem. Whether to use `≤` or `<` depends on the problem's convention: if `[1,2]` and `[2,3]` are considered touching-but-not-overlapping (common for meeting rooms, where one ends as the next begins), use `<`. Read the examples in the problem statement rather than guessing.

The complementary fact is sometimes easier to reason with: two intervals **fail** to overlap only when one ends entirely before the other starts.

## Sort by start, or sort by end?

Both appear, and the choice is not arbitrary.

**Sort by start** when you are building or combining intervals as you scan — merging, inserting, detecting any conflict. Processing in start order means each new interval either extends the current one or begins a fresh one.

**Sort by end** when you are *choosing a subset* and want to leave as much room as possible for whatever comes next. Finishing earliest keeps the most remaining space, which is the greedy argument behind interval scheduling (see [`6b_greedy.md`](6b_greedy.md)).

## Merge Overlapping Intervals

Sort by start, then walk. Either the current interval overlaps the last merged one — in which case extend its end — or it does not, and starts a new block.

```
input:  [[1,3], [8,10], [2,6], [15,18]]
sorted: [[1,3], [2,6], [8,10], [15,18]]

[1,3]                       out = [[1,3]]
[2,6]   2 ≤ 3, overlap      extend → out = [[1,6]]
[8,10]  8 > 6, disjoint     append → out = [[1,6], [8,10]]
[15,18] 15 > 10, disjoint   append → out = [[1,6], [8,10], [15,18]]
```

```python
def merge(intervals):
    intervals.sort(key=lambda x: x[0])
    out = [intervals[0]]
    for start, end in intervals[1:]:
        if start <= out[-1][1]:
            out[-1][1] = max(out[-1][1], end)     # max, not end
        else:
            out.append([start, end])
    return out
```

`max(out[-1][1], end)` rather than `end` is the detail people drop. A fully contained interval like `[2,3]` inside `[1,6]` would otherwise shrink the merged block to `[1,3]`.

## Insert Interval

The list is already sorted and non-overlapping, so a single pass suffices without re-sorting — O(n). Three phases:

```
existing: [1,3]  [6,9]  [12,15]        new: [4,10]

phase 1   [1,3] ends before 4        → copy through
phase 2   [6,9] overlaps             → absorb: new becomes [4,10]
          [12,15] starts after 10    → stop absorbing
phase 3   append [4,10], then copy [12,15]

result:   [1,3]  [4,10]  [12,15]
```

```python
def insert(intervals, new):
    out, i, n = [], 0, len(intervals)
    while i < n and intervals[i][1] < new[0]:      # entirely before
        out.append(intervals[i]); i += 1
    while i < n and intervals[i][0] <= new[1]:     # overlapping
        new = [min(new[0], intervals[i][0]), max(new[1], intervals[i][1])]
        i += 1
    out.append(new)
    out.extend(intervals[i:])                      # entirely after
    return out
```

## Non-Overlapping Intervals

Remove the fewest intervals so that none overlap. Equivalent to *keeping* the most, which is the classic interval scheduling problem. **Sort by end** and greedily keep every interval that starts at or after the last kept one's end.

```
[[1,2], [2,3], [1,3], [3,4]]   sorted by end: [1,2] [2,3] [1,3] [3,4]

keep [1,2], last_end = 2
[2,3]: 2 ≥ 2  keep, last_end = 3
[1,3]: 1 < 3  overlaps → remove (count 1)
[3,4]: 3 ≥ 3  keep

removed: 1
```

Sorting by *start* here gives wrong answers: a long early interval would be kept and block several short ones behind it. Ending soonest is what leaves the most room, and the exchange argument in [`6b_greedy.md`](6b_greedy.md) is why that is provably optimal.

## Meeting Rooms

**Meeting Rooms I** — can one person attend all of them? Sort by start and check any adjacent pair for overlap. One pass.

**Meeting Rooms II** — how many rooms are needed at once? This is the maximum number of intervals overlapping at any instant. Two standard solutions.

*Min-heap of end times.* Sort by start; for each meeting, discard every heap entry that has already finished, then push this meeting's end. The heap size is the number of concurrent rooms, and its maximum is the answer. O(n log n) — see [`2f_heaps_and_priority_queues.md`](../02_data_structures/2f_heaps_and_priority_queues.md).

*Sweep line / chronological events.* Split each interval into a `+1` at its start and a `−1` at its end, sort all events by time, and scan keeping a running count.

```
[[0,30], [5,10], [15,20]]

events:  0:+1   5:+1   10:−1   15:+1   20:−1   30:−1
count:     1      2      1       2       1       0
                  ↑ peak = 2 rooms
```

The sweep is often easier to reason about, and it extends directly to related questions: car pooling capacity, the busiest time of day, maximum population alive in a given year. When start and end coincide, process the `−1` first if a room can be reused immediately.

## Complexity

| Problem | Cost | Dominated by |
|---|---|---|
| Merge Intervals | O(n log n) | the sort |
| Insert Interval (pre-sorted) | O(n) | the single pass |
| Non-Overlapping Intervals | O(n log n) | the sort |
| Meeting Rooms I | O(n log n) | the sort |
| Meeting Rooms II (heap) | O(n log n) | sort + n heap ops |
| Meeting Rooms II (sweep) | O(n log n) | sorting the events |

Space is O(n) for the output, or O(1) extra if merging in place is allowed.

## Pitfalls

- **Assigning `end` instead of `max(end, current_end)`** when merging. Breaks on nested intervals.
- **Sorting by the wrong field.** By start for merging, by end for selecting a maximum subset.
- **Getting the boundary convention wrong.** `[1,2]` and `[2,3]`: touching or overlapping? The problem's examples decide, and the answer changes by one either way.
- **Sorting the events but not the tie-break** in a sweep line. Two events at the same timestamp need a defined order, or a room is double-counted.
- **Re-sorting in Insert Interval.** The input is already sorted; sorting again turns an O(n) solution into O(n log n) for nothing.
- **Mutating the input list while iterating it** when removing overlaps. Count removals instead, or build a new list.
