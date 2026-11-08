# Integer Formulas

These formulas come up in many unrelated problems: splitting a range in half, rounding a division up, computing a midpoint, turning a grid position into an array index, counting pairs or subarrays. Each one replaces a floating-point call or a special case with a single integer expression. Every formula below was checked by running it over a range of inputs, and each section says where it stops working.

Integer division in this page means C-style division of non-negative numbers, which rounds down. How `/` and `%` behave on negative numbers in each language is in [overflow](../13_bit_manipulation/13b_overflow.md#division-and-remainder-of-negative-numbers).

## Splitting a count into two halves

To split `total` elements into a left part and a right part as evenly as possible:

```
left  = (total + 1) / 2
right = total - left
```

When `total` is even, both halves are equal. When it is odd, the left half gets the extra element:

```
total   left   right
  6       3      3
  7       4      3
```

`(total + 1) / 2` is `ceil(total / 2)`. Using `total / 2` instead rounds down and gives the extra element to the right half. Either choice works as long as the code uses the same one everywhere. The left-heavy split is common because then the left half is never empty when `total >= 1`. Median of Two Sorted Arrays uses it to decide how many elements go on the left of the partition, and Find Median from Data Stream keeps the lower heap the larger one for the same reason ([heap problems](../02_data_structures/2h_heap_problems.md#two-heaps-find-median-from-data-stream-295)).

## Ceiling division

To round `a / b` **up** without floating point:

```
ceil(a / b) = (a + b - 1) / b        for a >= 0, b > 0
```

Adding `b - 1` before dividing pushes every value that is not an exact multiple of `b` past the next multiple, and leaves exact multiples where they are:

```
a    b    a / b (floor)    (a + b - 1) / b    true ceiling
12   4         3                 3                 3
13   4         3                 4                 4
15   4         3                 4                 4
16   4         4                 4                 4
```

This was checked for every `a` from 0 to 59 and `b` from 1 to 19.

It is used for the number of pages, buckets or trips needed: `n` items in boxes of `b` need `(n + b - 1) / b` boxes. Koko Eating Bananas computes the hours for one pile with it.

**It fails for negative `a`** in C-style languages, because `/` rounds negative results toward zero. For `a = -7`, `b = 3`, the true ceiling of `-2.33` is `-2`, but `(-7 + 3 - 1) / 3 = -5 / 3`, which C evaluates to `-1`. Ceiling of a negative quotient needs a different formula, or simply `-((-a) / b)` when `a <= 0`.

Two other ways to write it:

```
a / b + (a % b != 0)     safe for a >= 0, b > 0
(a - 1) / b + 1          wrong for a = 0 in C, C++, Java and Go
```

The second form gives `ceil(0 / 3) = (0 - 1) / 3 + 1`. C rounds `-1 / 3` toward zero, to 0, so the result is 1 instead of 0. Python's `//` rounds `-1 // 3` down to -1, so the same expression gives the right answer there. The `(a + b - 1) / b` form and the `%` form avoid the question.

## A midpoint that does not overflow

Binary search computes the middle of `[left, right]`. The direct form overflows a 32-bit `int` when `left + right` is above 2 147 483 647:

```
left = 1073741824, right = 2147483647
left + right = 3221225471          too large for a 32-bit int
```

Subtracting first keeps every intermediate value inside the range:

```
floor:    mid = left + (right - left) / 2
ceiling:  mid = left + (right - left + 1) / 2
```

`right - left` is never larger than `right`, and half of it added to `left` stays between `left` and `right`. For the values above, the floor form gives `1610612735` with no overflow. Both forms were checked against `(left + right) / 2` and `(left + right + 1) / 2` for every `0 <= left <= right < 30`.

**Which one to use.** The floor form can return `left`, and the ceiling form can return `right`. With two elements left, `left = 4` and `right = 5`, floor gives 4 and ceiling gives 5. A loop that sets `left = mid` needs the ceiling form, or it can set `left` to the same value forever. The pairing rules are in [binary search](../05_sorting_and_searching/5c_binary_search.md#floor-vs-ceiling-in-mid).

Python integers do not overflow, so `(left + right) // 2` is safe there. Java and C++ also offer `(left + right) >>> 1` and `std::midpoint` respectively.

## Flattening a 2D grid into a 1D index

A grid with `R` rows and `C` columns can be stored in one array of `R · C` elements, row after row. The cell at `(row, col)` goes to:

```
index = row * C + col
```

To reach row `row`, the index skips every complete row before it. Each of those rows holds `C` cells, so that is `row * C` cells. Then `col` moves along the current row to the cell.

The inverse turns an index back into a position:

```
row = index / C
col = index % C
```

For `R = 3`, `C = 4`:

```
          col 0   col 1   col 2   col 3
row 0       0       1       2       3
row 1       4       5       6       7
row 2       8       9      10      11
```

Index 5 gives `row = 5 / 4 = 1` and `col = 5 % 4 = 1`. Index 11 gives `(2, 3)`.

Both formulas use `C`, the number of **columns**, not `R`. Using `R` for a non-square grid gives indices that overlap or skip cells.

Uses:

- **Binary search on a sorted matrix** (Search a 2D Matrix, 74): treat the matrix as one sorted array of `R · C` elements, and turn each `mid` back into `(row, col)`.
- **Union-Find on a grid**: each cell needs a single integer id ([union find](../11_graphs/11c_union_find.md)).
- **Storing a grid in one `vector`** instead of a vector of vectors, which keeps the cells in one block of memory.

## Counting formulas

| Quantity | Formula | Example |
|---|---|---|
| integers in `[l, r]` | `r - l + 1` | `[3, 7]` holds 5 |
| `1 + 2 + … + n` | `n(n + 1) / 2` | `n = 100` gives 5050 |
| pairs `(i, j)` with `i < j` among `n` | `n(n - 1) / 2` | `n = 4` gives 6 |
| non-empty contiguous subarrays of `n` elements | `n(n + 1) / 2` | `n = 4` gives 10 |
| multiples of `k` in `[1, n]` | `n / k` | multiples of 3 up to 20: 6 |
| multiples of `k` in `[l, r]` | `r / k - (l - 1) / k` | multiples of 3 in `[7, 20]`: 4 |
| digits of `n > 0` | `floor(log10(n)) + 1`, or count `n /= 10` steps | 12345 has 5 |
| `n` rounded up to a multiple of `k` | `(n + k - 1) / k * k` | 13 → 16 for `k = 8` |

The number of subarrays and the number of pairs are close but not the same. A subarray is a pair `(i, j)` with `i <= j`, so it also counts the `n` one-element subarrays: `n(n - 1) / 2 + n = n(n + 1) / 2`.

`n(n + 1) / 2` multiplies before dividing, so for `n` near 65 536 the product overflows a 32-bit `int` even though the result fits. Computing it in 64 bits avoids that.

## K largest and K smallest with a heap

```
k largest  → min-heap of size k
k smallest → max-heap of size k
```

The heap keeps the current best `k` values, and its top is the **worst** of them, the one to throw out when a better value arrives. For the `k` largest, the worst is the smallest, so the heap is a min-heap. Each new value is pushed, and when the heap holds more than `k`, the top is popped. Traces are in [heap problems](../02_data_structures/2h_heap_problems.md#a-heap-kept-at-size-k).
