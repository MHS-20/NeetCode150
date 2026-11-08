# 1D vs 2D Dynamic Programming

A companion to [`8a_dynamic_programming.md`](8a_dynamic_programming.md), which covers memoization, tabulation, and complexity. This file answers one question: **how many dimensions does the table need, and how do you shrink it afterwards?**

## The rule

> **One dimension per independent variable needed to describe a subproblem.**

Write down what you must know to answer a subproblem in isolation, ignoring how you got there. Each separate quantity in that description is one axis of the table.

- "The best answer using houses `0..i`" — one variable, `i`. **1D.**
- "The best answer using the first `i` items with capacity `c` remaining" — two variables, and neither is derivable from the other. **2D.**
- "The LCS of `s1[0..i]` and `s2[0..j]`" — two independent indices. **2D.**
- "Can `s[i..j]` be split into valid pieces" — a range, so two endpoints. **2D.**

The test for independence: if fixing one variable still leaves the other free to vary, they are separate dimensions. In the knapsack, index 3 can pair with any remaining capacity from 0 to W, so capacity is a real second axis. In House Robber, there is nothing else to know once `i` is fixed.

## Where the extra dimension comes from

Almost always one of these four.

**A second sequence.** Two strings or arrays being compared position by position. `dp[i][j]` = answer for the first `i` of one and the first `j` of the other. Edit Distance, LCS, Interleaving String, Distinct Subsequences.

```
        ""  a   b   c         LCS("abc", "ac")
    ""   0   0   0   0
    a    0   1   1   1        chars match    → dp[i-1][j-1] + 1
    c    0   1   1   2        no match       → max(dp[i-1][j], dp[i][j-1])
```

**A resource budget.** A number you spend down as you go: capacity, a target sum, a coin total, a number of transactions, `k` remaining moves. `dp[i][c]` = answer at index `i` with `c` of the budget left. Every knapsack variant, Coin Change, Partition Equal Subset Sum, Target Sum.

**A mode or small extra state.** Not a full axis so much as a handful of parallel 1D arrays. Best Time to Buy and Sell Stock with cooldown: `dp[i][holding]` where `holding` is 0 or 1. Paint House: `dp[i][colour]`. The second dimension is bounded by a small constant, so this is O(n·k) and often written as two or three separate 1D arrays.

**A grid, or a range.** The input is genuinely two-dimensional (Unique Paths, Minimum Path Sum), or a subproblem is an interval `(i, j)` rather than a prefix (Palindromic Substrings, Burst Balloons, Longest Palindromic Subsequence).

## Two shapes that look 1D but aren't, and one that looks 2D but isn't

**Looks 1D, is 2D.** Coin Change written as `dp[amount]` works, and this is the genuine 1D form for the *unbounded* case where every coin stays available. But 0/1 knapsack — each item usable once — cannot be expressed as `dp[capacity]` alone without the loop-direction trick below, because "which items are still available" is real state. Hidden budgets are the usual reason a 1D attempt produces almost-right answers.

**Looks 1D, is 2D.** Longest Increasing Subsequence is `dp[i]` = length of the LIS *ending at* `i`, but computing it scans all `j < i`, so the time is O(n²) with 1D space. The dimension count and the time complexity are separate questions; a 1D table with an inner loop is O(n²) time and O(n) space.

**Looks 2D, is 1D.** A grid walk that only ever moves right and down depends on the row above and the cell to the left, so one row of memory suffices. The *problem* is 2D; the *table* need not be.

## Collapsing 2D to 1D

The mechanical transformation, and the reason knapsack loop directions are what they are.

If `dp[i][...]` only reads `dp[i-1][...]`, row `i-1` is the only history that matters. Keep one row and overwrite it in place.

```python
# 2D: O(n·W) space
for i in range(1, n + 1):
    for c in range(W + 1):
        dp[i][c] = dp[i-1][c]
        if c >= w[i-1]:
            dp[i][c] = max(dp[i][c], dp[i-1][c - w[i-1]] + v[i-1])

# 1D: O(W) space — same recurrence, one row
for i in range(n):
    for c in range(W, w[i] - 1, -1):        # descending
        dp[c] = max(dp[c], dp[c - w[i]] + v[i])
```

**The loop must run descending, and this is the whole subtlety.** When `dp[c]` is being computed, `dp[c - w[i]]` must still hold the *previous* row's value — the state before item `i` was considered. Going descending, the lower indices have not been touched yet this iteration, so they are still row `i-1`. Going ascending, `dp[c - w[i]]` was already updated with item `i`, so the item gets used twice.

That accident is exactly the unbounded knapsack, which is why the direction is the switch between the two variants:

```
descending c  →  each item used at most once   (0/1 knapsack)
ascending  c  →  each item reusable            (unbounded knapsack, Coin Change)
```

For two-sequence DP, the same collapse applies but `dp[j-1]` is needed from *both* rows, so one scalar must be stashed before it is overwritten:

```python
for i in range(1, n + 1):
    prev_diag = dp[0]
    for j in range(1, m + 1):
        temp = dp[j]                 # this is dp[i-1][j], needed next iteration
        dp[j] = prev_diag + 1 if a[i-1] == b[j-1] else max(dp[j], dp[j-1])
        prev_diag = temp
```

When only two rows are needed and the index juggling gets error-prone, keeping `prev` and `cur` as two full arrays and swapping them is the safer O(m) version. Write the 2D form first, confirm it passes, then collapse — the reverse order produces bugs that are hard to localise.

## What you lose

Collapsing keeps the optimal *value* and destroys the optimal *choices*. Reconstructing which items were taken, or the actual longest common subsequence, requires walking the full table backwards from the answer cell. If the problem asks for the subsequence rather than its length, or the path rather than its cost, keep all O(n·m) cells and skip the optimization.

## Quick diagnostic

| Description of a subproblem | Table | Collapsible to |
|---|---|---|
| prefix of one array | `dp[i]` | O(1), keep 2–3 scalars |
| prefix of one array + a budget | `dp[i][c]` | O(W), one row, mind the direction |
| prefixes of two sequences | `dp[i][j]` | O(m), stash the diagonal |
| a cell in a grid | `dp[r][c]` | O(C), one row |
| an interval `(i, j)` | `dp[i][j]` | **not collapsible** — fill by length |
| prefix + a small mode | `dp[i][k]` | a few scalars per mode |

Interval DP is the exception: `dp[i][j]` depends on shorter ranges scattered across the table rather than on a single adjacent row, so there is no row to discard.
