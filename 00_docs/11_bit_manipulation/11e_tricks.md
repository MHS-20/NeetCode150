# Bit Tricks and the Problems That Use Them

Each trick on this page is a short expression with a specific effect on the bits, followed by a step-by-step run on a small input. The problems named are the ones in `18_bit_manipulation/`, and each walkthrough follows the C++ solution there. The operators and masks used are explained in [operators](11c_operators_and_shifts.md) and [masking](11d_masking.md).

## XOR cancels pairs

XOR has four properties that, together, make it cancel any value that appears twice:

```
x ^ 0 = x                    0 changes nothing
x ^ x = 0                    a value XORed with itself is 0
x ^ y = y ^ x                order of the two inputs does not matter
(x ^ y) ^ z = x ^ (y ^ z)    grouping does not matter
```

The last two together mean that a chain of XORs gives the same result in any order. The values can be rearranged so that equal ones sit next to each other. Each equal pair becomes 0, and the zeros disappear by the first rule.

### Single Number (136)

Every value in the array appears twice except one. XORing all the values leaves the one without a partner:

```
[4, 1, 2, 1, 2]

4 ^ 1 ^ 2 ^ 1 ^ 2
= 4 ^ (1 ^ 1) ^ (2 ^ 2)      rearranged
= 4 ^ 0 ^ 0
= 4
```

The solution runs in O(n) time and O(1) space. It keeps a single running value and needs no hash set.

The same trace bit by bit, for the running value `xr`:

```
step   value   xr after
start            0 0 0
^ 4    1 0 0     1 0 0
^ 1    0 0 1     1 0 1
^ 2    0 1 0     1 1 1
^ 1    0 0 1     1 1 0      the first 1 is cancelled
^ 2    0 1 0     1 0 0      the first 2 is cancelled
```

### Missing Number (268)

The array holds `n` distinct numbers from `0..n` with one missing. If the full list `0..n` is XORed together with the array, every number that is present appears twice and cancels. Only the missing number is left.

The solution XORs the indices `0..n-1` and the values in one loop, and starts from `n` to include the last index:

```cpp
int res = nums.size();
for (int i = 0; i < nums.size(); i++)
    res ^= i ^ nums[i];
```

For `[3, 0, 1]`, with `n = 3`:

```
start    res = 3
i = 0    res = 3 ^ 0 ^ 3 = 0
i = 1    res = 0 ^ 1 ^ 0 = 1
i = 2    res = 1 ^ 2 ^ 1 = 2
```

Over the whole loop, the numbers XORed into `res` are `3, 0, 1, 2` from the indices and `n`, and `3, 0, 1` from the array. Every number except 2 appears twice, and the answer is 2.

The sum formula `n(n+1)/2 - sum(nums)` gives the same answer, but the sum can overflow in fixed-width types for large `n`. XOR results never exceed the bit width of the inputs.

## Clearing the lowest set bit: `x & (x - 1)`

The **lowest set bit** of `x` is the rightmost position holding a 1. `x & (x - 1)` turns that bit off and leaves the others.

Subtracting 1 changes only the lowest set bit and the bits below it. The lowest set bit becomes 0, and the zeros below it become 1, because the subtraction borrows from that bit. The bits above it are unchanged:

```
x          1 0 1 1 0 0
x - 1      1 0 1 0 1 1      the lowest 1 and everything to its right flipped
────────── AND ──────
           1 0 1 0 0 0      the lowest 1 is gone
```

In the AND, the bits above the lowest 1 match in `x` and `x - 1`, so they are kept. The bits from the lowest 1 downwards differ in every position, so they all become 0.

### Counting set bits: Number of 1 Bits (191)

Applying `x & (x - 1)` repeatedly removes one set bit each time. The number of steps until `x` is 0 is the number of set bits:

```cpp
int count = 0;
while (n != 0) {
    n = n & (n - 1);
    count++;
}
```

For `n = 11`:

