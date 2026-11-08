# Knapsack: 0/1, Unbounded, and Their Disguises

## What it solves

There are `n` items. Item `i` has a **weight** `w[i]` and a **value** `v[i]`. A knapsack holds at most `W` total weight. Choose items to maximise the total value without going over `W`.

The variants differ in how many times each item can be used:

| Variant | Each item | Typical problems |
|---|---|---|
| **0/1** | at most once | Partition Equal Subset Sum (416), Target Sum (494), Last Stone Weight II (1049) |
| **Unbounded** | any number of times | Coin Change (322), Coin Change II (518), Perfect Squares (279) |
| **Bounded** | at most `k[i]` times | reduces to 0/1 (see below) |
| **Fractional** | any fraction | greedy by value/weight, no DP ([`8b_greedy.md`](../08_techniques/8b_greedy.md)) |

Greedy fails for 0/1: taking the best value-per-weight item first can block a better combination ([`8b_greedy.md`](../08_techniques/8b_greedy.md) has a counterexample). Trying every subset is O(2ⁿ). The DP below runs in O(n · W).

## The 0/1 recurrence

Let `dp[i][c]` be the best value using only the first `i` items with capacity `c`. For item `i`, there are two choices:

- **skip it:** `dp[i-1][c]`
- **take it**, if it fits: `dp[i-1][c - w[i]] + v[i]`. The capacity left drops by its weight, and only the earlier items remain available.

```
dp[i][c] = max(dp[i-1][c],  dp[i-1][c - w[i]] + v[i])    if w[i] ≤ c
dp[i][c] = dp[i-1][c]                                    otherwise
dp[0][c] = 0
```

Items `(w, v)`: `(1, 1)`, `(3, 4)`, `(4, 5)`, and `W = 6`:

```
           c:  0  1  2  3  4  5  6
no items       0  0  0  0  0  0  0
+ (1,1)        0  1  1  1  1  1  1
+ (3,4)        0  1  1  4  5  5  5     c=4: take → dp[1][1] + 4 = 5
+ (4,5)        0  1  1  4  5  6  6     c=5: take → dp[2][1] + 5 = 6

answer dp[3][6] = 6     items (1,1) + (4,5)
```

`(3,4) + (4,5)` would be worth 9, but its weight 7 does not fit.

### One row is enough

Row `i` only reads row `i-1`, so a single array of size `W + 1` can be overwritten in place. The capacity loop must run **descending**, so that `dp[c - w]` still holds the previous row's value when `dp[c]` reads it ([`10b_dp_1d_vs_2d.md`](10b_dp_1d_vs_2d.md) walks through why).

```cpp
int knapsack01(vector<int> &w, vector<int> &v, int W) {
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < w.size(); i++)
    for (int c = W; c >= w[i]; c--)          // descending: each item once
      dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
  return dp[W];
}
```

O(n · W) time, O(W) space.

## The unbounded recurrence

If an item can be reused, taking it leaves it available. The "take" branch reads the **same row**:

```
dp[i][c] = max(dp[i-1][c],  dp[i][c - w[i]] + v[i])
                                 ↑ same row: item i still available
```

In one array, that means looping capacity **ascending**. Then `dp[c - w]` has already been updated with item `i`, which is exactly "item `i` may already be in there".

```cpp
int knapsackUnbounded(vector<int> &w, vector<int> &v, int W) {
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < w.size(); i++)
    for (int c = w[i]; c <= W; c++)          // ascending: item reusable
      dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
  return dp[W];
}
```

Same items, `W = 6`, unbounded:

```
c:   0  1  2  3  4  5  6
     0  1  2  4  5  6  8      c=6: (3,4) twice = 8
```

The two variants differ in a single loop direction, and the wrong direction silently computes the other one.

## What the table stores

The take-or-skip structure stays the same. What changes is the question, and with it the combining operation and the base case:

