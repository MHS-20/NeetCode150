# Integer Representation: Bits, Two's Complement and Type Limits

Every bit trick works on the stored bit pattern of an integer, not on its decimal value. Before reading `x & (x - 1)` or `x >> 1`, the reader needs two facts: which bit pattern a given number has, and how many bits the type holds. Both change between languages, and both decide what a bit trick returns on negative numbers.

## Bit positions and place values

An integer of width `n` is a row of `n` bits. The bits are numbered from the right, starting at position `0`:

```
position:   7   6   5   4   3   2   1   0
value:    128  64  32  16   8   4   2   1
```

Position `d` is worth `2^d`. The number stored is the sum of the values of the positions holding a `1`:

```
bits:       0   0   1   0   1   1   0   1
position:   7   6   5   4   3   2   1   0

            32 + 8 + 4 + 1  =  45
```

The rightmost bit, position `0`, is called the **least significant bit** (LSB). Flipping it changes the number by 1. The leftmost bit is the **most significant bit** (MSB). In an 8-bit number, flipping it changes the number by 128.

Hexadecimal is used for bit patterns because one hex digit covers four bits:

```
binary:   0010 1101
hex:         2    D      →  0x2D  =  45
```

`0xFF` is eight ones, `0xFFFFFFFF` is thirty-two ones, and `0x80000000` is a single `1` at position 31.

## Unsigned integers

An **unsigned** integer of width `n` uses all `n` bits for the value. Its range is `0` to `2^n - 1`:

| Width | Smallest | Largest | Largest in hex |
|---|---|---|---|
| 8 bits | 0 | 255 | `0xFF` |
| 16 bits | 0 | 65 535 | `0xFFFF` |
| 32 bits | 0 | 4 294 967 295 | `0xFFFFFFFF` |
| 64 bits | 0 | 18 446 744 073 709 551 615 | `0xFFFFFFFFFFFFFFFF` |

The largest value is all ones. Adding 1 to it carries out of the top bit, and that carry has nowhere to go. The stored result is `0`. This wraparound is the defined behaviour for unsigned types in C, C++, Go and Rust's `wrapping_*` methods ([overflow](9b_overflow.md) covers each language).

## Two's complement

Signed integers need a way to store negative numbers. Every language used in this repo stores them in **two's complement**.

### The rule

In two's complement with `n` bits, the top bit (position `n - 1`) is worth `-2^(n-1)` instead of `+2^(n-1)`. Every other position keeps its usual positive value.

For 8 bits, the place values become:

```
position:     7    6   5   4   3   2   1   0
value:     -128   64  32  16   8   4   2   1
```

Reading a pattern is the same sum as before, with the top bit counted as negative:

```
1111 1011  =  -128 + 64 + 32 + 16 + 8 + 2 + 1  =  -5
1000 0000  =  -128
0111 1111  =  64 + 32 + 16 + 8 + 4 + 2 + 1     =  127
1111 1111  =  -128 + 127                       =  -1
```

A pattern with the top bit set is negative, and one with the top bit clear is zero or positive. That is why the top bit is called the **sign bit**, although it is an ordinary place value with a negative weight, not a separate flag.

### All sixteen 4-bit values

Four bits are small enough to list every pattern. The same 16 patterns read as unsigned on the left and as two's complement on the right:

```
pattern   unsigned   signed            pattern   unsigned   signed
 0000        0          0                1000        8         -8
 0001        1          1                1001        9         -7
 0010        2          2                1010       10         -6
 0011        3          3                1011       11         -5
 0100        4          4                1100       12         -4
 0101        5          5                1101       13         -3
 0110        6          6                1110       14         -2
 0111        7          7                1111       15         -1
```

Three points follow from the table:

- **The left half is identical.** Patterns with the top bit clear mean the same number in both readings. Small non-negative values can move between signed and unsigned types unchanged.
- **The right half differs by 16.** Each pattern with the top bit set is `2^4 = 16` less as a signed value than as an unsigned one: `1011` is 11 unsigned and `11 - 16 = -5` signed.
- **There is one more negative value than positive.** The signed range is `-8` to `7`. Zero takes one of the eight patterns with the top bit clear, so only seven are left for positive numbers.

### Adding 1, pattern by pattern

Adding 1 always moves to the next pattern in the list. After `1111`, the carry leaves the four bits and the pattern starts again at `0000`:

```
pattern:   0000  0001 ... 0110  0111  1000  1001 ... 1110  1111 │ 0000
unsigned:     0     1 ...    6     7     8     9 ...   14    15 │    0
signed:       0     1 ...    6     7    -8    -7 ...   -2    -1 │    0
                                   ↑                          ↑
                       signed jump: 7 + 1 = -8     unsigned jump: 15 + 1 = 0
```