```
n          count
1 0 1 1      0
1 0 1 0      1
1 0 0 0      2
0 0 0 0      3      the answer is 3
```

The loop runs once per set bit, not once per bit position. For `2147483645`, which has 30 set bits, it runs 30 times. A version that checks each of the 32 positions always runs 32 times.

The count of set bits is called the **popcount**. Most languages provide it directly: `__builtin_popcount` in gcc, `Integer.bitCount` in Java, `bits.OnesCount` in Go, `count_ones` in Rust and `int.bit_count` in Python 3.10 and later.

### Power-of-two test

A power of two has one set bit. Clearing it gives 0:

```
x > 0 && (x & (x - 1)) == 0
```

```
x = 16     1 0 0 0 0   →   x & (x - 1) = 0 0 0 0 0     power of two
x = 18     1 0 0 1 0   →   x & (x - 1) = 1 0 0 0 0     not a power of two
```

The test `x > 0` is required, because `0 & -1` is also 0, and 0 is not a power of two.

## Isolating the lowest set bit: `x & -x`

`x & -x` keeps the lowest set bit of `x` and clears everything else.

In two's complement, `-x` is `~x + 1` ([integer representation](11a_integer_representation.md#negation-invert-and-add-one)). Inverting `x` turns its lowest 1 into a 0 and the zeros below it into ones. Adding 1 then carries through those ones and stops at the lowest set bit, which becomes 1 again. The bits above it stay inverted.

For `x = 12`, in 8 bits:

```
x          0 0 0 0 1 1 0 0
~x         1 1 1 1 0 0 1 1
-x         1 1 1 1 0 1 0 0      ~x + 1
────────── AND ────────────
x & -x     0 0 0 0 0 1 0 0      = 4, the lowest set bit of 12
```

Above the lowest set bit, `x` and `-x` are opposite in every position, so the AND gives 0. At the lowest set bit both are 1. Below it both are 0.

A Fenwick tree (binary indexed tree) uses `x & -x` to move between the nodes it updates and reads. It is also used to visit the set bits of a number one at a time: take `x & -x`, process it, then remove it with `x & (x - 1)`.

## Counting Bits (338)

The task is to return the popcount of every number from `0` to `n`. Running the popcount loop on each number takes O(n log n). A DP reuses the count of a smaller number, which is already in the table, and adds a correction.

**Version 1, `ans[i & (i - 1)] + 1`.** `i & (i - 1)` is `i` with its lowest set bit cleared. It is smaller than `i` and has exactly one fewer set bit.

**Version 2, `ans[i >> 1] + (i & 1)`.** `i >> 1` is `i` with its last bit dropped. It is smaller than `i` and has the same set bits except the last one. `i & 1` adds that last bit back.

Both versions on `n = 5`:

```
 i   binary   i & (i-1)   ans[i & (i-1)] + 1   i >> 1   i & 1   ans[i >> 1] + (i & 1)
 0    000         -              0                -        -              0
 1    001        000         0 + 1 = 1           000       1          0 + 1 = 1
 2    010        000         0 + 1 = 1           001       0          1 + 0 = 1
 3    011        010         1 + 1 = 2           001       1          1 + 1 = 2
 4    100        000         0 + 1 = 1           010       0          1 + 0 = 1
 5    101        100         1 + 1 = 2           010       1          1 + 1 = 2
```

Both fill the table in one pass, O(n) in total, and give `[0, 1, 1, 2, 1, 2]`.

## Reverse Bits (190)

The task is to reverse the order of the 32 bits of an unsigned integer: bit 0 becomes bit 31, bit 1 becomes bit 30, and so on.

### One bit at a time

The sequential solution reads `x` from the right and builds `res` from the left:

```cpp
for (int i = 0; i < 32; i++) {
    int bit = (x >> i) & 1;     // read bit i of x
    res = (res << 1) | bit;     // make room at the bottom, then put the bit there
}
```

Each new bit enters `res` at position 0. Every later shift pushes it one position further up. The first bit read is shifted 31 more times and ends at position 31.

