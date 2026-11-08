# Bitwise Operators and Shifts

The bitwise operators work on each bit position separately. A shift moves every bit left or right by a given number of positions. For negative numbers and large shift counts, the languages in this repo give different results, so a shift copied from one language to another can change its output.

The examples use 8-bit values to keep the rows short. The rules are the same at 32 and 64 bits. Every non-obvious result in the tables was printed by a test program in the language named.

## AND, OR, XOR, NOT

`&`, `|` and `^` take two numbers and combine the bits at each position. Position `d` of the result depends only on position `d` of the two inputs.

```
a  b │ a & b   a | b   a ^ b
─────┼───────────────────────
0  0 │   0       0       0
0  1 │   0       1       1
1  0 │   0       1       1
1  1 │   1       1       0
```

- **AND** gives 1 only where both inputs are 1.
- **OR** gives 1 where at least one input is 1.
- **XOR** (exclusive or) gives 1 where the inputs differ.

One worked byte, `a = 1100 1010` (202) and `b = 1010 0110` (166):

```
a        1 1 0 0 1 0 1 0
b        1 0 1 0 0 1 1 0
─────────────────────────
a & b    1 0 0 0 0 0 1 0      (130)
a | b    1 1 1 0 1 1 1 0      (238)
a ^ b    0 1 1 0 1 1 0 0      (108)
```

**NOT** (`~`) takes one number and flips every bit:

```
a        1 1 0 0 1 0 1 0
~a       0 0 1 1 0 1 0 1
```

For a signed type, `~x` equals `-x - 1`, from the two's complement rule `~x + 1 = -x` ([integer representation](11a_integer_representation.md#negation-invert-and-add-one)). So `~5` is `-6` in every language here. Python gives `-6` too, even though its integers have no fixed width. For an 8-bit unsigned value, `~5` is `250`: in C, `(uint8_t)~5` printed `250`.

Two languages spell NOT differently. Rust uses `!` (`!5i32` is `-6`), and Go uses unary `^` (`^x` with `x := 5` is `-6`).

## How each operator acts on one bit

The masking techniques in [masking](11d_masking.md) depend on what each operator does when one input bit is fixed. Here `x` is any bit:

| Operation | Result | Effect on `x` |
|---|---|---|
| `x & 0` | 0 | forced to 0 |
| `x & 1` | `x` | kept |
| `x \| 0` | `x` | kept |
| `x \| 1` | 1 | forced to 1 |
| `x ^ 0` | `x` | kept |
| `x ^ 1` | `~x` | flipped |

For each operator, one constant leaves the bit alone and the other changes it. A **mask** is a number whose bits choose which positions get changed.

## Left shift

`x << k` moves every bit `k` positions to the left. The `k` bits that leave at the top are dropped, and `k` zeros come in at the bottom:

```
x        0 0 0 0 1 1 0 1      (13)
x << 1   0 0 0 1 1 0 1 0      (26)
x << 2   0 0 1 1 0 1 0 0      (52)
```

Each position is worth twice the one to its right, so `x << k` multiplies by `2^k` as long as no `1` is pushed out at the top. `1 << k` is a number with only bit `k` set. It is the starting point for every single-bit mask.

