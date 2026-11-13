# Interval DP: Answers for Every Range `[i, j]`

Interval DP solves problems about **one** sequence where the answer for a range `i..j` is built from the answers for shorter ranges inside it. The table is `dp[i][j]` for every pair `i ≤ j`, the answer for the whole input is `dp[0][n-1]`, and cells are filled from the shortest ranges up to the longest.

It differs from [string DP](12d_string_dp.md) in what the two indices mean. In string DP, `i` and `j` are prefix lengths of two *different* strings. Here they are the two ends of a range in the *same* sequence, so only the upper triangle `i ≤ j` is used.

Examples below, by LeetCode number. The first three have solutions in this repo:

| Problem | Range state | Transition |
|---|---|---|
| Longest Palindromic Substring (5) | is `s[i..j]` a palindrome | shrink both ends |
| Palindromic Substrings (647) | is `s[i..j]` a palindrome | shrink both ends |
| Burst Balloons (312) | best coins inside `(l, r)` | split at `k` |
| Longest Palindromic Subsequence (516) | longest palindrome in `s[i..j]` | shrink one or both ends |
| Stone Game (877) | score lead on `piles[i..j]` | shrink one end |
| Minimum Cost to Cut a Stick (1547) | cheapest way to cut between two cuts | split at `k` |

## Fill order

`dp[i][j]` only reads ranges strictly inside `[i, j]`, which are shorter. Filling the table one length at a time, from length 1 up to `n`, guarantees that every cell it reads is already computed:

```python
for length in range(1, n + 1):
    for i in range(n - length + 1):
        j = i + length - 1
        dp[i][j] = ...        # reads only shorter ranges
```

```
           j=0  j=1  j=2  j=3  j=4         each cell shows its range length j-i+1
    i=0     1    2    3    4    5
    i=1     .    1    2   [3]->(4)         (4) = dp[1][4], reads:
    i=2     .    .    1   [2]  [3]           dp[1][3]  (left)
    i=3     .    .    .    1    2            dp[2][4]  (below)
    i=4     .    .    .    .    1            dp[2][3]  (below-left)
                                           all on shorter diagonals
    . = unused (j < i)
```

The loop above fills one diagonal per pass: the main diagonal (length 1) first, the top-right corner (the whole input) last. In a shrink-the-ends problem, `dp[1][4]` (in parentheses) reads the three bracketed cells, all on earlier diagonals.

A second order also works: `i` from `n-1` down to 0, and `j` from `i` up to `n-1`. Every range inside `[i, j]` either starts later (a larger `i`, so its row was finished in an earlier pass) or starts at `i` and ends earlier (a smaller `j`, earlier in the same row). Row-by-row from the top fails: `dp[0][4]` would read `dp[1][3]` before row 1 exists, and get 0.

Writing the recurrence top-down with memoization avoids choosing an order. The recursion computes each inner range on demand.

## Shape 1: shrink the ends

The range `[i, j]` is reduced by removing `s[i]`, `s[j]`, or both. Each cell reads at most three neighbours, so the work per cell is O(1) and the whole table is O(n²).

### Longest Palindromic Substring (5) and Palindromic Substrings (647)

```python
dp[i][j] = s[i] == s[j] and (j - i < 2 or dp[i+1][j-1])
```

`s[i..j]` is a palindrome when its two end characters match and the part between them, `s[i+1..j-1]`, is a palindrome. Ranges of length 1 and 2 have an empty or single-character inside, so they only need the end check, which is what `j - i < 2` covers. Problem 5 keeps the longest `true` range; 647 counts all of them. `5_solution1_tab.cpp` fills this table bottom-up from the last row, and `647_solution1.cpp` fills it by length; both are in `13_dp_1D/`. `5_solution2_memo.cpp` computes the same table top-down with memoized recursion.

Both problems also have an O(1)-space solution that expands outward from each of the `2n - 1` centres, as in `5_solution3_no_dp.cpp`. It runs in the same O(n²) time.