The same loop for 4 bits, on `x = 1101`:

```
i   bit i of x   res
0       1        0 0 0 1
1       0        0 0 1 0
2       1        0 1 0 1
3       1        1 0 1 1      1101 reversed
```

### Swapping halves

The divide-and-conquer solution swaps the two 16-bit halves, then the bytes inside each half, then the 4-bit groups, the 2-bit groups and finally single bits. It does five steps with no loop. The masks it uses and an 8-bit trace are in [masking](11d_masking.md#repeating-masks).

Both versions need **logical** shifts, because bit 31 has to move down as an ordinary bit and not as a sign ([shifts](11c_operators_and_shifts.md#right-shift-logical-and-arithmetic)). The C++ solution copies the input into a `uint32_t`. Java and JavaScript use `>>>`, and the JavaScript version ends with `>>> 0` to return an unsigned number.

## Adding without `+`: Sum of Two Integers (371)

Binary addition works one column at a time. In each column, the sum bit is the XOR of the two input bits, and a carry goes to the next column if both bits are 1:

```
a  b │ sum bit (a ^ b)   carry (a & b)
─────┼────────────────────────────────
0  0 │       0               0
0  1 │       1               0
1  0 │       1               0
1  1 │       0               1        carry goes one column left
```

For whole numbers, `a ^ b` is the sum with every carry ignored. `(a & b) << 1` holds the carries, each moved one column left to where it belongs. The true sum is `(a ^ b) + ((a & b) << 1)`. That is another addition, so the same step is repeated on its two parts. It stops when there are no carries left.

### Example: 5 + 3 in 4 bits

```
         sum              carry
start    0101 ^ 0011      (0101 & 0011) << 1
         = 0 1 1 0        = 0 0 1 0
step 1   0 1 0 0          0 1 0 0
step 2   0 0 0 0          1 0 0 0
step 3   1 0 0 0          0 0 0 0      no carry left: 8
```

Each step moves the carry at least one column to the left. With 32 bits, the loop runs at most 32 times.

### Example: -7 + 3 in 4 bits

In 4-bit two's complement, `-7` is `1001` and `3` is `0011`:

```
         sum              carry
start    1 0 1 0          0 0 1 0
step 1   1 0 0 0          0 1 0 0
step 2   1 1 0 0          0 0 0 0      no carry left: 1100 = -4
```

The same steps work for negative numbers with no special case, because two's complement addition is the same as unsigned addition on the bits.

### The fixed width is part of the algorithm

The loop ends because the carry eventually moves past the top bit and is dropped. That requires a fixed width:

- **C and C++** do the work in `unsigned`, because left-shifting a negative signed value is undefined behaviour ([overflow](11b_overflow.md#c-and-c-signed-overflow-is-undefined)).
- **Rust** casts to `u32`.
- **Go** converts to `uint32`. Its `int` is 64 bits, so the carry would otherwise run on past bit 31.
- **Java and JavaScript** keep the logic as it is. Java's `int` wraps, and JavaScript's bitwise operators work in 32 bits.
- **Python** masks the sum and carry to 32 bits on every step, then converts the result back to signed ([masking](11d_masking.md#sum-of-two-integers-without-the-mask)).

## Cost of bit operations

A bitwise operation on one 32- or 64-bit integer is one machine instruction, O(1). Costs grow in these cases:

- **A loop over every bit position** is O(w) for a width of `w` bits. It is often written as O(1) with `w` fixed at 32. Counting Bits with a plain popcount loop on each number is O(n · w).
- **A loop of `x & (x - 1)`** runs once per set bit, so it costs O(number of set bits), at most O(w).
- **Enumerating all subsets** of `n` items is O(2^n) masks, each costing O(n) if the items are listed. Fast operations on each mask do not reduce the number of masks.

Python integers are an exception. They grow without limit, so an operation on an integer with `b` bits costs O(b). For values that fit in 64 bits, this is still constant in practice.
