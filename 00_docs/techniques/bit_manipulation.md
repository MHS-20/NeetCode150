# Bit Manipulation and Bitmasking

## How to think about bit positions

Forget MSB/LSB terminology for a second — it is simpler than it sounds. An integer is just a sequence of bits, and the bits are *numbered* from the right, starting at position `0`:

```
bit position:  ... 4 3 2 1 0
bit value:     ... 0 0 0 0 0
```

Bit `0` is the rightmost bit — this is what people mean by LSB, "least significant bit"; it is just position 0. Bit `1` is next, then bit `2`, and so on. You never need to think about where they physically sit in memory. Treat position `0` as the starting point and count leftwards.

Position `d` is worth `2^d`, which is why the rightmost bit is "least significant": flipping it changes the number by 1, while flipping bit 10 changes it by 1024.

```
  0 0 1 0 1 1 0 1        =  32 + 8 + 4 + 1  =  45
  7 6 5 4 3 2 1 0           ← positions
```

## The key operator: left shift (`<<`)

`1 << d` produces a number with **only bit `d` turned on**, everything else `0`. It is the tool for saying "give me a number representing just position `d`".

```
1 << 0  =  0000 0001   (decimal 1)   → bit 0 is on
1 << 1  =  0000 0010   (decimal 2)   → bit 1 is on
1 << 3  =  0000 1000   (decimal 8)   → bit 3 is on
```

So `1 << d` moves the single `1` bit over by `d` positions.

Shifting a whole number works the same way, and has an arithmetic meaning: `x << 1` doubles `x`, `x >> 1` halves it (rounding down). Each position is worth twice the one to its right, so sliding everything left multiplies by 2.

```
x     =  0000 1101   (13)
x << 1 = 0001 1010   (26)
x >> 1 = 0000 0110   (6, the 1 shifted off the end is lost)
```

## Setting a bit: OR (`|`)

To turn *on* bit `d` in an existing number `mask`, without touching any other bits:

```
mask = mask | (1 << d)
```

OR-ing with `0` keeps the original bit unchanged; OR-ing with `1` forces that bit to `1`. Since `1 << d` is all zeros except at position `d`, every other bit of `mask` is left alone and only bit `d` is forced on.

```
mask      0 1 0 0 1 0
1 << 3    0 0 1 0 0 0
      OR  ─────────────
          0 1 1 0 1 0        bit 3 now on, everything else untouched
```

## Checking a bit: AND (`&`)

To test whether bit `d` is currently on:

```
(mask & (1 << d)) != 0
```

AND-ing with `0` forces a bit to `0` regardless of what it was; AND-ing with `1` keeps the original value. Since `1 << d` is all zeros except at position `d`, the expression zeroes every bit except that one — so the result is either `0` (bit was off) or nonzero (bit was on).

```
mask      0 1 1 0 1 0
1 << 3    0 0 1 0 0 0
     AND  ─────────────
          0 0 1 0 0 0        nonzero → bit 3 is on
```

An equivalent form pushes the bit down to position 0 instead: `(mask >> d) & 1`, which yields exactly `0` or `1`. Use whichever reads better; the `!= 0` version avoids the mistake of comparing `mask & (1 << d) == 1`, which is false for every position except 0.

## Do you need `int16` or a mask like `0xFF`?

No — that mixes up two different ideas, byte-level masking and bit-level flags. There is no need to isolate a "byte" at all. A plain 32-bit `int` is completely fine even if only 9 of its bits are used; the other 23 stay `0` and are harmless. Shrinking to `int16` or applying `0xFF`-style byte masks is a different technique for a different problem (byte packing), not this one.

## The rest of the operator set

| Operation | Expression | Effect |
|---|---|---|
| set bit `d` | `x \| (1 << d)` | force to 1 |
| clear bit `d` | `x & ~(1 << d)` | force to 0 |
| toggle bit `d` | `x ^ (1 << d)` | flip it |
| test bit `d` | `(x >> d) & 1` | read it |
| clear the lowest set bit | `x & (x - 1)` | see below |
| isolate the lowest set bit | `x & -x` | see below |