When a `1` reaches the top bit of a signed type, the result reads as negative: `1 << 31` is `-2147483648` in Java ([overflow](11b_overflow.md#shifting-a-32-bit-1)).

## Right shift: logical and arithmetic

`x >> k` moves every bit `k` positions to the right. The `k` bits that leave at the bottom are dropped. Something has to fill the `k` empty positions at the top, and there are two choices:

- **Logical shift**: fill with zeros.
- **Arithmetic shift**: fill with copies of the sign bit (the old top bit).

For a non-negative number the sign bit is 0, so the two give the same result. For a negative number they differ. Using `-8` in 8 bits:

```
-8               1 1 1 1 1 0 0 0
arithmetic >> 1  1 1 1 1 1 1 0 0      (-4)   top filled with 1, the sign bit
logical    >> 1  0 1 1 1 1 1 0 0      (124)  top filled with 0
```

The arithmetic shift keeps the number negative and halves it. The logical shift treats the bits as unsigned.

Which shift `>>` performs depends on the language and the type:

| Language | `>>` on a signed type | `>>` on an unsigned type | Logical shift of a signed value |
|---|---|---|---|
| C / C++ | arithmetic on gcc | logical | cast to unsigned first |
| Java | arithmetic | (no unsigned types) | `>>>` |
| Go | arithmetic | logical | convert to `uint32` / `uint64` first |
| Rust | arithmetic | logical | cast to `u32` / `u64` first |
| JavaScript | arithmetic | (no unsigned types) | `>>>` |
| Python | arithmetic | (no unsigned types) | mask first ([masking](11d_masking.md#keeping-python-to-32-bits)) |

All six printed `-8 >> 1 = -4`. For C, the result of right-shifting a negative value is implementation-defined, and gcc documents it as an arithmetic shift. C++20 defines it as arithmetic for every compiler.

At 32 bits, Java and JavaScript both printed `-8 >>> 1 = 2147483644`, which is `0x7FFFFFFC`: the sign bit became 0 and the rest moved down.

Reverse Bits (190) needs logical shifts, because it moves the top bit to the bottom as an ordinary bit. The C, Go and Rust ports take `uint32` / `u32` input. The Java and JavaScript ports use `>>>`.

## Shifts as multiplication and division

`x << 1` doubles `x`, and `x >> 1` halves it. The halving does not always match `/ 2`, because they round differently:

| Expression | Result | Rounding |
|---|---|---|
| `7 >> 1` | `3` | |
| `7 / 2` | `3` | |
| `-7 >> 1` | `-4` | toward minus infinity |
| `-7 / 2` | `-3` | toward zero (C, C++, Java, Go, Rust) |

The arithmetic shift drops the lowest bit, and dropping bits always rounds down, toward minus infinity. In 8 bits, `-7` is `1111 1001`. Shifting gives `1111 1100`, which is `-4`. Division in C-family languages rounds toward zero instead ([overflow](11b_overflow.md#division-and-remainder-of-negative-numbers)).

For non-negative values the two match. `i >> 1` in Counting Bits (338) is safe, because `i` is never negative.

## Shifting by the full width or more

Shifting a 32-bit value by 32 or more positions is handled differently in every language. The test shifted `1` by a variable `s = 32`:

| Language | `1 << 32` on a 32-bit type | Rule |
|---|---|---|
| C / C++ | undefined behaviour; printed `1` | the sanitizer reports `shift exponent 32 is too large for 32-bit type` |
| Java | `1` | only the low 5 bits of the count are used, so 32 acts as 0 and 33 as 1 |
| JavaScript | `1` | same as Java: the count is taken mod 32 |
| Go | `0` | shifts of the full width or more give 0 |
| Rust, debug build | panic | |
| Rust, release build | `1` | the count is masked, as in Java |
| Python | `4294967296` | no width, no limit |

Rust's `checked_shl` returns `None` for a count too large, and `wrapping_shl` masks the count explicitly. Go's result of `0` comes from the language specification, so it is the same in every build.

In practice, a loop over bit positions should stop at `width - 1`. Building a mask with `(1 << n) - 1` fails at `n = 32` on a 32-bit type. For `n = 32`, the C fix is `(uint32_t)-1` or a 64-bit shift: `(1ULL << 32) - 1`.

## Operator precedence

In C, C++, Java and JavaScript, `&`, `|` and `^` bind **more loosely** than `==` and `!=`. The expression `x & 1 == 0` is read as `x & (1 == 0)`. With `x = 4`:

| Language | `x & 1 == 0` | Why |
|---|---|---|
| C / C++ | `0` (wrong) | `4 & (1 == 0)` is `4 & 0` |
| JavaScript | `0` (wrong) | same as C |
| Java | compile error | `int & boolean`: `bad operand types for binary operator '&'` |
| Go | `true` | `&` binds tighter than `==` |
| Rust | `true` | `&` binds tighter than `==` |
| Python | `True` | `&` binds tighter than `==` |

The correct answer is true, since 4 is even. In C, C++ and JavaScript the code compiles and runs without warning by default and returns the wrong value. Writing the parentheses, `(x & 1) == 0`, gives the right result in all six languages.

Shifts have a precedence difference of their own. With `n = 3`, `1 << n - 1` printed:

| Language | `1 << n - 1` | Read as |
|---|---|---|
| C, C++, Java, JavaScript, Python, Rust | `4` | `1 << (n - 1)` |
| Go | `7` | `(1 << n) - 1` |

Go puts `<<` at the same level as `*`, above `-`. The other languages put `-` above `<<`. Parentheses again remove the difference.
