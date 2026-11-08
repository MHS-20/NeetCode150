# Two Pointers from Opposite Ends

Many array problems ask about a **pair** of positions: two numbers that add up to a target, two walls that hold the most water, two characters that must match. An array of `n` elements has `n(n-1)/2` pairs, so checking every pair takes O(n²) time. Two pointers find the answer in O(n) by starting at both ends and moving inward. At each step, the values at the two pointers show that one pointer's remaining pairs cannot contain the answer, so that pointer moves on.

The examples follow the C++ solutions in `02_two_pointers/`. Every trace on this page was produced by running the same loop on the input shown.

## The basic loop

```cpp
int i = 0, j = n - 1;
while (i < j) {
    // look at a[i] and a[j]
    // then move i forward, or j backward, or both
}
```

`i` only moves right and `j` only moves left. Each step moves at least one of them, and the loop stops when they meet, so it runs at most `n - 1` times.

The difficult part is not the loop but the rule that decides which pointer moves. That rule needs a reason why moving is safe, which means a reason why none of the skipped pairs can be the answer. Each problem below gives its own reason.

## Two Sum II (167): why sorted order makes it work

The input is sorted in increasing order, and the task is to find two numbers that add up to `target`.

The rule:

- If `a[i] + a[j]` is **less** than `target`, move `i` right.
- If it is **greater**, move `j` left.
- If it is **equal**, return the pair.

### Why moving is safe

Write every pair `(i, j)` with `i < j` in a grid. For 6 elements:

```
         j=1     j=2     j=3     j=4     j=5
i=0    (0,1)   (0,2)   (0,3)   (0,4)   (0,5)
i=1            (1,2)   (1,3)   (1,4)   (1,5)
i=2                    (2,3)   (2,4)   (2,5)
i=3                            (3,4)   (3,5)
i=4                                    (4,5)
```

The pointers start at `(0, 5)`, the top-right corner.

Suppose `a[0] + a[5]` is less than `target`. The array is sorted, so `a[5]` is the largest value `a[0]` can be paired with. Every other pair in row `i = 0` uses a smaller `a[j]` and has a smaller sum. None of them can reach `target`, so the whole row is ruled out, and `i` moves to 1.

If `a[0] + a[5]` is greater than `target`, the same argument works on the column. `a[0]` is the smallest value `a[5]` can be paired with, so every pair in column `j = 5` has a larger sum. The column is ruled out, and `j` moves to 4.

Each step removes one row or one column from the grid. The grid has `n - 1` rows, so after at most `n - 1` steps either the pair is found or the grid is empty.

### Trace

`a = [1, 3, 4, 6, 8, 11]`, `target = 10`:

```
 i   j   a[i]  a[j]   sum   action
 0   5     1    11     12   too big   → j--   (column 5 ruled out)
 0   4     1     8      9   too small → i++   (row 0 ruled out)
 1   4     3     8     11   too big   → j--
 1   3     3     6      9   too small → i++
 2   3     4     6     10   found
```

The answer is indices 2 and 3. LeetCode numbers positions from 1, so the solution returns `[3, 4]`.

### Comparison with binary search

The repo's first solution fixes each `a[idx]` in turn and binary-searches the rest of the array for `target - a[idx]`. That is O(n log n). The two-pointer version is O(n), and both use O(1) extra space.

A hash map also solves Two Sum in O(n), and it does not need sorted input. On sorted input the two pointers do the same job without the map's O(n) memory.

## Valid Palindrome (125): pointers that skip

The task is to check whether a string reads the same forwards and backwards, counting only letters and digits and ignoring case.

The pointers compare the two ends and move inward together. Each one first skips any character that is not a letter or a digit:

```cpp
while (left < right) {
    while (left < right && !isalnum(s[left]))  left++;
    while (left < right && !isalnum(s[right])) right--;
    if (tolower(s[left]) != tolower(s[right])) return false;
    left++;
    right--;
}
return true;
```

The test `left < right` appears in the inner loops as well as the outer one. Without it, a string made only of punctuation, such as `".,"`, would move `left` past the end of the string.

