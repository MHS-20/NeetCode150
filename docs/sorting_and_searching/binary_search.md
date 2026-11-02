# Binary Search

## What it solves

Binary search finds a position in O(log n) by halving the range of candidates at every step. Each comparison at `mid` throws away the half that cannot contain the answer.

It needs one property: a **monotonic predicate**. Some yes/no condition `P(x)` is false for every candidate up to some point, and true for every candidate after it:

```
x:      0  1  2  3  4  5  6  7
P(x):   F  F  F  F  T  T  T  T
                    ↑ first true: the boundary binary search finds
```

A sorted array is one source of such a predicate: `P(i) = arr[i] >= target`. It is not the only one. The candidates can be speeds, capacities, timestamps or split positions, as long as checking `P` at one point tells you which side the answer is on. Every problem in this lesson comes down to choosing `P` and finding where it flips.

It also needs **random access**. Halving a range means jumping to its middle in O(1), which works on arrays, on numeric ranges, and on anything indexable. On a linked list, reaching the middle costs O(n), and the O(log n) is lost.

## The core loop shape

Two closed-range variables `i` and `j` bound the region you still need to check:

```cpp
int i = 0, j = n - 1;
while (i <= j) {
    int mid = i + (j - i) / 2;
    // compare arr[mid] to what you're looking for
    // update i or j
}
```

`mid` is written `i + (j - i) / 2`, not `(i + j) / 2`. Both give the same value, but `i + j` can overflow a 32-bit `int` when both indices are above about 1.07 × 10⁹, which is common when searching a numeric range rather than an array. The overflowed sum is negative, and `mid` becomes a negative index.

Getting a binary search right means getting three moving parts right: the loop condition, the bounds you start with, and what you do with `mid` after checking it.

## `i <= j` vs `i < j`

Ask: **can the region I'm searching ever legitimately be exactly one element wide, and does that element still need to be checked?**

- If yes, because you're looking for an exact value and a single remaining candidate could be it, use `i <= j` (a closed range). This is the standard "search for a value" pattern.
- If you're narrowing toward a *boundary* rather than testing a candidate value directly (e.g. "find the first index where some condition flips from false to true"), use a half-open range `[i, j)` with `i < j`, where `j` starts at `n` (one past the end) instead of `n - 1`.

The half-open range is needed for boundary searches, not just tidier. A boundary search must be able to answer "no element qualifies", and that answer is `n`, the position just past the end. The closed range `[0, n - 1]` has no slot for it. The half-open range `[0, n)` does.

Both styles are valid. The mistake is mixing them: a half-open bound (`j = n`) with a closed-range condition (`i <= j`). That loop can reach `i == j == n`, compute `mid = n`, and read `arr[n]`, one element past the end of the array.

## Setting up the initial bounds

A frequent bug is writing `i = 0, j = n - 1` automatically, without asking what the problem actually allows. Before coding the bounds, state in words: *"given the constraints of this problem, which indices am I actually allowed to land on?"*

Example: Two Sum II on a sorted array, solved by binary search. For each `arr[k]`, search the array for `target - arr[k]`. The second number cannot be `arr[k]` itself, so the valid range for the search isn't `[0, n-1]`. It's `[k+1, n-1]`, because index `k` is already spoken for. Starting the search at `k` instead of `k+1` lets the algorithm pair an element with itself. With `arr = [1, 3, 4]` and `target = 6`, no two different elements sum to 6, but at `k = 1` the search for `3` finds index 1 itself and returns the pair `(1, 1)`.

The general habit: translate every problem constraint ("no reuse," "must come after," "must be strictly greater") directly into a bound on `i` or `j` before writing the loop — don't discover it via a failing test case.

When the candidates are not array indices, the bounds are the smallest and largest answers that could possibly be correct. For "binary search on the answer" below, that means reasoning about the problem's values, not about `n`.

## Floor vs. ceiling in `mid`

Integer division in most languages floors. That's fine — *as long as your updates always guarantee the range shrinks*. The way to check this: ask what happens when `i` and `j` are adjacent (`j = i + 1`).

- `mid = i + (j - i) / 2` (floor) → when `j = i+1`, `mid = i`.
- `mid = i + (j - i + 1) / 2` (ceiling) → when `j = i+1`, `mid = j`.

When the range is two elements, `mid` lands on one end of it. The update must then move the *other* end, or nothing changes:

- **Floor** lands on `i`. An update `i = mid` sets `i = i`, so the range never shrinks and the loop runs forever. Floor is safe with `j = mid` and `i = mid + 1`.
- **Ceiling** lands on `j`. An update `j = mid` sets `j = j`, which is the same infinite loop on the other side. Ceiling is safe with `i = mid` and `j = mid - 1`.

So the division and the "keep `mid`" update come in pairs: **floor with `j = mid`, ceiling with `i = mid`**. If neither branch keeps `mid`, because both updates are `± 1`, either division works.

