# Monotonic Stack

Many array problems ask, for every element, about the **nearest** element to one side that is larger or smaller: the next warmer day, the first shorter bar, the next taller wall. Scanning outward from each element costs O(n) per element and O(n²) in total. A **monotonic stack** answers the question for every element in one O(n) pass. It holds the elements still waiting for an answer, and keeps them sorted so that the newest element can settle all of the ones it answers in a single run of pops.

What a stack is and how it is implemented is in [`stacks.md`](stacks.md). The examples here follow the C++ solutions in `04_stacks/` and `02_two_pointers/`, and every trace was produced by running the loop shown.

## Next greater element

The task: for each element, find the first element to its right that is larger. Return -1 if there is none.

The stack holds the indices of elements that have not found their next greater element yet. When a new element `x` arrives, it is the answer for every waiting element smaller than `x`. Those are popped and given `x` as their answer. Then `x` is pushed, to wait for its own answer.

```cpp
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[i] > a[st.top()]) {
        answer[st.top()] = a[i];      // a[i] is the next greater for the top
        st.pop();
    }
    st.push(i);
}
// indices still on the stack have no next greater element
```

### Why the stack stays sorted

Before `x` is pushed, every element on the stack smaller than `x` has been popped. So the element below `x` on the stack is at least as large as `x`. That holds at every push, so the values on the stack never increase from bottom to top. This is what makes it a **monotonic** stack (a *decreasing* one here).

The sorted order is also why the pops can stop at the first element that is not smaller than `x`. Every element below it is at least as large, so none of them can be answered by `x` either.

### Trace

`a = [2, 1, 5, 3]`:

```
x    popped (answer = x)     stack (values, bottom → top)
2    —                       [2]
1    —                       [2, 1]          1 < 2: 1 waits on top of 2
5    1 → 5, then 2 → 5       [5]
3    —                       [5, 3]
end                          5 and 3 have no next greater: -1
```

The answer is `[5, 5, -1, -1]`.

### Why the cost is O(n)

The inner `while` can pop many elements for one `i`. But each index is pushed once and popped at most once over the whole pass, so the total number of pops is at most `n`. The whole pass is O(n), and each element costs O(1) amortised: averaged over the pass, even if one step pops many elements.

### The four variants

The direction of the scan and the comparison change which question is answered:

| Question | Scan | Pop while | Stack order (bottom → top) |
|---|---|---|---|
| next greater to the right | left to right | `a[i] > a[top]` | decreasing |
| next smaller to the right | left to right | `a[i] < a[top]` | increasing |
| previous greater to the left | left to right | `a[i] >= a[top]`, then read the top | decreasing |
| previous smaller to the left | left to right | `a[i] <= a[top]`, then read the top | increasing |

For the "previous" variants, the answer for `a[i]` is the element left on top **after** the pops, before `a[i]` is pushed. Popping equal elements (`>=` or `<=`) makes the top strictly greater or strictly smaller.

## Daily Temperatures (739): store indices

The task: for each day, find how many days until a warmer temperature. That is next greater element, but the answer is a **distance**, so the stack must hold indices. With values alone, the position of the popped day would be lost.

```cpp
while (!st.empty() && temps[i] > temps[st.top()]) {
    res[st.top()] = i - st.top();
    st.pop();
}
st.push(i);
```

For `temps = [73, 74, 75, 71, 69, 72, 76, 73]`:

```
i   temp   popped (index: days to wait)   stack (indices)   stack (temps)
0    73    —                              [0]               [73]
1    74    0: 1                           [1]               [74]
2    75    1: 1                           [2]               [75]
3    71    —                              [2, 3]            [75, 71]
4    69    —                              [2, 3, 4]         [75, 71, 69]
5    72    4: 1, 3: 2                     [2, 5]            [75, 72]
6    76    5: 1, 2: 4                     [6]               [76]
7    73    —                              [6, 7]            [76, 73]
```