Here the reason for moving is simple: the pair `(left, right)` has been checked, and a palindrome has to match at every mirrored pair, so the next mirrored pair is `(left + 1, right - 1)`. The array does not need to be sorted.

## Container With Most Water (11): moving the shorter wall

`height[i]` is the height of a wall at position `i`. Two walls and the ground form a container. Its area is the distance between the walls times the height of the **shorter** wall:

```
area(l, r) = (r - l) * min(height[l], height[r])
```

The task is to find the largest area.

The rule: compute the area, then move the pointer at the **shorter** wall. If the walls are equal, either can move.

### Why moving the shorter wall is safe

Suppose `height[l] <= height[r]`, so `l` is the shorter wall. Look at every other pair that uses `l`: `(l, j)` for `l < j < r`.

- **The width is smaller.** `j - l < r - l`.
- **The height is not larger.** The container's height is `min(height[l], height[j])`, and that is at most `height[l]`, whatever `height[j]` is.

So every pair `(l, j)` has a smaller area than `(l, r)`, which has already been measured. Wall `l` has no better partner left, and `l` can move on.

The same argument does not work for the taller wall. Pairs that use `r` with a different left wall can be taller than `height[l]`, so they can have a larger area.

### Trace

`height = [1, 8, 6, 2, 5, 4, 8, 3, 7]`:

```
 l   r   h[l]  h[r]   area   best   move
 0   8     1     7      8      8    l (shorter)
 1   8     8     7     49     49    r (shorter)
 1   7     8     3     18     49    r
 1   6     8     8     40     49    l (equal; the code moves l)
 2   6     6     8     24     49    l
 3   6     2     8      6     49    l
 4   6     5     8     10     49    l
 5   6     4     8      4     49    l
```

The answer is 49, from walls 1 and 8.

### What goes wrong if the taller wall moves

With the rule reversed, the first step at `(0, 8)` moves `r`, because `height[8] = 7` is taller than `height[0] = 1`. The pair `(1, 8)` that gives 49 is then never visited. On this input the reversed rule returns 8.

## 3Sum (15): fixing one value, then two pointers

The task is to find every set of three numbers that adds up to 0, with no repeated triplets in the output.

### Reducing to Two Sum II

After sorting, the solution fixes the first number `nums[idx]` and looks for two numbers after it that add up to `-nums[idx]`. That is Two Sum II on the subarray `nums[idx+1 ..]`, and the same pointer rule applies: move `i` right if the sum is too small, and `j` left if it is too big.

Sorting costs O(n log n). Each fixed `idx` runs one O(n) two-pointer pass, so the total is O(n²).

### Skipping duplicates

Sorting puts equal values next to each other, so repeated triplets can be avoided by skipping equal neighbours in three places:

```cpp
for (int idx = 0; idx < nums.size(); idx++) {
    if (idx > 0 && nums[idx] == nums[idx - 1])
        continue;                       // 1. same first value as the last idx
    int i = idx + 1, j = nums.size() - 1;
    while (i < j) {
        int sum = nums[idx] + nums[i] + nums[j];
        if (sum == 0) {
            result.push_back({nums[idx], nums[i], nums[j]});
            i++;
            j--;
            while (i < j && nums[i] == nums[i - 1]) i++;   // 2. same second value
            while (i < j && nums[j] == nums[j + 1]) j--;   // 3. same third value
        } else if (sum > 0) {
            j--;
        } else {
            i++;
        }
    }
}
```

The skips at 2 and 3 run only after a triplet is found. When the sum is not zero, landing on a repeated value can only repeat a sum that has already been rejected, which costs time but never adds a duplicate to the output.

### Trace

`nums = [-1, 0, 1, 2, -1, -4]`, sorted to `[-4, -1, -1, 0, 1, 2]`:

```
idx  nums[idx]   i   j   sum   action
 0      -4       1   5    -3   too small → i++
 0      -4       2   5    -3   too small → i++
 0      -4       3   5    -2   too small → i++
 0      -4       4   5    -1   too small → i++    (i meets j)
 1      -1       2   5     0   found [-1, -1, 2] → i++, j--
 1      -1       3   4     0   found [-1, 0, 1]  → i++, j--  (i meets j)
 2      -1                     same as nums[1] → skipped (rule 1)
 3       0       4   5     3   too big → j--    (i meets j)
 4       1                     i = 5, j = 5: no pairs left
```

