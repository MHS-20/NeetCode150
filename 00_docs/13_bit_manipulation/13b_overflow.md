# Overflow: What Each Language Does When a Value Does Not Fit

An arithmetic result **overflows** when it lies outside the range of its type. `2147483647 + 1` needs 2 147 483 648, and a 32-bit signed integer stops at 2 147 483 647 ([integer representation](13a_integer_representation.md#the-range-of-a-signed-type)). The languages in this repo answer this in four different ways: wrap around, stop the program, give a wrong float, or never overflow at all. A port that copies the C++ arithmetic into another language can change its answer on the boundary tests without any change to the code's logic.

Every result on this page was printed by a test program on x86-64 Linux: gcc for C and C++, OpenJDK for Java, the Go toolchain, rustc, Node.js and CPython.

## `INT_MAX + 1` in every language

The test adds 1 to the largest 32-bit signed value. The value was kept in a variable so that the compiler could not reject the expression ahead of time.

| Language | Code | Result |
|---|---|---|
| C / C++ | `int m = INT_MAX; m + 1` | **undefined behaviour**; printed `-2147483648` at `-O0` |
| Java | `Integer.MAX_VALUE + 1` | `-2147483648` (wraps) |
| Go | `var m int32 = math.MaxInt32; m++` | `-2147483648` (wraps) |
| Rust, debug build | `i32::MAX + 1` | panic: `attempt to add with overflow` |
| Rust, release build | `i32::MAX + 1` | `-2147483648` (wraps) |
| JavaScript | `2147483647 + 1` | `2147483648` (no 32-bit type; floats) |
| Python | `2**31 - 1 + 1` | `2147483648` (no overflow) |

Wrapping means the bits are kept and the carry out of the top bit is dropped. The pattern `0111…1` plus 1 is `1000…0`, which reads as `-2^31`. This is the signed jump from 7 to -8 in the 4-bit table of [integer representation](13a_integer_representation.md#adding-1-pattern-by-pattern), at 32 bits.

### C and C++: signed overflow is undefined

In C and C++, overflow of a **signed** integer is undefined behaviour. The standard puts no requirement on the result. The compiler may assume it never happens and optimise on that basis, so the printed `-2147483648` at `-O0` is not a guarantee. Building with `-fsanitize=undefined` makes it visible at run time:

```
runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

Overflow of an **unsigned** integer is defined: the result wraps modulo `2^n`. `UINT_MAX + 1` printed `0`. This difference is why the C and C++ solutions to Sum of Two Integers (371) do their shifting in `unsigned`.

### Rust: panic in debug, wrap in release, or choose explicitly

A debug build stops the program on overflow. A release build (`rustc -O`) wraps. Code that needs a particular behaviour in both builds calls a method that names it:

```rust
let m = i32::MAX;
m.wrapping_add(1)     // -2147483648
m.checked_add(1)      // None
m.overflowing_add(1)  // (-2147483648, true)
m.saturating_add(1)   // 2147483647   (clamped to the limit)
```

### Java and Go: always wrap

Java and Go define signed overflow as wrapping, so the result is the same in every build. Java also has `Math.addExact`, `Math.multiplyExact` and related methods, which throw `ArithmeticException: integer overflow` instead of wrapping.

Go checks **constant** expressions at compile time. Writing `int32(0xFFFFFFFF)` with a literal fails to compile with `constant 4294967295 overflows int32`. The same value held in a `uint32` variable converts without error.

### JavaScript and Python: no 32-bit overflow in arithmetic

In JavaScript, `+`, `-` and `*` work on 64-bit floats, so `2147483647 + 1` is `2147483648`. Only the bitwise operators work in 32 bits. Above `2^53` the floats lose precision and adding 1 can leave the value unchanged ([integer representation](13a_integer_representation.md#integer-types-in-each-language)).

Python integers never overflow. A problem that says "assume a 32-bit environment" has to check the limits by hand in Python, as Reverse Integer (7) does.

## Negating the smallest value

The smallest 32-bit value, `-2^31 = -2147483648`, has no positive counterpart, because the largest is `2^31 - 1` ([two's complement](13a_integer_representation.md#negation-invert-and-add-one)). Negating it overflows:

| Language | Expression | Result |
|---|---|---|
| Java | `-Integer.MIN_VALUE` | `-2147483648` |
| Java | `Math.abs(Integer.MIN_VALUE)` | `-2147483648` |
| Go | `-mn` with `mn := int32(math.MinInt32)` | `-2147483648` |
| C++ | `abs(INT_MIN)` | `-2147483648` (undefined behaviour) |
| C++ | `llabs((long long)INT_MIN)` | `2147483648` |

`abs` returning a negative number breaks any code that assumes the result is at least zero.

The fix is to **widen before negating**: move the value into a 64-bit type, where `+2^31` fits, and negate there. Pow(x, n) (50) does this. `n` can be `-2^31`, and the loop needs `|n|`:

```cpp
long long N = n;    // widen first
if (N < 0)
    N = -N;         // 2147483648 fits in 64 bits
```

The Java and C ports widen to `long` the same way. Rust uses `(n as i64).abs()`. Go needs nothing extra, because the Go solution takes `n` as `int`, which is 64 bits there.

## Checking before the operation

Wrapping or undefined behaviour can only be avoided by testing **before** the arithmetic runs. A test afterwards is too late. In C and C++ the overflow has already happened, and in Java the wrapped value can look like a normal number.

Reverse Integer (7) builds the result one digit at a time with `res = res * 10 + d`, and must return `0` if the reversed number does not fit in 32 bits. The check compares `res` with the limit divided by 10 before multiplying:

```cpp
if (res > INT_MAX / 10 || res < INT_MIN / 10)
    return 0;           // res * 10 would overflow
res = res * 10 + d;
```

`INT_MAX / 10` is `214748364`. If `res` is larger, `res * 10` is at least `2147483650`, which is past the limit.

The check does not look at the digit `d` that is about to be added. The only case it misses is `res` equal to `214748364` exactly, where `res * 10 + d` overflows only if `d` is 8 or 9. That cannot happen. `res` has nine digits at that point, so `d` is the first digit of a ten-digit input, and a ten-digit `int` starts with 1 or 2. The negative side works the same way.

A tested example: the input `1534236469` reverses to `9646324351`, which does not fit, and all seven ports return `0`.

## Mixed widths and mixed signs

### Shifting a 32-bit 1

The literal `1` is a 32-bit `int` in C, C++ and Java. Shifting it into position 31 or higher does not give the expected value:

| Language | Expression | Result |
|---|---|---|
| Java | `1 << 31` | `-2147483648` (position 31 is the sign bit) |
| Java | `1 << 32` | `1` (shift count taken mod 32; [shifts](13c_operators_and_shifts.md#shifting-by-the-full-width-or-more)) |
| Java | `1L << 40` | `1099511627776` |
| C / C++ | `1LL << 40` | `1099511627776` |

To set bit 40, the `1` has to be 64-bit before the shift: `1LL` in C and C++, `1L` in Java, `1u64` or `1i64` in Rust.

### Comparing signed with unsigned in C

When C compares an `int` with an `unsigned`, it converts the `int` to `unsigned` first. `-1` becomes `4294967295`:

```c
-1 < 1u    // 0  (false): compares 4294967295 < 1
```

The same happens in C++. gcc reports the comparison with `-Wsign-compare`, which `-Wall` turns on for C++ and `-Wextra` turns on for C. A loop like `for (int i = 0; i < v.size() - 1; i++)` hits the related problem: when `v` is empty, `v.size() - 1` is an unsigned value, so it wraps to the largest `size_t` instead of `-1`.

## Division and remainder of negative numbers

Integer division has to round when the answer is not whole. `-7 / 2` is `-3.5`, and the languages split on the direction:

| Language | `-7 / 2` | `-7 % 2` | Rounding |
|---|---|---|---|
| C, C++, Java, Go, Rust | `-3` | `-1` | toward zero |
| JavaScript | `-3.5` | `-1` | `/` is float division; `%` rounds toward zero |
| Python | `-7 // 2 = -4` | `1` | toward minus infinity |

In every language, `(a / b) * b + a % b == a`. The remainder therefore takes the sign that matches the rounding: toward zero gives a remainder with the sign of `a`, and toward minus infinity gives one with the sign of `b`.

Reverse Integer (7) depends on this. It takes the last digit with `x % 10` and drops it with `x / 10`. In C, for `x = -123`, the steps are `d = -3, x = -12`, then `d = -2, x = -1`, then `d = -1, x = 0`, and the result is `-321`. In Python, `-123 % 10` is `7` and `-123 // 10` is `-13`, so the same loop reads the wrong digits.

The Python port uses functions that round toward zero instead:

```python
d = int(math.fmod(x, 10))   # math.fmod(-7, 2) is -1.0, like C
x = int(x / 10)             # int(-3.5) is -3, like C
```

`int(x / 10)` goes through a float, which is exact here because `x` stays within 32 bits. The JavaScript port uses `Math.trunc(x / 10)` for the same reason: `Math.trunc(-3.5)` is `-3` and `Math.floor(-3.5)` is `-4`.

Rust also has `rem_euclid` and `div_euclid` when a non-negative remainder is needed: `(-7i32).rem_euclid(2)` is `1` and `(-7i32).div_euclid(2)` is `-4`.