**NOT (`~`)** flips every bit, so `~(1 << d)` is all ones except at position `d` — AND-ing with that keeps everything and forces position `d` to zero. That is the clear operation.

**XOR (`^`)** is 1 when the two bits differ. Its properties are what make it useful far beyond bit fiddling:

```
x ^ 0 = x           identity
x ^ x = 0           self-cancelling
x ^ y = y ^ x       commutative — order never matters
(x ^ y) ^ z = x ^ (y ^ z)    associative
```

Self-cancellation plus order-independence is the whole trick behind Single Number: XOR every element of an array where each value appears twice except one, and the pairs annihilate each other regardless of their positions, leaving the lone value.

```
[4, 1, 2, 1, 2]  →  4^1^2^1^2  =  4^(1^1)^(2^2)  =  4^0^0  =  4
```

The same idea finds a missing number (XOR the indices against the values) and swaps two variables without a temporary.

## The two tricks worth memorising

**`x & (x - 1)` clears the lowest set bit.** Subtracting 1 flips the lowest `1` to `0` and turns every zero below it into a `1`; AND-ing with the original keeps only the bits above that point.

```
x        1 0 1 1 0 0
x - 1    1 0 1 0 1 1
   AND   ─────────────
         1 0 1 0 0 0        the lowest 1 is gone
```

Two immediate uses:

- **Counting set bits** in O(number of set bits) rather than O(32): loop `x &= x - 1` until `x` is zero, counting iterations. This is Brian Kernighan's algorithm.
- **Power-of-two test**: a power of two has exactly one bit set, so `x > 0 and (x & (x - 1)) == 0`.

**`x & -x` isolates the lowest set bit.** In two's complement, `-x` is `~x + 1`, which leaves everything above the lowest set bit inverted and the lowest set bit itself intact. AND-ing keeps exactly that one bit. It is the core of the Fenwick tree (binary indexed tree) and useful whenever you need to iterate over the set bits one at a time.

## Two's complement, briefly

Negative numbers are stored by inverting all bits and adding one. In 8 bits:

```
 5   0000 0101
-5   1111 1011      (~5 + 1)
```

The consequences that actually bite:

- The leftmost bit is the sign bit for signed types, so `-1` is all ones.
- **`>>` on a signed negative number is an arithmetic shift** in C, C++, and Java — it copies the sign bit in from the left, so `-8 >> 1` is `-4`, not a huge positive number. Java's `>>>` is the unsigned version that shifts in zeros. C++ has no `>>>`; cast to an unsigned type instead.
- Overflow wraps: `INT_MAX + 1` is `INT_MIN`.

**Python is the exception and it matters.** Python integers are arbitrary precision, so they behave as if they have infinitely many sign bits. `~5` is `-6`, not `250`, and shifting left never overflows. Problems asking for 32-bit behaviour need an explicit mask:

```python
MASK = 0xFFFFFFFF
x &= MASK                              # confine to 32 bits
if x > 0x7FFFFFFF:                     # sign bit set → convert to a negative int
    x -= 0x100000000
```

Forgetting this makes Reverse Bits and the add-two-numbers-without-`+` problems loop forever or return wrong values in Python specifically.

## Bitmasking: an integer as a set

This is where bits become an algorithmic technique rather than an arithmetic one. An integer with `n` bits represents a **subset** of `n` items: bit `i` is on if item `i` is in the set.

```
items:  {a, b, c, d}
mask 0b1010  =  {b, d}         (bits 1 and 3 on)
mask 0b1111  =  all four
mask 0b0000  =  empty set
```

Set operations become single machine instructions:

| Set operation | Bitmask |
|---|---|
| add item `i` | `mask \| (1 << i)` |
| remove item `i` | `mask & ~(1 << i)` |
| contains item `i` | `mask & (1 << i)` |
| union | `a \| b` |
| intersection | `a & b` |
| difference `a \ b` | `a & ~b` |
| size | `bin(mask).count('1')` / `popcount` |
| all `n` items | `(1 << n) - 1` |
| is subset of `b` | `(a & b) == a` |

