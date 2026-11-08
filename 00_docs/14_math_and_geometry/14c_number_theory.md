# Number Theory: GCD, LCM, Modular Arithmetic and Primes

Problems that reduce fractions, line up repeating cycles, return a count "modulo 10⁹ + 7", or test for primes all rely on a few results about integers. Each section below gives the rule, the reason it holds, and a worked example that was computed by running it.

## Greatest common divisor

The **greatest common divisor** `gcd(a, b)` is the largest integer that divides both `a` and `b`. `gcd(12, 18) = 6`.

### Euclid's algorithm

```
gcd(a, b) = gcd(b, a % b)
gcd(a, 0) = a
```

**Why it holds.** Any number that divides both `a` and `b` also divides `a - q·b` for any integer `q`, and `a % b` is `a - q·b` for `q = a / b`. In the other direction, any number that divides both `b` and `a % b` also divides `a = q·b + a % b`. So the pairs `(a, b)` and `(b, a % b)` have exactly the same common divisors, and the same greatest one.

For `gcd(1071, 462)`:

```
a      b      a % b
1071   462    147
462    147     21
147     21      0      → gcd = 21
```

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

The remainder at least halves every two steps, so the loop runs O(log min(a, b)) times. C++17 has `std::gcd` in `<numeric>`, Python has `math.gcd`.

`gcd(a, 0) = a`, because every number divides 0. So `gcd(0, 7) = 7`. Most libraries return a non-negative result for negative inputs: Python's `math.gcd(12, -18)` is 6.

## Least common multiple

The **least common multiple** `lcm(a, b)` is the smallest positive integer that both `a` and `b` divide. `lcm(12, 18) = 36`.

```
gcd(a, b) · lcm(a, b) = a · b
lcm(a, b) = a / gcd(a, b) * b
```

For 12 and 18: `6 · 36 = 216 = 12 · 18`.

**Divide first.** `a * b / gcd(a, b)` gives the same value, but `a * b` can overflow when the LCM itself fits. Dividing `a` by the GCD first keeps the intermediate value no larger than the result.

LCM answers "when do two cycles line up". Two events repeating every 12 and every 18 days both happen on the same day every 36 days. For more than two numbers, `lcm(a, b, c) = lcm(lcm(a, b), c)`, and the same holds for GCD.

### Reducing a fraction

Dividing the numerator and denominator by their GCD gives the reduced form: `18/12` becomes `3/2`. A reduced fraction with a fixed sign rule (for example, the denominator always positive) is a safe hash key for a slope, where a floating-point `dy / dx` would not be ([math and geometry](14a_math_and_geometry.md#geometry-basics)).

## Modular arithmetic

When an answer can be astronomically large, problems ask for it modulo a prime, usually `m = 10⁹ + 7`. The modulus is applied after **every** operation, because the intermediate value is the one that overflows.

### The rules

```
(a + b) mod m = ((a mod m) + (b mod m)) mod m
(a · b) mod m = ((a mod m) · (b mod m)) mod m
(a - b) mod m = ((a mod m) - (b mod m) + m) mod m
```

**Multiplication needs 64 bits.** Two values below `10⁹ + 7` can multiply to about `10¹⁸`, which needs a 64-bit integer, `long long` in C++. The result is then reduced below `m` again.

**Subtraction needs `+ m`.** `(5 - 8) mod m` should be `m - 3`. In C, C++ and Java, `%` of a negative number is negative: `(5 - 8) % m` is `-3`. Adding `m` before the final `%` makes it positive. Python's `%` already returns `1000000004` for `(5 - 8) % (10**9 + 7)`, but writing `+ m` costs nothing and works in every language.

### Division: the modular inverse

Division does not follow the same rule. `(a / b) mod m` is not `(a mod m) / (b mod m)`. Instead, `a` is multiplied by the **modular inverse** of `b`: the number `b⁻¹` with `b · b⁻¹ mod m = 1`.

When `m` is prime and `b` is not a multiple of `m`, **Fermat's little theorem** gives the inverse directly:

```
b⁻¹ = b^(m-2) mod m
```

For `m = 10⁹ + 7` and `b = 4`, `4^(m-2) mod m = 250000002`, and `4 · 250000002 mod m = 1`. So `12 / 4 mod m` is `12 · 250000002 mod m = 3`.

This is how `C(n, k) mod m` is computed: `n! · (k!)⁻¹ · ((n-k)!)⁻¹`, with factorials and their inverses precomputed.

### Fast exponentiation

`b^(m-2)` with `m - 2` near 10⁹ cannot be computed by multiplying a billion times. **Exponentiation by squaring** does it in O(log n) steps. Write the exponent in binary. Square the base at each step, and multiply it into the result where the exponent's bit is 1:

```cpp
long long power(long long x, long long n, long long m) {
    long long result = 1;
    x %= m;
    while (n > 0) {
        if (n & 1)
            result = result * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return result;
}
```

For `3^13`, with `13 = 1101` in binary:

```
bit of n   x before squaring   result
   1              3              3          (13 is odd)
   0              9              3
   1             81            243          (3 · 81)
   1           6561        1594323          (243 · 6561)
```

`3^13 = 3¹ · 3⁴ · 3⁸ = 1594323`. Python's `pow(x, n, m)` does the same. Pow(x, n) (50) in `17_math_geometry/` is this loop without the modulus.

## Primes

### Testing one number

`n` is prime if no number from 2 to `√n` divides it. If `n = a · b` with `a <= b`, then `a · a <= a · b = n`, so `a <= √n`. A factor above `√n` always comes with one below it, which was already tested.

The loop condition `i * i <= n` avoids computing a square root. 0 and 1 are not prime, and a loop starting at 2 does not run for them, so they need their own check.

### All divisors

The same pairing lists all divisors of `n` in O(√n): for each `i <= √n` that divides `n`, both `i` and `n / i` are divisors. For `n = 36` this gives `1, 2, 3, 4, 6, 9, 12, 18, 36`. When `i · i = n`, as with `6 · 6`, the divisor is added once.

### The sieve of Eratosthenes

To find every prime up to `n`, cross out the multiples of each prime. Crossing out for prime `p` starts at `p · p`, because every smaller multiple of `p` has a smaller prime factor and was crossed out already. The outer loop can stop at `√n` for the same reason.

For `n = 30`:

```
p = 2   crosses out 4 6 8 10 12 14 16 18 20 22 24 26 28 30
p = 3   crosses out 9 12 15 18 21 24 27 30          (starting at 9)
p = 5   crosses out 25 30                           (starting at 25)
p = 6   6 · 6 = 36 > 30: stop

primes: 2 3 5 7 11 13 17 19 23 29
```

The sieve takes O(n log log n) time and O(n) memory.

## Common mistakes

- **Multiplying two values below 10⁹ + 7 in 32 bits.** The product needs 64 bits.
- **Forgetting `+ m` after a subtraction** in C, C++, Java or Go. The result can be negative.
- **Dividing under a modulus.** Multiply by the modular inverse instead.
- **Computing `a * b / gcd(a, b)`** when `a / gcd(a, b) * b` fits and the product does not.
- **Treating 0 and 1 as prime**, or a loop up to `√n` that never runs for small `n`.