## `mid ± 1` vs. `i/j = mid`

Most binary search bugs are here. Before writing the update for a branch, ask exactly one question:

> **After this comparison, is `mid` still possibly the answer, or have I just proven it can't be?**

- **Proven `mid` is wrong → exclude it.** Use `i = mid + 1` or `j = mid - 1`. This is safe and necessary: you must make progress, and you know for certain `mid` will never be revisited correctly.
- **`mid` might still be the answer → keep it in range.** Use `i = mid` or `j = mid`, *not* `± 1`. Throwing `mid` away here would eliminate a value you haven't actually ruled out.

### Pattern A: exact-match search (checked and rejected)

You test equality directly and return immediately on a match, so every other branch has, by construction, ruled `mid` out:

```cpp
while (i <= j) {
    int mid = i + (j - i) / 2;
    if (arr[mid] == target) return mid;      // handled: mid IS the answer
    else if (arr[mid] < target) i = mid + 1; // disproven: exclude it
    else j = mid - 1;                        // disproven: exclude it
}
return -1;                                   // range empty: not present
```

Both updates are `± 1` because both branches only run when `mid` has already been eliminated as a candidate.

### Pattern B: boundary search, first true

You're not testing "is this the answer," you're testing "does this satisfy a condition," and satisfying it doesn't disqualify `mid` — it might just *be* the best answer so far:

```cpp
// find the first index where arr[i] >= target
int i = 0, j = n; // half-open: j = n, not n-1
while (i < j) {
    int mid = i + (j - i) / 2;
    if (arr[mid] >= target) j = mid;     // mid could BE the answer — keep it
    else i = mid + 1;                    // arr[mid] < target — definitely disqualified
}
// i is the answer: i == n means no element is >= target
```

`j = mid` keeps `mid`, because `arr[mid] >= target` doesn't rule it out as the first qualifying index. `i = mid + 1` excludes it, because `arr[mid] < target` is a hard disqualification. The update that keeps `mid` is on the high side, so floor division is the right pairing.

After the loop, `i` is also the **insertion point**: the index where `target` would go to keep the array sorted. This is the C++ standard library's `std::lower_bound` and Python's `bisect_left`. Changing `>=` to `>` gives the first element strictly greater than `target`, which is `std::upper_bound` and `bisect_right`.

### Pattern C: last true

To find the *last* index where a condition holds, the update that keeps `mid` is on the low side, `i = mid`, so the division must be ceiling:

```cpp
// find the last index where arr[i] <= target, or -1
int i = -1, j = n - 1;                   // i = -1 stands for "none"
while (i < j) {
    int mid = i + (j - i + 1) / 2;       // ceiling: mid is never i
    if (arr[mid] <= target) i = mid;     // mid could BE the answer — keep it
    else j = mid - 1;                    // too big — disqualified
}
// i is the answer: -1 means every element is > target
```

Starting `i` at `-1` plays the same role as `j = n` in Pattern B: it gives "no element qualifies" a slot. Ceiling division keeps `mid` at least `i + 1`, so `arr[-1]` is never read.

The same answer is also one step left of the Pattern B boundary for `>`: `upper_bound(...) - 1`. In practice that is often the shortest way to write it.

### Pattern D: closed range with a saved answer

A third way to write boundary searches: keep the closed-range loop from Pattern A, and record `mid` in a variable every time it satisfies the condition. Both updates are then `± 1`, so there is no floor/ceiling pairing to get wrong:

```cpp
// last index where arr[i] <= target, or -1
int i = 0, j = n - 1, ans = -1;
while (i <= j) {
    int mid = i + (j - i) / 2;
    if (arr[mid] <= target) {
        ans = mid;                       // best so far
        i = mid + 1;                     // look for a later one
    } else {
        j = mid - 1;
    }
}
```

It costs one extra variable and finds the same index as Pattern C. When a problem's predicate is awkward to pair with the right division, this form is the safer one to write.

## Quick reference table

| Situation | Update | Division needed |
| --- | --- | --- |
| Exact match tested and failed | `mid ± 1` on both sides | floor is fine |
| First true: `mid` still a candidate on the high side | `j = mid`, `i = mid + 1` | **floor**: ceiling would stall at two elements |
| Last true: `mid` still a candidate on the low side | `i = mid`, `j = mid - 1` | **ceiling**: floor would stall at two elements |
| Saved answer, closed range | `mid ± 1` on both sides, `ans = mid` when it qualifies | floor is fine |

## Binary search on the answer

Some problems never give you a sorted array. They ask for the smallest (or largest) value that makes something possible: the minimum speed, capacity, or number of days. If making the value bigger never turns a "possible" into "impossible", then `P(x) = "x works"` is a monotonic predicate over the range of possible answers, and binary search finds the first `x` where it becomes true.

