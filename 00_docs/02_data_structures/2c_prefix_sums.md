# Prefix Sums

A **prefix sum** array stores, for each position, the sum of every element before it. With it, the sum of any contiguous range is one subtraction instead of a loop over the range. The same idea, with a hash map, counts the subarrays whose sum equals a target in O(n), including when the numbers are negative, which a sliding window cannot handle.

Every example on this page was produced by running the code shown.

## The definition

For an array `a` of length `n`, the prefix sum array `P` has `n + 1` entries:

```
P[0] = 0
P[i] = a[0] + a[1] + … + a[i-1]
```

`P[i]` is the sum of the first `i` elements. Building it is one pass: `P[i+1] = P[i] + a[i]`.

The extra entry `P[0] = 0`, for the empty prefix, is what keeps the range formula free of special cases.

For `a = [3, 1, 4, 1, 5, 9, 2, 6]`:

```
i       0   1   2   3   4   5   6   7   8
a           3   1   4   1   5   9   2   6
P       0   3   4   8   9  14  23  25  31
```

## The sum of a range

The sum of `a[l .. r-1]`, the elements from index `l` up to but not including `r`, is:

```
sum(a[l .. r-1]) = P[r] - P[l]
```

`P[r]` is the sum of the first `r` elements, and `P[l]` is the sum of the first `l`. Subtracting removes the first `l` elements and leaves the ones from `l` to `r - 1`.

For `a[2 .. 5]`, which is `4 + 1 + 5 + 9 = 19`: `P[6] - P[2] = 23 - 4 = 19`.

After the O(n) build, every range sum costs O(1). Range Sum Query (303) asks exactly this: many range sums on an array that does not change. If the array does change between queries, each update would have to rewrite every later `P[i]`, and a Fenwick tree or segment tree is used instead.

## Subarray Sum Equals K (560)

The task: count the contiguous subarrays whose sum is exactly `k`. The numbers can be negative.

By the range formula, the subarray `a[l .. r-1]` sums to `k` when:

```
P[r] - P[l] = k        which is the same as        P[l] = P[r] - k
```

So for each end position `r`, the number of subarrays ending there with sum `k` is the number of earlier prefix sums equal to `P[r] - k`. A hash map counts how many times each prefix sum has appeared so far. The loop adds the count for `P[r] - k`, then records `P[r]`:

```python
count = {0: 1}           # the empty prefix, P[0] = 0, seen once
prefix = answer = 0
for x in nums:
    prefix += x
    answer += count.get(prefix - k, 0)
    count[prefix] = count.get(prefix, 0) + 1
```

The starting entry `{0: 1}` is `P[0]`. Without it, subarrays that start at index 0 would never be counted.

Recording `P[r]` **after** looking up `P[r] - k` matters when `k = 0`. Looking it up after recording would count the empty subarray from `r` to `r`.

The full trace on `[1, -1, 5, -2, 3]` with `k = 3` is in [variable-size windows](../04_sliding_window/4b_variable_size.md#when-a-window-does-not-work). The same page shows why a sliding window fails here: with negative numbers, removing an element from the window can raise its sum.

The hash map holds up to `n + 1` prefix sums, so this is O(n) time and O(n) space.

## Prefix products

Product of Array Except Self (238) uses the same idea with multiplication: a prefix product from the left and a suffix product from the right, multiplied together at each position. It is traced in [array problems](2b_array_problems.md#product-of-array-except-self-238).

Products cannot be "subtracted" the way sums can. Dividing by a prefix product fails when it contains a 0. That is why problem 238 combines a prefix and a suffix instead of dividing.

## Prefix sums on a grid

The same idea works in two dimensions. `P[r][c]` is the sum of every cell above and to the left of `(r, c)`, that is, rows `0 .. r-1` and columns `0 .. c-1`. It is built from three neighbours:

```
P[r+1][c+1] = grid[r][c] + P[r][c+1] + P[r+1][c] - P[r][c]
```

`P[r][c+1]` and `P[r+1][c]` both include the rectangle `P[r][c]`, so it is subtracted once to avoid counting it twice.

The sum of the rectangle from `(r1, c1)` to `(r2, c2)`, inclusive, is:

```
P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]
```

The two subtractions remove the strip above and the strip to the left. They overlap in the top-left corner, which was subtracted twice, so it is added back.

For this grid:

```
grid          P
3 0 1         0  0  0  0
5 6 3         0  3  3  4
1 2 0         0  8 14 18
              0  9 17 21
```

the rectangle from `(1, 1)` to `(2, 2)` holds `6 + 3 + 2 + 0 = 11`, and the formula gives `P[3][3] - P[1][3] - P[3][1] + P[1][1] = 21 - 4 - 9 + 3 = 11`. Range Sum Query 2D (304) uses this.