### Longest Palindromic Subsequence (516)

A subsequence may skip characters, so a mismatch at the ends does not end the search:

```python
dp[i][i] = 1
if s[i] == s[j]: dp[i][j] = dp[i+1][j-1] + 2          # both ends join the palindrome
else:            dp[i][j] = max(dp[i+1][j], dp[i][j-1])  # drop one end
```

For `s = "bbbab"` the table is (rows `i`, columns `j`, answer 4, "bbbb"):

```
         b  b  b  a  b
    b    1  2  3  3  4      s[0]=b == s[4]=b: dp[1][3] + 2 = 2 + 2
    b       1  2  2  3
    b          1  1  3
    a             1  1
    b                1
```

`dp[i+1][j-1]` for a length-2 range is `dp[i+1][i]`, a cell below the diagonal. Python's table initialises it to 0, which is the right value for an empty range, so `"bb"` gives `0 + 2 = 2` with no special case.

### Stone Game (877)

Two players take turns removing a pile from either end of the row; each plays optimally. Store the **score lead** of whoever is about to move:

```python
dp[i][i] = piles[i]
dp[i][j] = max(piles[i] - dp[i+1][j],   # take the left pile; opponent then leads by dp[i+1][j]
               piles[j] - dp[i][j-1])   # take the right pile
```

After the current player takes a pile, the opponent faces the shorter range and is now the one moving, so the opponent's best lead is subtracted. Storing one lead instead of two separate scores keeps the state at `(i, j)`. For `[5, 3, 4, 5]` the lead at `dp[0][3]` is 1, so the first player wins. The same recurrence solves the general version where a tie or a loss is possible (Predict the Winner, 486).

## Shape 2: try every split point

The range is divided at some `k` inside it, and the answer combines the two sides plus a cost for the split itself:

```python
dp[i][j] = best over k in (i, j) of: dp[i][k] + dp[k][j] + cost(i, k, j)
```

Each cell loops over up to `n` values of `k`, so the work is O(n) per cell and O(n³) overall. That limits inputs to a few hundred elements; Burst Balloons allows `n ≤ 300`.

### Burst Balloons (312)

Bursting balloon `k` earns `left * nums[k] * right`, where `left` and `right` are its current neighbours.

```
   index    0      1      2      3      4      5
   a      [ 1 ]    3      1     (5)     8    [ 1 ]
            l                    k             r
                 \___________/          \/
                   dp[l][k]          dp[k][r]
                 burst first       burst first
                                       then k last: a[l] * a[k] * a[r]
   [ ] = walls, never burst     ( ) = last balloon in (l, r)
```

The array is padded with a 1 at each end, `a = [1, nums..., 1]`, and `dp[l][r]` is the best score for bursting every balloon **strictly between** `l` and `r`. The diagram shows `a = [1, 3, 1, 5, 8, 1]` with `l = 0`, `r = 5` and `k = 3`. The two end balloons act as walls and are never burst.

The split chooses `k` as the **last** balloon burst in `(l, r)`:

```python
for k in range(l + 1, r):
    dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[k] * a[r])
```

1. Everything in `(l, k)` is burst first, while `k` is still standing, so `k` is the right wall of that range. That is `dp[l][k]`.
2. The same holds for `(k, r)`, with `k` as the left wall: `dp[k][r]`.
3. Then `k` is burst. Its neighbours at that moment are `a[l]` and `a[r]`, because everything between them is gone.

Choosing `k` as the **first** balloon instead does not split the problem. In `[3, 1, 5]`, bursting the 1 first makes 3 and 5 adjacent, so the score of the left part depends on what is left in the right part, and `dp[l][k]` and `dp[k][r]` stop being independent.

For `[3, 1, 5, 8]` the table over the padded array is (answer 167):

```
         1   3   1   5   8   1
    1    0   0   3  30 159 167
    3        0   0  15 135 159
    1            0   0  40  48
    5                0   0  40
    8                    0   0
    1                        0
```

