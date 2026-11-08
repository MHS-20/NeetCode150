# Variable-Size Sliding Windows

Many problems ask for the **longest** or **shortest** contiguous subarray or substring that meets a condition: no repeated characters, contains every letter of `t`, at most `k` characters differ. The window length is not given. A variable-size window grows by moving `right` forward, and shrinks by moving `left` forward, until it meets the condition. Both pointers only move forward, so the pass is O(n), even though it has a loop inside a loop.

The examples follow the C++ solutions in `03_sliding_window/`. Every trace was produced by running the loop shown.

## The basic loop

```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    add(a[right]);                       // grow on the right
    while (/* window must shrink */) {
        remove(a[left]);                 // shrink on the left
        left++;
    }
    // use the window a[left .. right]
}
```

The window is valid or invalid with respect to the problem's condition. Two kinds of problem use this loop with a different shrink test.

**Longest valid window.** Shrink **while the window is invalid**. After the inner loop the window is valid, and its length is a candidate for the answer.

**Shortest valid window.** Shrink **while the window is valid**, and record its length inside the inner loop before each shrink. The loop stops at the first invalid window.

Both rely on a property of the condition. For the longest window: if a window is valid, every shorter window inside it is valid too. For the shortest window: if a window is valid, every longer window containing it is valid too. Either way, once `left` has moved past an index, no answer can need it back, so `left` never moves backwards. When the property fails, the window does not work, as shown at the end of this page.

### Why the cost is O(n)

The inner `while` can run many times for one value of `right`, so it looks like O(n²). But every time it runs, `left` moves forward by one, and `left` never moves back. Over the whole pass `left` moves at most `n` times in total. So the inner loop body runs at most `n` times across all iterations of the outer loop, and the whole pass is O(n) plus the cost of `add` and `remove`.

Each element is added once, when `right` reaches it, and removed at most once, when `left` passes it.

## Longest Substring Without Repeating Characters (3)

The window is valid if no character appears twice in it.

With the basic loop, the window keeps a set of its characters. When `s[right]` is already in the set, `left` moves forward, removing characters, until the earlier copy is gone.

The repo's solution skips that inner loop. It stores the last index where each character was seen. When `s[right]` was last seen inside the window, `left` jumps straight past that index:

```cpp
for (int right = 0; right < s.size(); right++) {
    char c = s[right];
    if (lastSeen.count(c) && lastSeen[c] >= left)
        left = lastSeen[c] + 1;
    lastSeen[c] = right;
    maxLen = max(maxLen, right - left + 1);
}
```

For `s = "abcabcbb"`:

```
right   c   last seen   left   window   best
  0     a       —         0     "a"       1
  1     b       —         0     "ab"      2
  2     c       —         0     "abc"     3
  3     a       0         1     "bca"     3
  4     b       1         2     "cab"     3
  5     c       2         3     "abc"     3
  6     b       4         5     "cb"      3
  7     b       6         7     "b"       3
```

The answer is 3.

The test `lastSeen[c] >= left` is required. A character can have been seen before the window started, and jumping to it would move `left` backwards. For `s = "abba"`:

```
right   c   last seen   left   window
  0     a       —         0     "a"
  1     b       —         0     "ab"
  2     b       1         2     "b"
  3     a       0         2     "ba"      'a' was seen at 0, before left = 2: no jump
```

Without the test, `right = 3` would set `left = 0 + 1 = 1`, and the window `"bba"` would contain two `b`s. The answer would come out as 3 instead of 2.

## Minimum Window Substring (76)

The task: find the shortest substring of `s` that contains every character of `t`, counting repeats. This is a shortest-window problem, so the window shrinks while it is valid.

The repo's second solution keeps two values:

- `need[c]`: how many more copies of `c` the window still needs. It starts as the count of `c` in `t`, and can go negative when the window holds extra copies.
- `missing`: how many characters of `t` the window still lacks in total. It starts at `len(t)`. The window is valid when `missing == 0`.

```cpp
for (int right = 0; right < s.size(); right++) {
    if (need[s[right]]-- > 0)
        missing--;                     // this copy was still needed
    while (missing == 0) {             // valid: record, then shrink
        if (right - left + 1 < bestLen) {
            bestStart = left;
            bestLen = right - left + 1;
        }
        if (++need[s[left]] > 0)
            missing++;                 // removed a copy that was needed
        left++;
    }
}
```

`missing` changes only when a needed copy enters or leaves. An extra copy of a letter, or a letter not in `t`, only moves `need[c]` further below 0 or back towards it.

For `s = "ADOBECODEBANC"`, `t = "ABC"`, these are the valid windows the inner loop sees, in order:

```
left  right   window          length
  0     5     ADOBEC             6   ← first valid window, best = 6
  1    10     DOBECODEBA        10
  2    10     OBECODEBA          9
  3    10     BECODEBA           8
  4    10     ECODEBA            7
  5    10     CODEBA             6
  6    12     ODEBANC            7
  7    12     DEBANC             6
  8    12     EBANC              5
  9    12     BANC               4   ← best = 4
```

After `ADOBEC` is recorded, removing `A` makes the window invalid, and `right` has to reach index 10, the next `A`, before it is valid again. The answer is `"BANC"`.

The repo's first solution compares per-character counts instead of keeping `missing`, the same `matches` idea as in [Permutation in String](01_fixed_size.md#permutation-in-string-567).

## Longest Repeating Character Replacement (424)

The task: in a string of uppercase letters, up to `k` characters can be replaced with any letter. Find the length of the longest substring that can be made all one letter.

A window can be made all one letter if it has at most `k` characters that differ from its most common letter:

