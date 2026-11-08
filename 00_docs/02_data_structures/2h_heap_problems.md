# Heap Problems

A heap gives the smallest (or largest) element in O(1) and removes or inserts in O(log n). The problems in `09_heaps/` use it in four ways: a heap kept at size `k` to track the top `k`, a heap that is drained in priority order, two heaps that hold the two halves of a stream, and a heap that merges several sorted sources. How a heap works is covered in [heaps and priority queues](2g_heaps_and_priority_queues.md).

The examples follow the C++ solutions in `09_heaps/`. Every trace was produced by running the same steps on the input shown. In C++, `priority_queue<int>` is a max-heap, and `priority_queue<int, vector<int>, greater<int>>` is a min-heap.

## A heap kept at size k

### Kth Largest Element in an Array (215)

The task: find the `k`th largest value.

The solution keeps a **min-heap of the `k` largest values seen so far**. Its top is the smallest of them, which is the `k`th largest. A new value enters only if it beats that top:

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
for (int x : nums) {
    if ((int)pq.size() < k)
        pq.push(x);
    else if (x > pq.top()) {
        pq.pop();
        pq.push(x);
    }
}
return pq.top();
```

A min-heap is used to find the **largest** values because the value to throw out is always the smallest of the current top `k`, and a min-heap gives that one directly.

For `nums = [3, 2, 1, 5, 6, 4]`, `k = 2`:

```
x   action          heap      top
3   push            3          3
2   push            2 3        2
1   1 < 2: ignore   2 3        2
5   replace top     3 5        3
6   replace top     5 6        5
4   4 < 5: ignore   5 6        5
```

The answer is 5. The heap never holds more than `k` values, so this costs O(n log k) time and O(k) space. Sorting would cost O(n log n).

### Kth Largest Element in a Stream (703)

The same heap, kept between calls. The constructor builds the heap from the initial values and pops down to `k`. Each `add` pushes the new value, pops if the heap has more than `k`, and returns the top. Each call costs O(log k).

### K Closest Points to Origin (973)

The task: return the `k` points closest to `(0, 0)`.

This is the same pattern with the opposite heap. To keep the `k` **smallest** distances, the solution uses a **max-heap** of size `k`: the point to throw out is always the farthest of the current `k`. Each point is pushed, and the heap pops its largest distance whenever it holds more than `k`.

For `points = [[3, 3], [5, -1], [-2, 4]]`, `k = 2`, with squared distances 18, 26 and 20:

```
point     distance²   heap after (distance²)
[3, 3]       18        18
[5, -1]      26        18 26
[-2, 4]      20        18 20 26 → pop 26 → 18 20
```

The answer is `[[3, 3], [-2, 4]]`.

The repo's solution computes `sqrt(x² + y²)` as a `double`. The square root is not needed: if one distance is smaller than another, its square is smaller too. Comparing `x² + y²` as integers gives the same order without the square root or floating-point values.

## Draining a heap in priority order

### Last Stone Weight (1046)

The task: repeatedly smash the two heaviest stones. Equal stones both disappear. Otherwise the lighter one disappears and the heavier one loses that weight. Return the last stone's weight, or 0.

Every step needs the two heaviest stones, so a max-heap holds them all:

```
stones [2, 7, 4, 1, 8, 1]
smash 8 and 7   →  1 left    heap: 4 2 1 1 1
smash 4 and 2   →  2 left    heap: 2 1 1 1
smash 2 and 1   →  1 left    heap: 1 1 1
smash 1 and 1   →  none      heap: 1
```

The answer is 1. Building the heap from the array costs O(n), and each of up to `n` smashes costs O(log n).

### Task Scheduler (621)

The task: run tasks labelled by letters, one per time unit. Two runs of the same letter must be at least `n` units apart, and a unit can be left idle. Find the shortest total time.

**The greedy rule:** at each unit, run the available task with the **most** copies left. The letter with the most copies is the one most likely to force idle time at the end, so it is spread out first.

The repo's solution simulates this with two structures:

- a **max-heap** of `(copies left, letter)` for the letters that can run now;
- a **queue** of `(letter, time it becomes available)` for letters that are cooling down. Every letter in it waits the same `n`, so they leave the queue in the order they entered.

At each time unit, a letter whose cooldown has ended moves from the queue back to the heap. Then the top of the heap runs, and if it has copies left it joins the queue with available time `time + n + 1`. If the heap is empty, the unit is idle.

For `tasks = "AAABBB"`, `n = 2`:

```
time   runs    note
 0      A
 1      B
 2      idle   A and B are both cooling down
 3      A
 4      B
 5      idle
 6      A
 7      B