Days 6 and 7 stay on the stack and keep the default 0. The answer is `[1, 1, 4, 2, 1, 1, 0, 0]`.

## Largest Rectangle in Histogram (84): both neighbours at once

The task: bars of width 1 have heights `heights[i]`. Find the area of the largest rectangle inside the histogram.

The largest rectangle that uses the full height of bar `i` extends left and right until it reaches a shorter bar on each side. Its width is the gap between the **previous smaller** bar and the **next smaller** bar:

```
width(i) = nextSmaller(i) - prevSmaller(i) - 1
area(i)  = heights[i] * width(i)
```

The answer is the largest `area(i)`. One increasing stack finds both neighbours in the same pass:

- **Next smaller.** Bar `idx` is popped when a shorter bar `i` arrives. So `i` is the next smaller bar of `idx`.
- **Previous smaller.** After `idx` is popped, the bar now on top of the stack is the nearest bar to the left that is shorter than `idx`. If the stack is empty, there is none, and the left edge is `-1`.

```cpp
while (!st.empty() && heights[st.top()] > heights[i]) {
    int idx = st.top();
    st.pop();
    int prev = st.empty() ? -1 : st.top();
    int width = (i - 1) - (prev + 1) + 1;     // i - prev - 1
    maxArea = max(maxArea, heights[idx] * width);
}
st.push(i);
```

Bars still on the stack at the end have no shorter bar to their right, so their rectangles reach the end of the array. The solution pops them in a second loop with `n` as the right edge.

For `heights = [2, 1, 5, 6, 2, 3]`:

```
right edge  popped bar (height)  left edge (prev)  width  area   best
i = 1       0 (2)                -1                 1      2      2
i = 4       3 (6)                 2                 1      6      6
i = 4       2 (5)                 1                 2     10     10
end, n = 6  5 (3)                 4                 1      3     10
end, n = 6  4 (2)                 1                 4      8     10
end, n = 6  1 (1)                -1                 6      6     10
```

The answer is 10: bars 2 and 3, height 5, width 2.

## Trapping Rain Water (42), solution 3: water in layers

