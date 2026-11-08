# Intervals: Overlap, Merging and Inserting

An interval is a pair `[start, end]`: a meeting, a booking, a range of numbers. Interval problems give a list of them, usually unsorted, and ask about overlaps. Almost all of them are solved in two steps: **sort, then scan once from left to right**. The sort costs O(n log n) and the scan O(n), so the sort decides the total. The work is in choosing the sort key and writing the overlap test correctly.

The examples follow the C++ solutions in `16_intervals/`. Every trace was produced by running the same steps on the input shown. Selecting intervals and counting rooms are covered in [scheduling and rooms](10b_scheduling_and_rooms.md).

## When two intervals overlap

```
a = [1, 4]   b = [3, 6]          a = [1, 3]   b = [5, 8]
  |-------|                        |-----|
       |-------|                             |-------|
  overlap: 3 <= 4                  no overlap: 5 > 3
```

Two intervals `a` and `b` overlap when each starts before the other ends:

```
a.start <= b.end   and   b.start <= a.end
```

They fail to overlap only when one ends before the other starts.

If the intervals are sorted by start, so that `a.start <= b.start`, the first half of the test always holds: `a.start <= b.start <= b.end`. The test then becomes one comparison:

```
b.start <= a.end
```

### Touching intervals

Whether `[1, 2]` and `[2, 3]` overlap depends on the problem, and the answer changes the result by one. Merge Intervals (56) treats them as overlapping and merges them into `[1, 3]`. Meeting Rooms (252) treats a meeting that ends at 2 and one that starts at 2 as compatible. The examples in the problem statement decide it, and the comparison is `<=` or `<` accordingly.

## Merge Intervals (56)

The task: merge all overlapping intervals.

After sorting by start, each interval either overlaps the last merged block, and extends it, or starts after it, and begins a new block:

```cpp
sort(intervals.begin(), intervals.end());
vector<vector<int>> result;
for (const auto &cur : intervals) {
    if (result.empty() || result.back()[1] < cur[0])
        result.push_back(cur);                               // starts after the block ends
    else
        result.back()[1] = max(result.back()[1], cur[1]);    // extend the block
}
```

`sort` on a vector of vectors compares the first elements, then the second, so this sorts by start.

For `[[1, 3], [8, 10], [2, 6], [15, 18]]`, sorted to `[[1, 3], [2, 6], [8, 10], [15, 18]]`:

```
interval   block end   overlaps?      result
[1, 3]        —           —           [1,3]
[2, 6]        3        2 <= 3: yes    [1,6]
[8, 10]       6        8 > 6: no      [1,6] [8,10]
[15, 18]     10        15 > 10: no    [1,6] [8,10] [15,18]
```

### Why `max` and not the new end

The block's new end is `max(block end, cur[1])`, not `cur[1]`. An interval can lie entirely inside the block. For `[[1, 6], [2, 3]]`, assigning `cur[1]` would shrink the block from `[1, 6]` to `[1, 3]` and lose `[4, 6]`.

### Why sorting by start is needed

Without sorting, an interval can overlap a block that was closed earlier. In `[[1, 3], [8, 10], [2, 6]]`, the scan would see `[2, 6]` after `[8, 10]` and compare it only with `[8, 10]`. Sorting by start guarantees that every interval which can join a block comes right after it.

## Insert Interval (57)

The task: the intervals are already sorted and do not overlap. Insert a new interval and merge where needed.

Sorting again would cost O(n log n). The input is already sorted, so one pass in three phases is enough:

```cpp
// 1. intervals that end before the new one starts
while (i < n && intervals[i][1] < newInterval[0])
    result.push_back(intervals[i++]);
// 2. intervals that overlap the new one: absorb them
while (i < n && intervals[i][0] <= newInterval[1]) {
    newInterval[0] = min(newInterval[0], intervals[i][0]);
    newInterval[1] = max(newInterval[1], intervals[i][1]);
    i++;
}
result.push_back(newInterval);
// 3. intervals that start after the new one ends
while (i < n)
    result.push_back(intervals[i++]);
```

For `[[1, 3], [6, 9], [12, 15]]` and the new interval `[4, 10]`:

```
phase 1   [1, 3] ends at 3, before 4            → copy
phase 2   [6, 9] starts at 6 <= 10              → absorb: new stays [4, 10]
          [12, 15] starts at 12 > 10            → stop
          append [4, 10]
phase 3   copy [12, 15]

result:   [1, 3]  [4, 10]  [12, 15]
```

Phase 2 uses `min` for the start as well as `max` for the end. The first absorbed interval can start before the new one, as in inserting `[4, 8]` into `[[3, 5]]`, which gives `[3, 8]`.

The cost is O(n), and the output takes O(n) space.

## Meeting Rooms (252)

The task: can one person attend every meeting? That is, do any two meetings overlap?

After sorting by start, two meetings can only overlap if they are next to each other in the sorted order, so checking each adjacent pair is enough:

```cpp
sort by start;
for (int i = 0; i + 1 < intervals.size(); i++)
    if (intervals[i].end > intervals[i + 1].start)
        return false;
return true;
```

The test is `>`, so a meeting that ends at 10 and one that starts at 10 do not conflict.

**Why adjacent pairs are enough.** If meeting `i` overlaps a later meeting `j`, then meeting `i + 1`, which starts between them, also starts before `i` ends. So an overlap anywhere shows up as an overlap between some adjacent pair.

## Cost

| Problem | Time | Dominated by |
|---|---|---|
| Merge Intervals (56) | O(n log n) | the sort |
| Insert Interval (57) | O(n) | one pass; the input is sorted |
| Meeting Rooms (252) | O(n log n) | the sort |

## Common mistakes

- **Assigning the new end instead of the larger one** when merging. Nested intervals shrink the block.
- **Getting the touching case wrong.** `[1, 2]` and `[2, 3]` overlap in some problems and not in others.
- **Sorting again in Insert Interval.** The input is already sorted.
- **Sorting by the wrong field.** Merging needs start order. Choosing the most intervals that do not overlap needs end order ([scheduling and rooms](10b_scheduling_and_rooms.md#non-overlapping-intervals-435)).
