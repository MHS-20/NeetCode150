# Math and Geometry

## What this category is

Unlike the other lessons, this one has no single unifying structure. "Math and geometry" is where problems land that are not really about a data structure at all — the difficulty is a formula, an index manipulation, or an observation about numbers, and once you have it the code is a few lines.

That changes how to study it. There is no technique to internalise, only a set of specific facts and tricks. The list below is what recurs.

## Matrix index manipulation

The most common subcategory, and it is pure index arithmetic.

### Rotate an image 90° clockwise

The trick is that a rotation decomposes into two simple operations:

```
transpose (mirror over the main diagonal), then reverse each row

1 2 3        1 4 7        7 4 1
4 5 6   →    2 5 8   →    8 5 2
7 8 9        3 6 9        9 6 3
```

Transposing swaps `m[i][j]` with `m[j][i]` for `j > i` only — swapping over the whole matrix undoes itself. Both steps are in place, so the rotation is O(n²) time and O(1) space. Counterclockwise is the same with the steps' mirror: reverse the rows first, then transpose.

### Spiral traversal

Keep four boundaries and shrink them as each edge is consumed.

```
top=0, bottom=2, left=0, right=3

 →  →  →  →      walk right along `top`,     then top++
 ↑        ↓      down along `right`,          then right--
 ↑        ↓      left along `bottom`,         then bottom--
 ←  ←  ←  ↓      up along `left`,             then left++
```

```python
while top <= bottom and left <= right:
    for c in range(left, right + 1): out.append(m[top][c])
    top += 1
    for r in range(top, bottom + 1): out.append(m[r][right])
    right -= 1
    if top <= bottom:                             # re-check, single row left
        for c in range(right, left - 1, -1): out.append(m[bottom][c])
        bottom -= 1
    if left <= right:                             # re-check, single column left
        for r in range(bottom, top - 1, -1): out.append(m[r][left])
        left += 1
```

The two re-checks inside the loop are where this goes wrong. After the first two edges, a matrix with one row or one column remaining would traverse it a second time backwards without them.

### Set Matrix Zeroes

The naive approach needs O(m + n) space for the row and column flags. The O(1) trick: use the matrix's own first row and first column as the flag storage, handling those two lines separately with a pair of booleans. The general lesson — *store metadata inside the structure you already have* — recurs in other in-place problems.

## Integer arithmetic

### Overflow and division of negative numbers

What each language does when a result does not fit, the check-before-multiply guard used in Reverse Integer, and how `/` and `%` round negative numbers in each language are covered in [overflow](../13_bit_manipulation/13b_overflow.md). In short: test against the limit **before** the operation, and do not use Python's `//` or `%` where C-style rounding toward zero is required.

### Formulas, GCD, modular arithmetic and primes

Integer formulas such as ceiling division, an overflow-free midpoint and flattening a grid index are in [integer formulas](14b_integer_formulas.md). GCD and LCM, arithmetic modulo 10⁹ + 7, fast exponentiation, and primes are in [number theory](14c_number_theory.md).

## Digit and number tricks

**Extracting digits.** `n % 10` gives the last digit, `n //= 10` drops it. This is the loop behind reversing an integer, digit sums, and Happy Number.

**Palindrome Number without strings.** Reverse only the second half and compare it to the first, stopping when the reversed part is at least the remainder. Avoids overflow and halves the work.

**Cycle detection in a numeric sequence.** Happy Number repeats forever if it never reaches 1. Detect the loop with a set of seen values, or with the fast/slow pointer trick from [`6e_floyd_cycle_detection.md`](../06_linked_lists/6e_floyd_cycle_detection.md) — the sequence is a linked list whose `next` is a computed function.

## Combinatorics worth knowing

```
permutations of n:               n!
choose k from n, order matters:  n! / (n−k)!
choose k from n, unordered:      C(n, k) = n! / (k!(n−k)!)
subsets of a set of size n:      2ⁿ
```

`C(n, k)` also counts lattice paths: Unique Paths on an `m × n` grid moving only right and down is `C(m+n−2, m−1)`, since a path is just a choice of which of the moves are downward. That closed form is O(m + n) against the DP's O(m·n) — worth recognising, though the DP is the expected answer.

Pascal's triangle is the same numbers arranged so each is the sum of the two above it, which is exactly the recurrence `C(n,k) = C(n−1,k−1) + C(n−1,k)`.

## Geometry basics

Genuine geometry is rare in these problem sets, but a few facts cover what appears.

**Distance.** Compare **squared** distances rather than taking square roots — the comparison is identical, and it avoids floating point entirely.

```
d² = (x₁ − x₂)² + (y₁ − y₂)²
```

**Collinearity and slope.** Three points are collinear when the cross product of two of their difference vectors is zero:

```
(x₂ − x₁)(y₃ − y₁) − (y₂ − y₁)(x₃ − x₁) == 0
```

Use this rather than comparing slopes as `dy/dx`, which divides by zero on vertical lines and accumulates floating-point error. When slopes must be used as hash keys (Max Points on a Line), store the reduced fraction `(dy/g, dx/g)` with `g = gcd(dy, dx)` and a normalised sign — never a float.

**Rectangle overlap.** Two axis-aligned rectangles overlap when they overlap on *both* axes independently, which is the interval condition from [`10a_overlap_and_merge.md`](../10_intervals/10a_overlap_and_merge.md) applied twice.

**Areas.** The shoelace formula gives a polygon's area from its vertices; triangle area is half the absolute cross product of two edge vectors.

## Pitfalls

- **Floating point equality.** Never `==` on floats. Compare integers, compare cross products, or compare within a tolerance.
- **Overflow in the intermediate step.** `a * b // gcd(a, b)` overflows where `a // gcd(a, b) * b` does not.
- **Language-dependent `%` and `/` on negatives.** Check the convention before relying on it.
- **`0` and `1` in primality and factor loops.** Neither is prime, and a loop `for i in range(2, int(n**0.5) + 1)` does not execute at all for `n < 4`.
- **Forgetting the modulus until the end.** By then the number is already wrong in a fixed-width language.
- **Rotating a matrix with a temporary copy** when the problem says in place. The transpose-then-reverse decomposition is what it is testing.