```
length - (count of the most common letter) <= k
```

This is a longest-window problem. The solution keeps the counts of the window and `maxFreq`, the highest count seen:

```cpp
for (int right = 0; right < s.size(); right++) {
    reps[s[right]]++;
    maxFreq = max(maxFreq, reps[s[right]]);
    if (right - left - maxFreq >= k) {      // length - maxFreq > k
        reps[s[left]]--;
        left++;
    }
    maxLen = max(maxLen, right - left + 1);
}
```

This code differs from the basic loop in two places:

1. It shrinks with `if`, not `while`, so `left` moves at most one step per iteration.
2. `maxFreq` never decreases. When the most common letter leaves the window, `maxFreq` keeps its old value, which can be higher than any count in the current window.

Because of the second point, the current window can be invalid for a while. The answer still comes out right, for the reasons below.

### The window never gets shorter

Every iteration, `right` moves forward by one. `left` moves forward by at most one. So the window length either stays the same or grows by one. It never shrinks. After the loop, `maxLen` is the largest length the window ever reached.

### Every reported length has a valid window

`maxFreq` is always a real count: at the moment it was last raised, some letter appeared `maxFreq` times in the window of that moment. Call that window `W`. Its length is at most the current window length `L`, because the window never gets shorter.

The window keeps length `L` only if the `if` did not shrink it, which means `L - maxFreq <= k`. Take `W` and extend it with neighbouring characters until it has length `L`. Extending only adds characters, so the letter still appears at least `maxFreq` times. The extended window has at most `L - maxFreq <= k` other characters, so it is valid.

So whenever the window has length `L`, some valid window of length `L` exists in the string, although it may not be the current window. `maxLen` never reports a length that is too long.

### No length is missed

A stale `maxFreq` is higher than the true count, never lower. A higher value makes the shrink test `length - maxFreq > k` fail more often, so the window shrinks less often. It therefore grows at least as far as it would with an exact `maxFreq`, and `maxLen` is never too short either.

### Trace

`s = "AABABBA"`, `k = 1`. The correct answer is 4 (`"AABA"` with the `B` replaced, or `"ABBB"`). In the table, "true max" is the actual highest count in the window:

```
right   window    maxFreq   true max   valid?    best
  0     A            1         1        yes        1
  1     AA           2         2        yes        2
  2     AAB          2         2        yes        3
  3     AABA         3         3        yes        4
  4     ABAB         3         2        no         4    shrank by one, still invalid
  5     BABB         3         3        yes        4
  6     ABBA         3         2        no         4    shrank by one, still invalid
```

At `right = 4` and `right = 6`, the window has two `A`s and two `B`s, so it needs 2 replacements and `k` is 1. It keeps length 4 only because `maxFreq` is still 3, from the window `AABA` at `right = 3`. That window is a valid window of length 4, so `best = 4` is correct.

Keeping `maxFreq` exact would need the highest count in the window after each removal, which means scanning all 26 counts. That makes each step cost O(26) instead of O(1). Both versions are O(n) for a fixed alphabet.

## Best Time to Buy and Sell Stock (121)

The task: buy on one day and sell on a later day, for the largest profit. For each selling day, the best buying day is the cheapest day before it.

The repo's solution keeps that cheapest price as it goes:

```cpp
for (int p : prices) {
    mn = min(mn, p);
    profit = max(profit, p - mn);
}
```

As a window, the buying day is `left` and the selling day is `right`. `left` jumps to `right` whenever a new lowest price appears, because no earlier day can be a better buying day after that. Only the price at `left` matters, so the solution stores that price and not the index.

For `prices = [7, 1, 5, 3, 6, 4]`:

```
price   lowest so far   profit if sold today   best
  7          7                  0                0
  1          1                  0                0
  5          1                  4                4
  3          1                  2                4
  6          1                  5                5
  4          1                  3                5
```

## When a window does not work

The window depends on a property of the condition: in a longest-window problem, shrinking an invalid window has to move it towards valid. If removing an element can make the window either better or worse, `left` cannot know when to stop.

Subarray Sum Equals K (560) shows this. The task is to count the subarrays that sum to `k`, and the numbers can be negative. A window that shrinks while its sum is greater than `k` fails on `nums = [1, -1, 5, -2, 3]`, `k = 3`:

```
right   x    sum before shrink   shrinking                          window after   count
  0     1          1             —                                   [1]             0
  1    -1          0             —                                   [1, -1]         0
  2     5          5             drop 1 → 4, drop -1 → 5, drop 5 → 0  []              0
  3    -2         -2             —                                   [-2]            0
  4     3          1             —                                   [-2, 3]         0
```

The window counts 0, but three subarrays sum to 3: `[1, -1, 5, -2]`, `[5, -2]` and `[3]`. At `right = 2`, dropping `-1` raised the sum from 4 to 5, so shrinking made the window worse. The window then lost `5`, which is part of two of the answers.

The working solution uses prefix sums. `prefix[i]` is the sum of the first `i` elements. A subarray `nums[i .. j]` sums to `k` when `prefix[j+1] - prefix[i] == k`. A hash map counts how many times each prefix sum has appeared, and at each position the solution adds the count of `prefix - k`:

```
x     prefix   prefix - k   times seen before   count
          0                   (start: {0: 1})
 1        1        -2              0               0
-1        0        -3              0               0
 5        5         2              0               0
-2        3         0              2               2      [1, -1, 5, -2] and [5, -2]
 3        6         3              1               3      [3]
```

This works for any sign and runs in O(n) with O(n) extra space. If every number is positive, adding an element always raises the sum and removing one always lowers it, so the window works again and needs no map.