**Koko Eating Bananas (875).** Koko eats from one pile per hour at speed `k`, so a pile of `p` bananas takes `⌈p / k⌉` hours. Find the smallest `k` that finishes all piles within `h` hours.

- **Candidates:** speeds from `1` to `max(piles)`. A higher speed never helps, because every pile already takes one hour at that speed.
- **Predicate:** `P(k) = sum of ⌈p / k⌉ over all piles ≤ h`. A faster speed never takes longer, so once `P` is true it stays true.
- **Search:** first true. Pattern B or Pattern D both work. The check costs O(n) per candidate, so the total is O(n log max(piles)).

```
piles = [3, 6, 7, 11],  h = 8

k = 4:  1 + 2 + 2 + 3 = 8 hours   ≤ 8  → true
k = 3:  1 + 2 + 3 + 4 = 10 hours  > 8  → false
answer: 4
```

`⌈p / k⌉` is computed in integers as `(p + k - 1) / k`. With large piles, the sum of hours can exceed 32 bits, so add it up in a `long long`.

The same shape solves Capacity to Ship Packages, Split Array Largest Sum and Minimum Days to Make Bouquets. The signal is a question like "the minimum X such that the task can be done", with a check that is easy to write once X is fixed.

## Rotated sorted arrays

A sorted array rotated at an unknown point, such as `[4, 5, 6, 7, 0, 1, 2]`, is not sorted. But splitting it at any `mid` gives two halves, **at least one of which is sorted**. Comparing `nums[mid]` with an end of the range tells you which one.

**Find Minimum in Rotated Sorted Array (153)** is a first-true search with `P(i) = nums[i] <= nums[n - 1]`. Everything left of the rotation point is larger than the last element, and everything from the minimum onward is not:

```cpp
int i = 0, j = n - 1;
while (i < j) {
    int mid = i + (j - i) / 2;
    if (nums[mid] > nums[j]) i = mid + 1; // min is strictly right of mid
    else j = mid;                         // mid could be the min, keep it
}
return nums[i];
```

`j = mid` keeps `mid`, paired with floor division. Comparing with `nums[j]` rather than `nums[i]` matters: when the range is already sorted, `nums[mid] >= nums[i]` is true and would push the search right, past the minimum at `i`.

**Search in Rotated Sorted Array (33)** is an exact-match search, Pattern A, with one extra step per iteration. Find the sorted half, check whether `target` lies inside its range, then keep that half or the other one:

```cpp
if (nums[mid] >= nums[i]) {              // left half [i, mid] is sorted
    if (nums[i] <= target && target < nums[mid]) j = mid - 1;
    else i = mid + 1;
} else {                                 // right half [mid, j] is sorted
    if (nums[mid] < target && target <= nums[j]) i = mid + 1;
    else j = mid - 1;
}
```

The `>=` in `nums[mid] >= nums[i]` handles `mid == i`, where the left "half" is the single element `nums[i]`, which is sorted.

## Other shapes

**A 2D matrix sorted row by row (74).** If each row is sorted and each row's first element is greater than the previous row's last, the matrix is one sorted array of `rows × cols` elements laid out row by row. Search indices `0 .. rows·cols − 1`, and convert each `mid` with `r = mid / cols`, `c = mid % cols`.

**Last value at or before a time (981).** A time-based key-value store keeps each key's `(timestamp, value)` pairs in a list. Timestamps only increase, so the list is sorted. `get(key, t)` wants the value with the largest timestamp `≤ t`, which is a last-true search: Pattern C, Pattern D, or `upper_bound - 1`.

**Median of two sorted arrays (4).** Here the candidates are *split positions*: how many elements of the shorter array go to the left half of the merged order. A split is valid when everything on the left is `≤` everything on the right. Too few elements taken from one array and too many from the other show up as a violation on one specific side, which tells the search which way to move. It runs in O(log(min(m, n))).

## Complexity

Each iteration halves the range, so a range of size `n` takes about `log₂ n` iterations: 20 for a million, 30 for a billion. The total is O(log n) times the cost of one check. That check is O(1) for an array lookup, and O(n) for a feasibility check in binary search on the answer.

## General debugging habit for this class of bug

When a binary search "mostly works but fails on some inputs":

1. Write out, in plain English, exactly which indices are *allowed* to be considered, given the problem's constraints (not just `[0, n-1]` by default).
2. For each branch of the comparison, ask "did I just disprove `mid`, or is it still alive?" — that answer alone tells you whether to write `± 1` or plain `mid`.
3. If any branch keeps `mid` (`i = mid` or `j = mid`), mentally simulate `i, i+1` as your current range and confirm the update actually changes something.
4. Construct the smallest possible adversarial input by hand (duplicates, a range of size 1 or 2, the target equal to an endpoint, no element qualifying) rather than relying on the visible test cases. These are where off-by-one and floor/ceil mistakes hide.