[Two pointers](../two_pointers/01_opposite_ends.md#trapping-rain-water-42-which-side-is-already-known) computes the water column by column. The stack solution computes it in horizontal layers instead.

The stack holds bar indices with heights that do not increase from bottom to top. When a taller bar `i` arrives, the bar on top of the stack is the **bottom** of a pool. The bar below it on the stack is the pool's left wall, and `i` is its right wall:

```cpp
while (!st.empty() && height[i] > height[st.top()]) {
    int bottom = st.top();
    st.pop();
    if (st.empty())
        break;                                   // no left wall: water runs off
    int left = st.top();
    int width = i - left - 1;
    int depth = min(height[left], height[i]) - height[bottom];
    total += width * depth;
}
st.push(i);
```

Each pop fills one layer: the water between the two walls, above the bottom bar and up to the lower wall.

For `height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]`:

```
right wall i  bottom  left wall  width  depth                       water  total
     3           2        1        1    min(1, 2) - 0 = 1              1      1
     6           5        4        1    min(1, 1) - 0 = 1              1      2
     7           6        4        2    min(1, 3) - 1 = 0              0      2
     7           4        3        3    min(2, 3) - 1 = 1              3      5
    10           9        8        1    min(2, 2) - 1 = 1              1      6
```

The total is 6, the same as the column-by-column solutions. At `i = 7`, the layer with depth 0 is the pool whose bottom has already been filled up to height 1 by the layer at `i = 6`. The next pop then adds the layer from height 1 to height 2, 3 bars wide.

## Car Fleet (853): a stack of arrival times

The task: cars at `position[i]` drive towards `target` at `speed[i]`. A car that catches up with a slower car ahead cannot pass it, and from then on they drive together as one **fleet**. Find how many fleets arrive.

The solution sorts the cars by position and goes from the car closest to the target backwards. For each car it computes the time it would take to arrive alone, `(target - position) / speed`.

- If that time is **greater** than the time of the fleet just ahead, the car never catches up. It starts a new fleet and its time is pushed.
- Otherwise it catches up with the fleet ahead and joins it, arriving with it. Nothing is pushed.

The times on the stack only increase from bottom to top, so the stack is monotonic, but no pops happen. The number of fleets is the size of the stack.

For `target = 12`, `position = [10, 8, 0, 5, 3]`, `speed = [2, 4, 1, 1, 3]`:

```
position  speed  time alone       result               stack (times)
   10       2    (12-10)/2 = 1    new fleet            [1]
    8       4    (12-8)/4  = 1    joins fleet ahead    [1]
    5       1    (12-5)/1  = 7    new fleet            [1, 7]
    3       3    (12-3)/3  = 3    joins fleet ahead    [1, 7]
    0       1    (12-0)/1  = 12   new fleet            [1, 7, 12]
```

The answer is 3.

Only the top of the stack is ever compared. A single variable holding the slowest time so far gives the same count. The stack is useful when the times of the fleets are needed afterwards.

## Max Chunks To Make Sorted II (768): merging with the stack

The task: split the array into as many pieces (chunks) as possible such that sorting each piece on its own, then joining them, gives the sorted array.

The stack holds one value per chunk: that chunk's maximum. The chunks are valid when their maximums never decrease from bottom to top, because every chunk must contain only values no larger than the values in later chunks.

When a new value `x` arrives:

- If `x` is at least the top maximum, it starts a new chunk and is pushed.
- If `x` is smaller, it must belong to the same chunk as every earlier chunk whose maximum is larger than `x`. The solution saves the top maximum, pops every chunk with a maximum larger than `x`, and pushes the saved maximum back as the maximum of the merged chunk.

```cpp
if (st.empty() || x >= st.top()) {
    st.push(x);
} else {
    int mx = st.top();
    st.pop();
    while (!st.empty() && x < st.top())
        st.pop();
    st.push(mx);
}
```

For `arr = [1, 1, 0, 0, 1]`:

```
x    action                                         stack (chunk maximums)
1    new chunk                                      [1]
1    new chunk (1 >= 1)                             [1, 1]
0    0 < 1: merge, pop the other 1 too              [1]
0    0 < 1: merges into the only chunk              [1]
1    new chunk (1 >= 1)                             [1, 1]
```

The answer is 2: `[1, 1, 0, 0]` and `[1]`.

Max Chunks To Make Sorted (769) is the same problem for a permutation of `0..n-1`. The repo's solution uses the same stack with strict comparisons, because the values are distinct. Both problems also have a solution with a prefix maximum and a suffix minimum: a cut after position `i` is valid when `max(arr[0..i]) <= min(arr[i+1..])`.

## A stack that also drops from the front

All the examples above keep every waiting element until a later element answers it. In a sliding window, elements also leave from the front when the window moves past them. That needs a deque: the same pops from the back, plus pops from the front. Sliding Window Maximum (239) uses it, traced in [window maximum](../sliding_window/03_window_max_and_min.md).

## Common mistakes

- **Storing values when the answer needs a distance or a width.** Daily Temperatures and Largest Rectangle need positions, so the stack holds indices and reads values through them.
- **Forgetting the elements left on the stack.** They are the elements with no answer. Daily Temperatures leaves them at 0. Largest Rectangle has to pop them with the array end as the right edge, or it misses rectangles that reach the end: in the trace above, three of the six areas come from that final loop.
- **Mixing up `>` and `>=` in the pop condition.** It decides how equal values are handled. For "next greater", popping on `>` leaves equal values waiting, which is correct: an equal value is not greater.
- **Reading the nested loop as O(n²).** Count pushes and pops over the whole pass: at most `n` of each.