```

The total is 8. For `"AAABBBCCDE"` with `n = 2`, the same rule gives `A B C A B C A B D E`, 10 units with no idle time.

**The formula.** Let `m` be the largest count, and `k` the number of letters that have it. The most frequent letter needs `m - 1` gaps of `n` units after each run, plus one slot at the end for each letter with count `m`:

```
answer = max(len(tasks), (m - 1) * (n + 1) + k)
```

For `"AAABBB"`: `m = 3`, `k = 2`, so `(3 - 1) * 3 + 2 = 8`. When there are enough other tasks to fill every gap, no time is idle and the answer is the number of tasks: `"AAABBBCCDE"` gives `max(10, 8) = 10`. The formula and the simulation agreed on all three test inputs, including `"AAABBBCCDDEE"` with answer 12.

The simulation costs O(T log 26) for `T` time units, and the formula O(number of tasks).

## Two heaps: Find Median from Data Stream (295)

The task: add numbers one at a time, and return the median of all numbers so far at any point.

The solution splits the numbers into two halves:

- `lo`, a **max-heap** of the smaller half. Its top is the largest of the small numbers.
- `hi`, a **min-heap** of the larger half. Its top is the smallest of the large numbers.

The two tops are the two middle values. `lo` is kept equal in size to `hi` or one larger:

```
lo (max-heap)            hi (min-heap)
   1  3  [5]        |       [8]  15
          ↑ top         top ↑
odd count: the median is lo's top, 5
```

```cpp
void addNum(int num) {
    lo.push(num);
    hi.push(lo.top());          // the largest of lo moves to hi
    lo.pop();
    if (hi.size() > lo.size()) {
        lo.push(hi.top());      // rebalance so lo is never smaller
        hi.pop();
    }
}
double findMedian() {
    if (lo.size() > hi.size()) return lo.top();
    return (lo.top() + hi.top()) / 2.0;
}
```

Every new number goes through `lo` and then to `hi`. This makes sure that every value in `lo` is at most every value in `hi`, wherever the new number belongs. The last step moves one value back if `hi` has become larger.

For the stream `5, 15, 1, 3, 8`:

```
add   lo        hi       median
 5    5         —          5
15    5         15        10
 1    1 5       15         5
 3    1 3       5 15       4
 8    1 3 5     8 15       5
```

Each `addNum` does up to three pushes and pops, O(log n). `findMedian` reads the two tops, O(1).

**The follow-up with small values.** If every number is between 0 and 100, the repo's follow-up solution keeps a count per value instead of heaps. `addNum` is O(1), and `findMedian` walks the 101 counts to find the middle value or values, which is O(101), a constant.

## Merging sorted sources: Design Twitter (355)

`getNewsFeed` returns the 10 most recent tweets from a user and everyone they follow. Each user's tweets are stored in posting order, so each user's list is already sorted by time. The task is to merge several sorted lists and stop after 10, the same problem as [Merge k Sorted Lists](../06_linked_lists/6c_reorder_and_merge.md#merge-k-sorted-lists-23).

The repo's second solution pushes the **newest** tweet of each followed user into a max-heap keyed by timestamp, with the user and the index of that tweet in their list. Each pop takes the newest remaining tweet, then pushes the same user's next older tweet:

```cpp
for (int user : users)
    if (!tweets[user].empty())
        pq.push({time, tweetId, user, lastIndex});
while (!pq.empty() && res.size() < 10) {
    auto [time, tweetId, user, idx] = pq.top();
    pq.pop();
    res.push_back(tweetId);
    if (idx > 0)
        pq.push({older time, older tweetId, user, idx - 1});
}
```

With `f` followed users, the heap holds at most `f` entries, and the loop runs at most 10 times. The feed costs O(f log f) to build the heap plus O(10 log f) for the pops, however many tweets each user has.