`(1 << n) - 1` is worth understanding rather than memorising: `1 << n` is a single bit at position `n`, so subtracting 1 turns it into `n` consecutive ones below that position.

**Enumerating every subset** of `n` items is then just counting from `0` to `2ⁿ - 1`:

```python
for mask in range(1 << n):              # all 2ⁿ subsets
    subset = [items[i] for i in range(n) if mask & (1 << i)]
```

This is the iterative alternative to the recursive subsets in [`backtracking.md`](backtracking.md), and it is often shorter. Both are O(2ⁿ · n).

**Bitmask DP** uses the mask as a DP state: `dp[mask]` is the best answer for the set of items in `mask` (see [`dynamic_programming.md`](../dynamic_programming/dynamic_programming.md)). This is why the constraint table in [`pattern_recognition.md`](../foundations/pattern_recognition.md) lists `n ≤ 20` as a bitmask signal — `2²⁰` is about a million states, which fits, while `2³⁰` does not. Travelling Salesman is the standard example: `dp[mask][i]` = shortest route visiting exactly the cities in `mask` and ending at `i`.

A useful idiom for iterating the **submasks** of a mask:

```python
sub = mask
while sub:
    process(sub)
    sub = (sub - 1) & mask      # next smaller subset of mask
```

## Complexity

Bit operations on a machine word are **O(1)** — a single CPU instruction, regardless of how many bits are set. That is the appeal: a 64-element set fits in one register and unions in one cycle.

What is *not* O(1):

- Looping over all 32 or 64 positions is O(w) for word size `w`. Usually treated as constant, but say so if asked.
- `x & (x - 1)` counting is O(set bits), which is better than O(w) for sparse numbers.
- Iterating all `2ⁿ` masks is exponential. The bit tricks make each state cheap; they do not change the number of states.

Space is the real win in bitmask DP: `2ⁿ` integers instead of `2ⁿ` sets or lists, which is the difference between fitting in memory and not.

## Where it shows up

**Single Number family.** XOR self-cancellation. The variant where every element appears three times needs counting bits modulo 3 per position instead.

**Counting bits for 0..n.** `dp[i] = dp[i >> 1] + (i & 1)` — the count for `i` is the count for `i` with its last bit removed, plus that bit. A one-line DP.

**Reverse Bits, Number of 1 Bits, Power of Two.** Direct applications of the tricks above.

**Sum of Two Integers without `+`.** `a ^ b` is the sum without carries, `(a & b) << 1` is the carries; loop until the carry is zero. Needs the 32-bit masking in Python.

**Subsets and permutations by mask.** The iterative enumeration above.

**Bitmask DP.** Assignment problems, TSP, "cover all items" problems with `n ≤ 20`.

**Compact state in a grid or graph.** A visited set of ≤ 64 cells in one integer, so DP states can be hashed cheaply.

## Pitfalls

- **Operator precedence.** In C, C++, and Java, `&` binds *looser* than `==`, so `x & 1 == 0` parses as `x & (1 == 0)`. Parenthesise always: `(x & 1) == 0`. Python gets this right, but the habit is worth keeping.
- **Comparing to 1 instead of 0.** `mask & (1 << d) == 1` is wrong for every `d` except 0; compare against `0` or shift down first.
- **Shifting by more than the word width.** Undefined behaviour in C and C++, and a silent modulo of the shift amount in Java (`x << 32` is `x << 0`). Python is fine.
- **Python's infinite-width integers.** `~`, negative numbers, and left shifts do not wrap. Mask with `0xFFFFFFFF` when 32-bit semantics are required.
- **Arithmetic vs. logical right shift** on negative numbers. `>>` keeps the sign in most languages; use `>>>` in Java or an unsigned cast in C++.
- **Using bitmasks where a set is clearer.** Under about 20 items and in a hot loop, a mask wins. Otherwise a hash set is more readable and just as fast.
- **Mutating a mask inside a loop over its bits** without saving the original. Iterate over a copy, or compute positions first.