| Question | `dp[c]` means | Combine | Base case | Example |
|---|---|---|---|---|
| Max value, weight **≤ W** | best value with capacity `c` | `max` | all `0` | classic knapsack |
| Max value, weight **exactly W** | best value at exactly weight `c` | `max` | `dp[0] = 0`, others `-∞` | |
| Can we hit sum `c`? | reachable or not | `\|\|` | `dp[0] = true` | Partition Equal Subset Sum (416) |
| How many ways to hit `c`? | number of ways | `+` | `dp[0] = 1` | Coin Change II (518), Target Sum (494) |
| Fewest items to hit `c`? | min count | `min(dp[c], dp[c-w] + 1)` | `dp[0] = 0`, others `∞` | Coin Change (322), Perfect Squares (279) |

The base case encodes the question. An all-zero start means "unused capacity is fine", because every `dp[c]` starts out achievable with no items. `-∞` everywhere except `dp[0]` means "only sums actually built from items count". Using the wrong one is the usual reason a knapsack returns a plausible but wrong number.

### Coin Change (322): fewest coins, unbounded

```cpp
int coinChange(vector<int> &coins, int amount) {
  const int INF = amount + 1;                // more coins than could ever be needed
  vector<int> dp(amount + 1, INF);
  dp[0] = 0;
  for (int coin : coins)
    for (int c = coin; c <= amount; c++)     // ascending: coins reusable
      dp[c] = min(dp[c], dp[c - coin] + 1);
  return dp[amount] == INF ? -1 : dp[amount];
}
```

`amount + 1` works as infinity because no answer uses more than `amount` coins, since the smallest coin is 1. That also avoids the overflow of `INT_MAX + 1`.

## Combinations versus permutations

Counting problems hide a second switch: **which loop is on the outside**.

```cpp
// items outer → combinations: {1,2} and {2,1} counted once     Coin Change II (518)
for (int coin : coins)
  for (int c = coin; c <= amount; c++)
    dp[c] += dp[c - coin];

// capacity outer → permutations: 1+2 and 2+1 counted apart     Combination Sum IV (377)
for (int c = 1; c <= amount; c++)
  for (int coin : coins)
    if (coin <= c) dp[c] += dp[c - coin];
```

With coins `[1, 2]` and amount 3:

```
items outer:     {1,1,1} {1,2}               → 2
capacity outer:  1+1+1  1+2  2+1             → 3
```

With items on the outside, every combination is built in the order the items are listed: all the 1s first, then all the 2s. So each set of coins is counted once. With capacity on the outside, any item can be the last one added to any sum, so every ordering is a separate path.

For `max` and `min` questions, the loop order does not change the answer, because order never changes a total. It only matters when counting.

## Recognising a disguised knapsack

Most knapsack problems never mention weights or a bag. The signal is **a set of numbers, each either used or not, aiming at a target sum or a limit**.

**Partition Equal Subset Sum (416).** Can the array be split into two halves with equal sums? If the total is odd, no. Otherwise, the question is whether some subset sums to `total / 2`, which is 0/1 feasibility with capacity `total / 2`.

```cpp
bool canPartition(vector<int> &nums) {
  int total = accumulate(nums.begin(), nums.end(), 0);
  if (total % 2) return false;
  int target = total / 2;
  vector<bool> dp(target + 1, false);
  dp[0] = true;
  for (int x : nums)
    for (int c = target; c >= x; c--)       // descending: each number once
      dp[c] = dp[c] || dp[c - x];
  return dp[target];
}
```

**Target Sum (494).** Put `+` or `-` in front of every number to reach `target`. Call the sum of the plus numbers `P` and the sum of the minus numbers `N`. Then:

```
P - N = target
P + N = total
  → P = (total + target) / 2
```

So the question is how many subsets sum to `P`, which is a 0/1 count. If `total + target` is odd, or `|target| > total`, the answer is 0. Without that check, the division rounds or the index goes negative.

**Last Stone Weight II (1049).** Smashing stones together is equivalent to splitting them into two piles and taking the difference. Find the reachable subset sum closest to `total / 2` with 0/1 feasibility. The answer is `total - 2 · best`.

**Ones and Zeroes (474).** Each string costs some zeros and some ones, and there are two separate budgets. This is a 0/1 knapsack with two capacity dimensions, `dp[zeros][ones]`, and both loops run descending.

