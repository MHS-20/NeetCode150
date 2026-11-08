# Masking: Reading and Changing Chosen Bits

A **mask** is a number whose bits mark the positions an operation should touch. Combined with `&`, `|` or `^`, a mask reads, sets, clears or flips those positions and leaves every other bit as it was. The single-bit cases come first, then masks covering several bits, then the use of an integer as a set of small numbers.

The behaviour of each operator on one bit is in [operators](9c_operators_and_shifts.md#how-each-operator-acts-on-one-bit). In short: `& 0` clears, `| 1` sets, `^ 1` flips, and `& 1`, `| 0`, `^ 0` leave the bit unchanged.

## Single-bit masks

`1 << d` has only bit `d` set. All four single-bit operations start from it.

### Set bit `d`: `x | (1 << d)`

OR forces bit `d` to 1. Every other position of the mask is 0, and `| 0` leaves a bit unchanged.

Setting bit 3 of `x = 0100 0010`:

```
x          0 1 0 0 0 0 1 0
1 << 3     0 0 0 0 1 0 0 0
────────── OR ─────────────
           0 1 0 0 1 0 1 0      bit 3 is now 1
```

If bit 3 was already 1, the result equals `x`.

### Clear bit `d`: `x & ~(1 << d)`

The mask for clearing is the opposite of the one for setting: all ones except at position `d`. `~(1 << d)` builds it. AND then forces bit `d` to 0, and `& 1` keeps all the others.

Clearing bit 6 of `x = 0100 1010`:

```
1 << 6       0 1 0 0 0 0 0 0
~(1 << 6)    1 0 1 1 1 1 1 1
x            0 1 0 0 1 0 1 0
──────────── AND ────────────
             0 0 0 0 1 0 1 0      bit 6 is now 0
```

### Flip bit `d`: `x ^ (1 << d)`

XOR flips bit `d` and leaves the others, since `^ 1` flips and `^ 0` keeps. Applying the same flip twice gives back `x`.

```
x          0 0 0 0 1 0 1 0
1 << 1     0 0 0 0 0 0 1 0
────────── XOR ────────────
           0 0 0 0 1 0 0 0      bit 1 went from 1 to 0
```

### Test bit `d`

Two forms exist, and both are correct:

```
(x & (1 << d)) != 0     # true if bit d is set
(x >> d) & 1            # 1 if bit d is set, 0 if not
```

The first keeps bit `d` where it is and clears everything else. The result is `1 << d` if the bit was set, and `0` if not:

```
x          0 1 0 0 1 0 1 0
1 << 3     0 0 0 0 1 0 0 0
────────── AND ────────────
           0 0 0 0 1 0 0 0      = 8, not 0, so bit 3 is set
```

The second moves bit `d` down to position 0 first, then keeps only position 0, so the result is exactly 0 or 1.

A common mistake mixes the two: `(x & (1 << d)) == 1`. In the example above, `x & (1 << 3)` is `8`, and `8 == 1` is false even though the bit is set. The comparison works only for `d = 0`. Compare with `0`, or shift down first.

The parentheses around `x & (1 << d)` are required in C, C++, Java and JavaScript ([precedence](9c_operators_and_shifts.md#operator-precedence)).

### Summary

| Operation | Expression |
|---|---|
| set bit `d` | `x \| (1 << d)` |
| clear bit `d` | `x & ~(1 << d)` |
| flip bit `d` | `x ^ (1 << d)` |
| test bit `d` | `(x >> d) & 1` |

## Masks covering several bits

### The low `n` bits: `(1 << n) - 1`

`1 << n` is a single 1 at position `n`. Subtracting 1 borrows from that position, which turns it to 0 and every position below it to 1:

```
1 << 4          0 0 0 1 0 0 0 0      (16)
(1 << 4) - 1    0 0 0 0 1 1 1 1      (15)
```

So `(1 << n) - 1` is `n` ones at the bottom. `x & ((1 << n) - 1)` keeps the low `n` bits of `x` and clears the rest. For non-negative `x`, that equals `x % 2^n`.

For `n` equal to the type's width this breaks, because `1 << 32` on a 32-bit type is undefined or wrong ([shifts](9c_operators_and_shifts.md#shifting-by-the-full-width-or-more)). Write the all-ones constant directly instead: `0xFFFFFFFF`.

### Extracting a field: `(x >> k) & mask`

A **field** is a run of bits inside a number that holds a separate small value. To read the field of width `w` that starts at position `k`, shift it down to position 0, then keep its `w` bits:

```
(x >> k) & ((1 << w) - 1)
```

Reading the 4-bit field at positions 4–7 of `x = 1011 0110` (0xB6):

```
x                  1 0 1 1 0 1 1 0
x >> 4             0 0 0 0 1 0 1 1      field now at positions 0–3
& 0000 1111        0 0 0 0 1 0 1 1      = 11
```

Reading the 3-bit field at positions 2–4 of the same `x`:

```
x                  1 0 1 1 0 1 1 0
x >> 2             0 0 1 0 1 1 0 1
& 0000 0111        0 0 0 0 0 1 0 1      = 5
```

Without the AND, the bits above the field stay in the result. In the second example, `x >> 2` alone is 45, not 5.

### Byte masks and type width

`0xFF` keeps the low 8 bits, `0xFFFF` the low 16, and `0xFFFFFFFF` the low 32. They are masks of the form `(1 << n) - 1` for `n = 8, 16, 32`.

These masks are not needed to use only some of the bits of a number. A 32-bit `int` that holds 9 flags in bits 0–8 has 23 more bits that stay 0. Those zeros do not change any of the operations above, so the number needs no `0xFF` mask and no smaller type such as `int16`. Byte masks are for taking a number apart into bytes, as in parsing a binary format, or for limiting a value to a fixed width, as in the Python section below.

### Repeating masks

Some masks repeat a short pattern across the whole width. The patterns for 8 bits, extended to 32 by repeating the hex digits:

```
0x55   0 1 0 1 0 1 0 1      every other bit        (0x55555555)
0x33   0 0 1 1 0 0 1 1      pairs of bits          (0x33333333)
0x0F   0 0 0 0 1 1 1 1      groups of four bits    (0x0F0F0F0F)
```

Each mask has a complement that selects the other half of every group: `0xAA` is `1010 1010`, `0xCC` is `1100 1100`, and `0xF0` is `1111 0000`.

The divide-and-conquer solution to Reverse Bits (190) uses them to swap neighbouring groups. Each line swaps every group with its neighbour: first the two halves, then smaller groups, down to single bits. Reversing the 8-bit value `1011 0001`:

```
start                                 1 0 1 1 0 0 0 1
swap 4-bit groups    ((x & 0xF0) >> 4) | ((x & 0x0F) << 4)
                                      0 0 0 1 1 0 1 1
swap 2-bit groups    ((x & 0xCC) >> 2) | ((x & 0x33) << 2)
                                      0 1 0 0 1 1 1 0
swap single bits     ((x & 0xAA) >> 1) | ((x & 0x55) << 1)
                                      1 0 0 0 1 1 0 1
```

The result, `1000 1101`, is `1011 0001` read backwards. In each line, one mask picks the left member of every pair and shifts it right, the other picks the right member and shifts it left, and OR puts the two halves together. Eight bits need three swaps. Thirty-two bits need five: 16, 8, 4, 2 and 1.

## Keeping Python to 32 bits

Python's integers have no width, so they never wrap ([integer representation](9a_integer_representation.md#integer-types-in-each-language)). Problems that assume 32-bit integers need the wrapping done by hand. It takes two steps.

**Step 1, keep the low 32 bits.** `x & 0xFFFFFFFF` gives the unsigned reading of the low 32 bits. For `x = -2`, it gives `4294967294`, which is `0xFFFFFFFE`.

**Step 2, convert back to signed.** If bit 31 is set, the 32-bit signed value is negative, and equals the unsigned value minus `2^32`:

```python
MASK = 0xFFFFFFFF
x &= MASK
if x > 0x7FFFFFFF:          # bit 31 is set
    x -= 1 << 32            # 4294967294 - 4294967296 = -2
```

The Python solution to Sum of Two Integers (371) writes the second step as `~(x ^ MASK)`, which gives the same result. `x ^ MASK` flips the low 32 bits, and `~` flips every bit including Python's infinite sign bits. For `x = 0xFFFFFFFE`, both forms give `-2`.

### Sum of Two Integers without the mask

The solution adds without `+`. `a ^ b` is the sum without carries, and `(a & b) << 1` is the carries. The loop repeats until the carry is 0. In a 32-bit type, the carry eventually shifts out of the top bit and disappears.

In Python, it never shifts out. For `a = -1, b = 1`, an unmasked version was stopped after 200 loops. The carry had grown to a 61-digit number and was still growing. With the mask applied to the sum and the carry on every loop, the carry is dropped at bit 32 and the loop ends. The masked version returns `0`.

### Reverse Bits without the mask

The divide-and-conquer Reverse Bits in Python does not need a separate `0xFFFFFFFF` mask. The first line, `(x >> 16) | (x << 16)`, produces bits above position 31, which a 32-bit type would drop. The next line ANDs with `0xFF00FF00` and `0x00FF00FF`, and both have zeros above position 31. That AND removes the extra bits before they can affect the result.

An unmasked Python version gave the same output as a direct reversal for 100 000 random 32-bit inputs. The repo's Python solution also masks the first line, which does no harm but is not required.

## An integer as a set

An integer of `n` bits can stand for a **subset** of `n` items numbered `0` to `n - 1`. Bit `i` is 1 if item `i` is in the set. For the items `{a, b, c, d}`, numbered 0 to 3:

```
mask     items
0000     {}
0101     {a, c}            bits 0 and 2
1010     {b, d}            bits 1 and 3
1111     {a, b, c, d}
```

Set operations then become the bit operations from earlier on this page:

| Set operation | Bit expression |
|---|---|
| add item `i` | `mask \| (1 << i)` |
| remove item `i` | `mask & ~(1 << i)` |
| is item `i` in it | `(mask >> i) & 1` |
| union | `a \| b` |
| intersection | `a & b` |
| difference `a \ b` | `a & ~b` |
| is `a` a subset of `b` | `(a & b) == a` |
| number of items | popcount ([tricks](9e_tricks.md#counting-set-bits-number-of-1-bits-191)) |
| all `n` items | `(1 << n) - 1` |

Each of these is one machine instruction on a 32- or 64-bit integer, as long as `n` fits in the type.

### Every subset

The subsets of `n` items are the integers from `0` to `2^n - 1`. Counting through them visits every subset once:

```python
for mask in range(1 << n):
    subset = [items[i] for i in range(n) if (mask >> i) & 1]
```

This produces the same subsets as the recursive version in [backtracking](../06_techniques/6a_backtracking.md). Both take O(2^n · n) time.

### Every subset of a given set

To visit the subsets of one mask `m` (its **submasks**) without testing all `2^n` numbers:

```python
sub = m
while sub:
    process(sub)
    sub = (sub - 1) & m
```

Subtracting 1 clears the lowest set bit of `sub` and sets every bit below it. ANDing with `m` then removes the bits that are not in `m`. For `m = 1011`, the loop visits:

```
1011  1010  1001  1000  0011  0010  0001
```

That is every non-empty subset of `{0, 1, 3}`, from largest to smallest. The empty set `0000` ends the loop and has to be handled separately if it counts.

### Bitmask DP

A mask can also be the state of a DP table: `dp[mask]` holds the answer for the items in `mask`. The table has `2^n` entries, which limits the technique to small `n`. At `n = 20` the table has about a million entries, and at `n = 30` about a billion. That is why `n ≤ 20` in a problem's constraints suggests bitmask DP ([pattern recognition](../01_foundations/1b_pattern_recognition.md)).

Travelling Salesman is the usual example. `dp[mask][i]` is the length of the shortest route that visits the cities in `mask` and ends at city `i`.
