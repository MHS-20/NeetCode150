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

### Overflow

Python integers are arbitrary precision and never overflow. C++, Java, and Go integers do. Problems that constrain results to a 32-bit range (Reverse Integer, Divide Two Integers, String to Integer) are testing exactly this, and the check must happen **before** the operation:

```
safe to append digit d to x  ⟺  x < (INT_MAX − d) / 10
```

Checking after the fact is too late — the overflow has already occurred and, in C++, is undefined behaviour rather than a wrapped value.

### Integer division and negative numbers

Python's `//` floors toward negative infinity; C, C++, and Java truncate toward zero.

```
-7 // 2  ==  -4     (Python, floor)
-7 /  2  ==  -3     (C/Java, truncate)
```

Likewise `-7 % 3` is `2` in Python and `-1` in C. Problems specifying truncation need `int(a / b)` or an explicit sign fix, not `//`.

### Modular arithmetic

When a problem says "return the answer modulo 10⁹ + 7", the modulus is there to keep results inside 64 bits. Apply it as you go, not at the end — the intermediate value is what overflows.

```
(a + b) % m  =  ((a % m) + (b % m)) % m
(a · b) % m  =  ((a % m) · (b % m)) % m
```

Division does not distribute this way. It needs a modular inverse, which is beyond what these problems ask.

### GCD and LCM

Euclid's algorithm: repeatedly replace the larger number by its remainder against the smaller.

```
gcd(48, 18):  48 % 18 = 12
              18 % 12 = 6
              12 % 6  = 0   →  gcd = 6
```

```python
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

lcm = a * b // gcd(a, b)      # divide first in fixed-width languages, to avoid overflow
```

O(log(min(a, b))) — each step at least halves one operand. Available as `math.gcd`.

### Fast exponentiation

Computing `xⁿ` by multiplying `n` times is O(n). Squaring repeatedly makes it O(log n):

```
x¹³ = x⁸ · x⁴ · x¹          13 = 1101 in binary

square x each step, multiply into the result where the bit is set
```

```python
def power(x, n):
    if n < 0:
        x, n = 1 / x, -n
    result = 1
    while n:
        if n & 1:
            result *= x
        x *= x
        n >>= 1
    return result
```

The same halving idea appears in binary search and in merge sort — reducing `n` by a constant factor per step is what produces every logarithm in this field.

### Primes

The **sieve of Eratosthenes** finds every prime below `n` in O(n log log n): mark multiples of each prime, starting at `p·p` because everything smaller has already been marked by a smaller factor.

```
n = 30

2  3  4  5  6  7  8  9 10 ...
   ↑ mark 4, 6, 8, 10, ... then 9, 15, 21, ... then 25
remaining unmarked: 2 3 5 7 11 13 17 19 23 29
```

Testing a **single** number for primality needs only trial division up to `√n`: if `n = a·b` with `a ≤ b`, then `a ≤ √n`, so a factor above the square root implies one below it that was already checked.

## Digit and number tricks

**Extracting digits.** `n % 10` gives the last digit, `n //= 10` drops it. This is the loop behind reversing an integer, digit sums, and Happy Number.

**Palindrome Number without strings.** Reverse only the second half and compare it to the first, stopping when the reversed part is at least the remainder. Avoids overflow and halves the work.

**Cycle detection in a numeric sequence.** Happy Number repeats forever if it never reaches 1. Detect the loop with a set of seen values, or with the fast/slow pointer trick from [`linked_lists.md`](../data_structures/linked_lists.md) — the sequence is a linked list whose `next` is a computed function.

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

**Rectangle overlap.** Two axis-aligned rectangles overlap when they overlap on *both* axes independently, which is the interval condition from [`intervals.md`](intervals.md) applied twice.

**Areas.** The shoelace formula gives a polygon's area from its vertices; triangle area is half the absolute cross product of two edge vectors.

## Pitfalls

- **Floating point equality.** Never `==` on floats. Compare integers, compare cross products, or compare within a tolerance.
- **Overflow in the intermediate step.** `a * b // gcd(a, b)` overflows where `a // gcd(a, b) * b` does not.
- **Language-dependent `%` and `/` on negatives.** Check the convention before relying on it.
- **`0` and `1` in primality and factor loops.** Neither is prime, and a loop `for i in range(2, int(n**0.5) + 1)` does not execute at all for `n < 4`.
- **Forgetting the modulus until the end.** By then the number is already wrong in a fixed-width language.
- **Rotating a matrix with a temporary copy** when the problem says in place. The transpose-then-reverse decomposition is what it is testing.