The output is `[[-1, -1, 2], [-1, 0, 1]]`. Without rule 1, `idx = 2` would fix the second `-1` and find `[-1, 0, 1]` a second time.

### The other solution: a set of triplets

The repo's second solution skips no duplicates. It inserts every triplet into a `set<vector<int>>`, which removes repeats on insert. It gives the same output. The cost is O(log m) per insert into a set of `m` triplets, plus memory for the set, which the skipping version does not need.

## Trapping Rain Water (42): which side is already known

`height[i]` is the height of a bar of width 1. The task is to find how much rain water the bars trap.

The water above bar `i` is set by the tallest bar on each side of it. Water rises to the lower of the two, and the bar itself takes up `height[i]` of that:

```
water[i] = min(maxLeft[i], maxRight[i]) - height[i]
```

`maxLeft[i]` is the tallest bar from position 0 up to and including `i`. `maxRight[i]` is the tallest from `i` to the end. Including bar `i` in both means the formula never goes below zero.

The repo has three solutions, and each removes something from the one before.

### Solution 1: two arrays

Fill `maxLeft` with a pass from the left and `maxRight` with a pass from the right, then apply the formula at every position.

For `height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]`:

```
i          0  1  2  3  4  5  6  7  8  9 10 11
height     0  1  0  2  1  0  1  3  2  1  2  1
maxLeft    0  1  1  2  2  2  2  3  3  3  3  3
maxRight   3  3  3  3  3  3  3  3  2  2  2  1
water      0  0  1  0  1  2  1  0  0  1  0  0      total 6
```

This takes O(n) time and O(n) extra space for the two arrays.

### Solution 2: two pointers

The formula needs only the **smaller** of `maxLeft[i]` and `maxRight[i]`. Two pointers can find that without storing either array.

`left` and `right` start at the two ends. `leftMax` is the tallest bar seen so far from the left, and `rightMax` the tallest seen from the right. At each step, the side with the smaller maximum moves inward:

```cpp
while (left < right) {
    if (leftMax < rightMax) {
        left++;
        leftMax = max(leftMax, height[left]);
        total += leftMax - height[left];
    } else {
        right--;
        rightMax = max(rightMax, height[right]);
        total += rightMax - height[right];
    }
}
```

**Why the smaller side is already known.** Suppose `leftMax < rightMax`, and `left` moves to a new bar. That bar's true `maxLeft` is `leftMax`, because the left pointer has seen every bar to its left. Its true `maxRight` is not known yet. It is at least `rightMax`, because the bar at `rightMax` lies somewhere to its right. So the true `maxRight` is larger than `leftMax`, and the minimum of the two is `leftMax`. The water above the bar is `leftMax - height[left]`, whatever the bars in between turn out to be. The same argument holds on the right side when `rightMax <= leftMax`.

For `height = [4, 2, 0, 3, 2, 5]`:

```
start:  left = 0, right = 5, leftMax = 4, rightMax = 5

side   moves to   leftMax   rightMax   water at bar   total
left     1          4          5        4 - 2 = 2        2
left     2          4          5        4 - 0 = 4        6
left     3          4          5        4 - 3 = 1        7
left     4          4          5        4 - 2 = 2        9
left     5          5          5        5 - 5 = 0        9
```

`leftMax` stays below `rightMax` the whole way, so only the left pointer moves. The answer is 9. This version takes O(n) time and O(1) extra space.

### Solution 3: a monotonic stack

The third solution measures the water in horizontal layers, using a stack of indices whose heights decrease from bottom to top. When a taller bar arrives, it closes off a pool above the bar on top of the stack. It is O(n) time and O(n) space, like solution 1. A trace of this solution on the same input is in [monotonic stack](../02_data_structures/2d_monotonic_stack.md#trapping-rain-water-42-solution-3-water-in-layers).