Ranges of length 0 or 1 (`r - l < 2`) contain no balloon and stay 0, so the length loop starts at 2.

### Minimum Cost to Cut a Stick (1547)

A stick of length `n` must be cut at every position in `cuts`; each cut costs the length of the piece being cut. The order of the cuts changes the total.

Sort `cuts` and add both ends: `c = [0, sorted cuts..., n]`. `dp[l][r]` is the cheapest way to make every cut strictly between `c[l]` and `c[r]`. Choosing `k` as the **first** cut in that piece works here, because a cut splits the stick into two pieces that are handled separately:

```python
dp[l][r] = min(dp[l][k] + dp[k][r] for k in range(l + 1, r)) + (c[r] - c[l])
```

The cost of the first cut is the whole piece, `c[r] - c[l]`, whichever `k` is chosen. For `n = 7`, `cuts = [1, 3, 4, 5]`, `c = [0, 1, 3, 4, 5, 7]` and `dp[0][5] = 16`.

Compared with Burst Balloons, the split is the **first** event instead of the last. In both cases `k` is chosen so that the two sides do not affect each other: a cut separates the stick immediately, while a balloon only separates its neighbours once it is the last one left in the range.

## Open and closed ranges

Two conventions appear above, and mixing them causes off-by-one errors:

- **Closed `[i, j]`**: both ends are part of the range. Problems 5, 647, 516, 877. The base case is length 1, `dp[i][i]`.
- **Open `(l, r)`**: the ends are walls, and only the elements strictly between them count. Problems 312, 1547, and Matrix Chain Multiplication. The base case is `r - l < 2`, an empty inside, and the input is padded so that the whole problem is `(0, N-1)`.

Split problems use open ranges because `k` belongs to both sides: it is the right wall of `(l, k)` and the left wall of `(k, r)`. With closed ranges, `k` would have to be excluded from both `[l, k-1]` and `[k+1, r]`, which works but needs extra bounds checks for empty sides.

## Space

Shrink-the-ends problems read only row `i` and row `i+1`. With the `i`-descending order, two rows of length `n` are enough, O(n) space. Split problems read the whole row `l` and the whole column `r` up to the split point, so the full O(n²) table is needed.

## Recognising interval DP

- The input is **one** sequence, and the problem removes, merges, cuts or matches elements from its **ends** or splits it at some point.
- Doing one operation changes what is adjacent to what (bursting a balloon, merging two stones, cutting a stick), so the order of operations matters.
- A greedy choice fails on small examples, and brute force over all orders is O(n!).
- The constraints allow O(n²) or O(n³): `n` up to a few thousand for shrink-the-ends, a few hundred for split points.

To write the recurrence, answer three questions:

1. **Open or closed ranges?** Closed if the ends are part of the answer (palindromes, picking from ends). Open if they are boundaries that stay in place (walls, stick ends, matrix dimensions).
2. **Shrink or split?** Shrink if each step removes an end element. Split if each step divides the range in two at some inner point `k`.
3. **First or last?** For a split, choose the event that makes the two sides independent: the first cut, or the last balloon.

## Pitfalls

- **Filling by row from the top.** `dp[0][j]` needs rows below it. Fill by length, or with `i` descending.
- **Choosing the first balloon in Burst Balloons.** The sub-ranges then share neighbours and the recurrence gives wrong scores. Choose the last balloon.
- **Forgetting to pad or sort.** Burst Balloons needs the 1s at both ends for the boundary multipliers. Minimum Cost to Cut a Stick needs `cuts` sorted and `0` and `n` added, or the piece lengths `c[r] - c[l]` are wrong.
- **Mixing open and closed ranges** in one solution. Decide whether the ends are included before writing the base case.
- **Reading `dp[i+1][j-1]` on a length-2 range.** That is the empty range below the diagonal. It must hold the value for an empty range (0, or `true` for palindromes), or be guarded with `j - i < 2`.