**Perfect Squares (279).** The items are 1, 4, 9, 16, ..., each usable any number of times. Find the fewest items that sum to `n`. That is an unbounded min-count, the same code as Coin Change.

## Bounded knapsack

If item `i` can be used up to `k[i]` times, replace it with copies of sizes 1, 2, 4, ..., plus a remainder. For example, 13 copies become pieces of 1, 2, 4 and 6. Every count from 0 to 13 is a sum of some subset of those pieces. Run 0/1 on the pieces. Each item turns into `O(log k)` pieces instead of `k`, for O(W · Σ log k[i]) in total.

## Reconstructing the chosen items

The 1D array keeps only the best value. To recover *which* items were taken, keep the full 2D table and walk back from `dp[n][W]`. If `dp[i][c] != dp[i-1][c]`, item `i` was taken, so record it and set `c -= w[i]`. Either way, move to `i - 1`. In the example above, `dp[3][6] = 6 ≠ dp[2][6] = 5` gives item `(4,5)`, then `c = 2`, and `dp[1][2] = 1 ≠ dp[0][2] = 0` gives item `(1,1)`.

## Complexity, and when W is too large

O(n · W) is **pseudo-polynomial**. It grows with the *value* of `W`, not with the number of digits needed to write it ([`1c_p_np_nphard_npcomplete.md`](../01_foundations/1c_p_np_nphard_npcomplete.md)). A capacity of 10⁹ makes the table impossible to allocate, whatever `n` is. Options then:

- **Swap the dimensions.** If the *values* are small, let `dp[v]` be the minimum weight needed to reach value `v`. Then the answer is the largest `v` with `dp[v] ≤ W`, in O(n · Σv) time.
- **Meet in the middle**, for n up to about 40. Enumerate the subsets of each half (2²⁰ ≈ 10⁶ each), sort one side, and match pairs.
- **Memoised recursion on `(i, c)`** when only a few capacities are reachable, for example a handful of large weights. A hash map visits only the states that actually occur.

## How to spot it

- **Each element is used or not used**, and the choices must meet a **sum, budget, or capacity**.
- The question is "can we reach exactly X", "how many ways to reach X", "fewest elements to reach X", or "best value within budget X".
- The problem can be rewritten as **splitting a set into two groups**, as in 416, 494 and 1049. Algebra on the two group sums usually yields a single target.
- An element can be **reused**, like coins or squares. That makes it unbounded, with an ascending loop.
- The budget is **small**, up to a few thousand or 10⁴. A large target with few elements points to meet in the middle or recursion instead.

## When it's the wrong tool

- **Items can be split.** Fractional knapsack is solved greedily by value per weight.
- **The capacity is huge and the values are not small.** Use one of the alternatives above.
- **Order and adjacency matter**, not just which items are chosen. Problems like House Robber, where adjacent picks are forbidden, are linear DP over the index, with no capacity dimension.

## Pitfalls

- **Wrong loop direction in one array.** Ascending turns 0/1 into unbounded, and descending turns unbounded into 0/1. Both still produce numbers that look reasonable.
- **Wrong loop nesting when counting.** Items outer counts combinations, capacity outer counts permutations. Check which one the problem wants on a two-coin example.
- **Base case not matching the question.** Initialise with `-∞` for "exactly", `0` for "at most", `1` at `dp[0]` for counting, and `true` at `dp[0]` for feasibility.
- **`INT_MAX` as infinity in a `min` recurrence.** `dp[c - w] + 1` overflows to a large negative number and wins every `min`. Use a sentinel like `amount + 1`.
- **Skipping the parity and range checks** in the subset-sum rewrites (416, 494). An odd total or `|target| > total` has answer 0, or `false`, before any DP runs.
- **Counting overflow.** The number of ways grows exponentially. Use `long long`, or the modulus the problem specifies, at every addition.
- **2D table when 1D suffices.** It is correct, but it uses O(n · W) memory. Keep it only when you need to reconstruct the chosen items.
