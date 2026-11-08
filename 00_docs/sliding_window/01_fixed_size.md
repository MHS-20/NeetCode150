# Fixed-Size Sliding Windows

A **window** is a contiguous subarray `a[left .. right]`. Problems that ask about every subarray of length `k` (its sum, its letter counts, its maximum) would cost O(n · k) if each subarray were recomputed from scratch. Two neighbouring subarrays of length `k` share `k - 1` elements. A sliding window keeps the answer for one subarray and updates it with the single element that enters and the single element that leaves, so each step costs O(1) and the whole pass costs O(n).

The examples follow the C++ solutions in `03_sliding_window/`. Every trace was produced by running the loop shown.

## The basic loop

`right` visits every index. Once the window is longer than `k`, the element at `right - k` leaves:

```cpp
for (int right = 0; right < n; right++) {
    add(a[right]);                  // element enters on the right
    if (right >= k)
        remove(a[right - k]);       // element leaves on the left
    if (right >= k - 1)
        check();                    // window a[right-k+1 .. right] is full
}
```

The left end is never stored. It is always `right - k + 1`.

### Example: largest sum of 3 consecutive elements

`a = [2, 1, 5, 1, 3, 2]`, `k = 3`. The first window `[2, 1, 5]` sums to 8. After that, each step adds the new element and subtracts the one that left:

```
right   enters   leaves   window        sum             best
  2        —        —     [2, 1, 5]     8                 8
  3        1        2     [1, 5, 1]     8 + 1 - 2 = 7     8
  4        3        1     [5, 1, 3]     7 + 3 - 1 = 9     9
  5        2        5     [1, 3, 2]     9 + 2 - 5 = 6     9
```

The answer is 9. Each step does one addition and one subtraction, regardless of `k`.

## Keeping counts of the window

When the question is about which characters a window contains, the window keeps a count per character. An element entering increments its count, and an element leaving decrements it.

There are two choices for storing the counts:

- **A fixed array** indexed by the character, `array<int, 26>` for lowercase letters or `array<int, 128>` for ASCII. Each update is an array access.
- **A hash map** from character to count. It works for any alphabet, but each update hashes the key, and comparing two maps costs O(size of the map).

When the alphabet is small and known, the array is faster and comparing two arrays costs O(26), a constant.

## Permutation in String (567)

The task: given `s1` and `s2`, decide whether some substring of `s2` is a permutation of `s1`. A substring is a permutation of `s1` if it has the same length and the same count of every letter. So the problem is a fixed window of length `k = len(s1)` sliding over `s2`, checking whether the window's letter counts equal those of `s1`.

The repo has three solutions. All three avoid comparing the full count tables at every step. They keep a running number that says how close the window is to matching, and change it only for the letter that entered and the letter that left.

### Solution 1: two maps and a match counter

`freq` holds the counts of `s1`, and `wfreq` the counts of the window. `matches` is the number of distinct letters of `s1` whose count in the window equals their count in `s1`. The window is a permutation when `matches` equals the number of distinct letters in `s1`.

The update for one letter `c` changing by `delta` (+1 entering, -1 leaving):

```cpp
if (wfreq[c] == freq[c]) matches--;   // c was matching; it may stop now
wfreq[c] += delta;
if (wfreq[c] == freq[c]) matches++;   // c matches after the change
```

The first test removes `c` from the count if it matched before the change. The second adds it back if it matches after. Together they keep `matches` right whichever way the change goes. Letters that are not in `s1` are skipped, because they never count towards a match.

### Solution 2: one map of differences

A single map stores `diff[c] = (count of c in the window) - (count of c in s1)`. It starts with `-1` for each letter of `s1`. `mismatched` counts the letters whose `diff` is not 0. The window is a permutation when `mismatched` is 0. The update has the same shape as solution 1, with `diff[c] == 0` in place of `wfreq[c] == freq[c]`.

### Solution 3: two arrays of 26

The same idea as solution 1, with `array<int, 26>` in place of the maps. Here `matches` counts all 26 letters, including those not in `s1`. Before the window starts, every letter not in `s1` already matches with a count of 0, so `matches` starts at `26 - (number of distinct letters in s1)`. The target is `matches == 26`.

### Trace of solution 3

`s1 = "ab"`, `s2 = "eidbaooo"`, `k = 2`. Before the loop, `a` and `b` do not match (count 1 in `s1`, 0 in the window), and the other 24 letters do, so `matches = 24`.

```
right  enters  leaves  window   change to matches                  matches
  0      e       —      "e"     e: 0 → 1, was matching, now not      23
  1      i       —      "ei"    i: 0 → 1, was matching, now not      22
  2      d       e      "id"    d stops matching, e matches again    22
  3      b       i      "db"    b now matches, i matches again       24
  4      a       d      "ba"    a now matches, d matches again       26  → true
```

At `right = 4` all 26 letters match, so `"ba"` is a permutation of `"ab"`.

Each step costs O(1) and the loop runs `len(s2)` times. Solution 3 also needs no hashing.

## The maximum of a window

A sum or a count can be updated when an element leaves by subtracting it. A maximum cannot: when the largest element leaves, the new maximum is not known without looking at the rest of the window. Sliding Window Maximum (239) solves this with a monotonic deque, covered in [window maximum](03_window_max_and_min.md).
