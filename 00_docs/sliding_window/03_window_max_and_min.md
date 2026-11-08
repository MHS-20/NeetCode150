# The Maximum of a Sliding Window

Sliding Window Maximum (239) asks for the largest value in every window of length `k`. A running sum can be updated when an element leaves by subtracting it, but a running maximum cannot. When the largest element leaves, the next largest is not known without looking at the rest of the window. Rescanning the window at each step costs O(k), and O(n · k) in total. A **monotonic deque** keeps, in order, the only elements that can still become the maximum, and gives the answer for each window in O(1) amortised time.

A deque is a list with push and pop at both ends, explained in [`queues_and_deques.md`](../data_structures/queues_and_deques.md#the-deque). The trace on this page was produced by running the repo's C++ solution logic on the input shown.

## Which elements can still be the maximum

Take two elements in the window, at indices `i < j`, with `nums[i] <= nums[j]`. Element `i` leaves the window before element `j`, because it is further left. While both are in the window, `j` is at least as large. So `i` can never be the maximum of any window from now on, and can be thrown away.

Throwing away such elements leaves a list whose values decrease from front to back. The front is the largest element in the window.

## The solution

The deque stores **indices**, not values. The index is needed to tell when an element has left the window.

```cpp
for (int i = 0; i < nums.size(); i++) {
    if (!dq.empty() && dq.front() < i - k + 1)
        dq.pop_front();                       // 1. front has left the window
    while (!dq.empty() && nums[i] > nums[dq.back()])
        dq.pop_back();                        // 2. smaller elements can never be the max
    dq.push_back(i);                          // 3. the new element joins at the back
    if (i >= k - 1)
        maxs.push_back(nums[dq.front()]);     // 4. the front is the max of the window
}
```

The window is `nums[i - k + 1 .. i]`.

- **Step 1** removes the front index if it is to the left of the window. At most one index leaves per step, because the window moves by one.
- **Step 2** removes from the back every element smaller than the new one, by the argument above.
- **Step 3** adds the new index. The deque is still in decreasing order, because everything smaller than the new element was just removed.
- **Step 4** reads the answer once the first full window is reached.

Step 2 pops only elements that are strictly smaller (`>`), so an element equal to the new one stays, and the deque can hold equal values side by side. Popping equal elements as well (`>=`) gives the same maximums.

## Trace

`nums = [1, 3, -1, -3, 5, 3, 6, 7]`, `k = 3`:

```
 i  nums[i]  removed                  deque (indices)  deque (values)  window          max
 0     1     —                        [0]              [1]             —                —
 1     3     back: 0 (1 < 3)          [1]              [3]             —                —
 2    -1     —                        [1, 2]           [3, -1]         [1, 3, -1]       3
 3    -3     —                        [1, 2, 3]        [3, -1, -3]     [3, -1, -3]      3
 4     5     front: 1 (left window)   [4]              [5]             [-1, -3, 5]      5
             back: 3, 2 (< 5)
 5     3     —                        [4, 5]           [5, 3]          [-3, 5, 3]       5
 6     6     back: 5, 4 (< 6)         [6]              [6]             [5, 3, 6]        6
 7     7     back: 6 (< 7)            [7]              [7]             [3, 6, 7]        7
```

The output is `[3, 3, 5, 5, 6, 7]`.

At `i = 4`, index 1 (value 3) is at the front, but the window now starts at index 2, so step 1 removes it. Then 5 is larger than -3 and -1, so step 2 removes both.

At `i = 3`, the deque holds three indices, and index 1 is still the maximum. Indices 2 and 3 are kept because they are smaller and to the right of 1: once index 1 leaves the window, one of them can become the maximum.

## Why the cost is O(n)

Step 2 is a loop and can pop many elements in one step: at `i = 4` it pops two. But each index is pushed once, in step 3, and popped at most once, either in step 1 or in step 2. Over the whole pass there are `n` pushes and at most `n` pops, so the total work is O(n). Each window costs O(1) **amortised**: the cost averaged over all steps, even though a single step can cost more.

The deque holds at most `k` indices, so the extra space is O(k).

## The minimum of a window

For the minimum, the comparison in step 2 is reversed: pop from the back while `nums[i] < nums[dq.back()]`. The deque then increases from front to back, and the front is the smallest element in the window.

The same deque works for windows whose size changes, as long as both ends only move forward. Step 1 then pops from the front while the front index is less than `left`, instead of checking against `i - k + 1`.