The patterns themselves never jump. Only the reading does. The unsigned reading jumps from 15 to 0 at the end of the list. The signed reading jumps from 7 to -8 in the middle, where the top bit turns on. An integer overflow is a step across one of these two jumps.

### Negation: invert and add one

To negate a two's complement number, flip every bit and add 1:

```
 5        0000 0101
~5        1111 1010      flip every bit
~5 + 1    1111 1011      add one          →  -5
```

The rule works because `x + ~x` is all ones, which is `-1`. So `~x = -1 - x`, and `~x + 1 = -x`.

Two edge cases come straight from the circle:

- **`-0` is `0`.** `~0000 0000 + 1` is `1 0000 0000`. The ninth bit is dropped and `0000 0000` remains.
- **The smallest value is its own negative.** In 8 bits, `-(-128)` gives `~1000 0000 + 1 = 0111 1111 + 1 = 1000 0000`, which is `-128` again. `+128` does not fit in 8 bits. In 32 bits the same happens with `-2^31`, which is the source of the `abs(INT_MIN)` bug in [overflow](9b_overflow.md).

### The range of a signed type

A signed type of width `n` holds `-2^(n-1)` to `2^(n-1) - 1`:

| Width | Smallest | Largest |
|---|---|---|
| 8 bits | -128 | 127 |
| 16 bits | -32 768 | 32 767 |
| 32 bits | -2 147 483 648 | 2 147 483 647 |
| 64 bits | -9 223 372 036 854 775 808 | 9 223 372 036 854 775 807 |

In hex, the 32-bit limits are `0x7FFFFFFF` (largest, a zero followed by 31 ones) and `0x80000000` (smallest, a one followed by 31 zeros).

## Integer types in each language

The same name means different widths in different languages. The table lists the types the solutions in this repo use. C and C++ widths were measured with `sizeof` on x86-64 Linux with gcc. The C standard fixes only minimum widths for `int` and `long`, so `int32_t`, `uint32_t` and `int64_t` from `<stdint.h>` are the types to use when the width matters.

| Language | 32-bit signed | 32-bit unsigned | 64-bit signed | Notes |
|---|---|---|---|---|
| C / C++ | `int`, `int32_t` | `unsigned`, `uint32_t` | `long long`, `int64_t` | `long` was 8 bytes on the test machine |
| Java | `int` | none | `long` | no unsigned types at all |
| Go | `int32` | `uint32` | `int64`, `int` | `int` was 64 bits on the test machine |
| Rust | `i32` | `u32` | `i64` | `usize` is the index type, unsigned |
| JavaScript | (see below) | (see below) | none | numbers are 64-bit floats |
| Python | none | none | none | `int` has no fixed width |

**JavaScript** stores every number as a 64-bit floating-point value. The bitwise operators (`& | ^ ~ << >> >>>`) first convert their operands to 32-bit integers, run the operation, and return a 32-bit result. `>>>` returns it as unsigned and the others return it as signed. Outside the bitwise operators, integers are exact only up to `2^53`:

```js
2 ** 53       // 9007199254740992
2 ** 53 + 1   // 9007199254740992   the +1 is lost
```

For exact integers above `2^53`, JavaScript has `BigInt` (`9007199254740993n`).

**Python** integers grow as needed. `1 << 100` is an exact 31-digit number. Python still uses two's complement for the bitwise operators, but treats each number as if it had infinitely many copies of its sign bit to the left. So `~5` is `-6`, the two's complement answer, and not `250` as it would be for an 8-bit unsigned value.

## Reading the same bits as a different type

Converting between a signed and an unsigned type of the **same width** keeps the bits and changes only the reading. The values below were printed by each language:

| Expression | Bits kept | Result |
|---|---|---|
| C: `(unsigned)-1` | 32 ones | `4294967295` |
| C: `(int)0xFFFFFFFFu` | 32 ones | `-1` |
| Rust: `(-1i32) as u32` | 32 ones | `4294967295` |
| Go: `int(int32(w))` with `w := uint32(0xFFFFFFFF)` | 32 ones | `-1` |
| JavaScript: `-1 >>> 0` | 32 ones | `4294967295` |
| Python: `-1 & 0xFFFFFFFF` | 32 ones | `4294967295` |

The C, Rust and Go rows are casts. JavaScript's `>>> 0` shifts by zero places, which leaves the bits alone and returns the unsigned reading. Python has no 32-bit type, so the mask keeps the low 32 bits and the result is the unsigned reading of them. The reverse direction in Python (unsigned back to signed) is in [masking](9d_masking.md#keeping-python-to-32-bits).

These conversions are how solutions that need unsigned arithmetic accept signed input. Sum of Two Integers (371) in C, Go and Rust converts both inputs to unsigned 32-bit, does the work there, and converts the result back to signed at the end.
