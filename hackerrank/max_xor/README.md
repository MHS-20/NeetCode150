# Max XOR

Given `n` divisible by 4, find the smallest `x >= n` with the same number of binary digits as `n` that maximises `n ^ (n+1) ^ ... ^ x`.

Example: `n = 4`. The candidates are 4 to 7, and the XORs are 4, 1, 7, 0, so the answer is 6.

Solution idea: the XOR of `0..k` repeats with period 4 (`k`, `1`, `k+1`, `0` for `k % 4` = 0, 1, 2, 3). Since `n % 4 == 0`, the XOR of `0..n-1` is 0, so the value equals the XOR of `0..x`. With `b` bits the largest possible value is `2^b - 1`, first reached at `x = 2^b - 2`. O(log n).

Closest LeetCode problem: 1486, XOR Operation in an Array. Its O(1) solution uses the same period-4 formula.
