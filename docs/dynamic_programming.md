# Dynamic Programming

## What it actually is

Dynamic programming is recursion plus a notebook. You solve a problem by breaking it into smaller versions of itself, and you write down each answer the first time you compute it so you never compute it twice.

That is the whole trick. Everything else — memoization, tabulation, "states", "transitions" — is bookkeeping around that one idea.

A problem is a DP problem when it has both of these:

- **Overlapping subproblems** — the same smaller problem keeps reappearing. If every subproblem is distinct, caching buys nothing and you have plain divide-and-conquer (merge sort, binary search).
- **Optimal substructure** — the best answer for the whole is built from the best answers of its parts. If a locally optimal piece can never be part of a globally optimal whole, DP does not apply.

## Why it works: the Fibonacci picture

Naive recursion for `fib(5)`:

```
                fib(5)
            /            \
        fib(4)           fib(3)
       /      \          /     \
   fib(3)    fib(2)   fib(2)  fib(1)
   /    \
fib(2) fib(1)
```

`fib(3)` is computed twice, `fib(2)` three times. The tree branches twice per level and is `n` deep, so this is O(2ⁿ). But there are only **n distinct** subproblems — `fib(0)` through `fib(n)`. Caching collapses the tree into a line: O(n).

This is the general shape of every DP speedup. Exponential search space, polynomial number of *distinct* states, and the gap between the two is what the cache eliminates.

## The two styles

### Top-down (memoization)

Write the recursion the way you'd naturally state the problem, then add a cache.

```python
from functools import cache

@cache
def fib(n):
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)
```

- Easier to write — the recursion mirrors the problem statement.
- Only computes the states actually reachable from the input.
- Costs recursion stack depth, and can blow the stack on deep inputs.

### Bottom-up (tabulation)

Fill a table in an order where every value's dependencies are already filled.

```python
def fib(n):
    dp = [0] * (n + 1)
    dp[1] = 1
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]
```

- No recursion, no stack limit, less constant-factor overhead.
- Opens the door to space optimization (below).
- Requires you to figure out the correct fill order up front.

Same complexity, same answers. Write top-down first to find the recurrence, convert to bottom-up if you need the speed or the space trick.

## How to actually derive a DP

Four questions, in order. Answer them and the code writes itself.

**1. What is the state?** The smallest set of variables that fully describes a subproblem. "I'm at index `i` with `c` coins left" → state is `(i, c)`. Getting this wrong is the main failure mode: too few variables and different situations collide in the same cache slot; too many and the table explodes.

**2. What is the transition?** How a state's answer is built from smaller states. Usually a choice: *take it or skip it*, *match or advance*, *split here or there*.

**3. What are the base cases?** The states small enough to answer directly.

**4. What is the answer?** Which state — often the largest, sometimes a max over many.

House Robber, as an example:

```
state:      dp[i] = max money from houses 0..i
transition: dp[i] = max(dp[i-1],          # skip house i
                        dp[i-2] + val[i]) # rob house i, so skip i-1
base:       dp[0] = val[0], dp[1] = max(val[0], val[1])
answer:     dp[n-1]
```

## Complexity: count the states

> **total time = number of states × cost of one transition**

Because each state is computed exactly once, this is mechanical and doesn't need a recurrence-tree analysis.

| Shape | States | Per transition | Total |
|---|---|---|---|
| 1D over the input | O(n) | O(1) | O(n) |
| 1D with an inner scan | O(n) | O(n) | O(n²) |
| Two sequences | O(n·m) | O(1) | O(n·m) |
| Knapsack (index × capacity) | O(n·W) | O(1) | O(n·W) |
| Intervals (start × end) | O(n²) | O(n) split point | O(n³) |
| Bitmask over a set | O(2ⁿ·n) | O(n) | O(2ⁿ·n²) |

Space starts equal to the number of states, but often shrinks.

## Space optimization: rolling the table

If `dp[i]` only reads `dp[i-1]` and `dp[i-2]`, the rest of the array is dead weight. Keep only what you read:

```python
def rob(nums):
    prev2, prev1 = 0, 0
    for n in nums:
        prev2, prev1 = prev1, max(prev1, prev2 + n)
    return prev1
```

O(n) space → O(1). The 2D version of the same idea: if row `i` only depends on row `i-1`, keep two rows instead of `n` — O(n·m) → O(m). The cost is that you can no longer reconstruct *which* choices produced the answer, only its value. If the problem asks for the actual subsequence or path, keep the full table.

## The patterns worth recognising

**Linear / 1D.** State is one index. Climbing Stairs, House Robber, Decode Ways, Word Break. Ask: what are the ways to arrive at position `i`?

**Knapsack.** State is `(index, remaining capacity)`. The transition is always take-or-skip. Partition Equal Subset Sum and Coin Change are knapsacks in disguise — "can I hit exactly this sum" is a 0/1 knapsack, "fewest coins" is an unbounded one. The ordering of the two loops decides whether an item can be reused:

```python
for item in items:
    for cap in range(W, item - 1, -1):   # descending → each item used once (0/1)
        ...
    for cap in range(item, W + 1):       # ascending  → item reusable (unbounded)
        ...
```

**Two sequences.** State is `(i, j)`, one index per string. Longest Common Subsequence, Edit Distance, Distinct Subsequences. Transition is "do the current characters match?"

```
        ""  a   b   c        LCS of "abc" / "ac"
    ""   0   0   0   0
    a    0   1   1   1       match → dp[i-1][j-1] + 1
    c    0   1   1   2       no match → max(dp[i-1][j], dp[i][j-1])
```

**Intervals.** State is a range `(i, j)`, and the transition tries every split point inside it. Burst Balloons, Matrix Chain Multiplication. Fill by increasing range length, not by index.

**Grid.** State is a cell `(r, c)`, dependencies are the neighbours already visited. Unique Paths, Minimum Path Sum.

**Bitmask.** State packs a subset of ≤ ~20 items into an integer. Travelling Salesman and assignment problems.

## Common failure modes

- **Incomplete state.** If two genuinely different situations map to the same cache key, the cache returns a wrong answer — and it does so silently. When a memoized solution is wrong but the recursion looks right, the state is missing a variable.
- **Caching on mutable state.** A list or a set cannot be a dict key, and freezing one into a tuple usually means the state is too large for DP anyway.
- **Greedy where DP is needed.** Coin Change with coins `[1, 3, 4]` and target 6: greedy takes 4+1+1 = 3 coins, the optimum is 3+3 = 2. Greedy is only correct when a local choice is provably never regretted.
- **Wrong fill order.** Bottom-up reading a cell that hasn't been written yet — usually reads a zero and produces a plausible-looking wrong number. Check that every dependency of `dp[i]` is computed before `dp[i]`.
- **DP where the input doesn't bound it.** O(n·W) knapsack is *pseudo*-polynomial: it's polynomial in the capacity's *value*, not in its number of bits. A capacity of 10⁹ makes the table impossible regardless of how few items there are.

## Quick recognition checklist

Reach for DP when the problem asks for a **count of ways**, a **min/max over choices**, or a **yes/no reachability**, *and* the choices at each step are constrained by earlier choices. If it asks for the *actual* optimal arrangement rather than its value, it's still DP — you just keep the full table and walk it backwards afterwards.
