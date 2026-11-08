# Greedy Algorithms and How to Prove Them

A greedy algorithm builds its answer one choice at a time, takes the choice that looks best at that moment, and never changes it. The code is usually one loop, often after a sort. Whether the code is correct is a separate question: a wrong greedy rule gives a plausible answer on most inputs, including the examples in the problem statement. This page covers the two standard ways to prove a greedy rule correct, and the small counterexamples that show when a rule is wrong. The repo's greedy problems are worked through in [greedy problems](8e_greedy_problems.md).

## What has to be true

A greedy rule gives the optimal answer when two things hold:

- **The greedy choice is safe.** Some optimal answer includes the choice the rule makes. Taking it never rules out every optimal answer.
- **What remains is the same problem, smaller.** After the choice, the rest of the input is a smaller instance of the same problem, so the same rule can be applied again.

Dynamic programming also needs the second property, but not the first. DP tries every choice and keeps the best, so it does not need any single choice to be safe. Greedy tries one choice, so that choice has to be safe.

The two proof styles below are two ways to show that the greedy choice is safe.

## Proof style 1: the exchange argument

An exchange argument starts from **any** optimal answer and changes it, one step at a time, into the greedy answer, without ever making it worse. If that is always possible, the greedy answer is at least as good as the optimal one, so it is optimal.

The usual form:

1. Take an optimal answer `OPT` that differs from the greedy answer `G`.
2. Find the first choice where they differ.
3. Replace `OPT`'s choice there with `G`'s choice, and show that the result is still valid and no worse.
4. Repeat. Each exchange makes `OPT` agree with `G` on one more choice, and it never gets worse, so `G` is optimal.

### Example: interval scheduling

The task: given intervals, keep as many as possible with no two overlapping. Two intervals that only touch, like `[2, 3]` and `[3, 5]`, do not overlap.

The greedy rule: sort by **end** time. Keep each interval that starts at or after the end of the last kept interval.

For `[1,4], [2,3], [3,5], [4,7], [6,8]`, sorted by end: `[2,3], [1,4], [3,5], [4,7], [6,8]`.

```
interval   last kept end   start >= last end?   action
[2, 3]          —                 yes            keep, last end = 3
[1, 4]          3                 no             skip
[3, 5]          3                 yes            keep, last end = 5
[4, 7]          5                 no             skip
[6, 8]          5                 yes            keep, last end = 8
```

Greedy keeps 3 intervals. Checking every subset gives 3 as the maximum, so the answer is right on this input.

**The exchange.** Let `g` be the first interval greedy keeps, the one that ends earliest. Take any optimal answer whose first interval `o` is not `g`. Replace `o` with `g`:

- `g` ends no later than `o`, because `g` ends earliest of all intervals.
- Every other interval in the optimal answer starts at or after `o` ends, so it also starts at or after `g` ends. Nothing new overlaps.
- The number of intervals is unchanged.

So some optimal answer starts with `g`. After `g`, the remaining problem is the same task on the intervals that start at or after `g` ends, and the same argument applies to the next choice.

**What a wrong sort key does.** Sorting by **start** keeps `[1, 4]` first, then `[4, 7]`, and nothing after that fits: 2 intervals instead of 3. The exchange argument fails for this rule because the interval that starts earliest can end late, and replacing `o` with it can cause new overlaps.

## Proof style 2: greedy stays ahead

A "stays ahead" proof defines a measure of progress and shows that after every step, greedy's progress is at least as good as any other strategy's after the same number of steps. Then greedy cannot finish later or worse than the optimum.

### Example: Jump Game (55)

`nums[i]` is the longest jump allowed from index `i`. The task: decide whether the last index can be reached from index 0.

The greedy rule: walk the indices from left to right and keep `reach`, the furthest index reachable so far. At index `i`, if `i <= reach`, then `i` can be reached, and `reach` becomes `max(reach, i + nums[i])`.

**The measure** is `reach` after processing indices `0..i`. It is the furthest index that **any** sequence of jumps through those indices can reach, because every jump starting from them was considered. No strategy can get further using only those indices. If greedy ever finds an index `i > reach`, no strategy can reach `i`, and the answer is false.

A different greedy rule, "always take the longest jump from the current index", is wrong. For `[2, 5, 0, 0, 0, 1]`, it jumps from index 0 to index 2, where the value is 0, and is stuck. A jump of 1 to index 1 instead reaches index 5 directly. Tracking `reach` never commits to a landing spot: at index 0 it records that indices 1 and 2 are both reachable, and at index 1 `reach` becomes 6.

## Counterexamples: when a greedy rule is wrong

The fastest test of a greedy rule is to look for a small input where it fails. Two or three elements are usually enough.

**Coin change with coins 1, 3 and 4, amount 6.** Taking the largest coin that fits gives `4 + 1 + 1`, three coins. `3 + 3` uses two. Taking the 4 left a remainder of 2, which only 1-coins can make. Coin Change needs DP ([knapsack](../10_dynamic_programming/10c_knapsack.md)). With coins 1, 5, 10 and 25 the same greedy rule happens to be optimal, but that depends on those particular values.

**0/1 knapsack, capacity 10.** Items: weight 6 value 30, and two items of weight 5 value 20. Taking the best value per weight first takes the weight-6 item (5 per unit). Neither weight-5 item fits after it, so greedy ends with 30. The two weight-5 items give 40. If items could be cut into fractions, the greedy rule would be optimal. With whole items it is not.

**Dijkstra with a negative edge.** Dijkstra's algorithm is greedy: it fixes the distance of the closest unfinished node and never changes it. A negative edge found later can make a route to that node shorter, and the fixed distance is then wrong. Dijkstra needs non-negative weights, and Bellman-Ford handles negative ones ([Bellman-Ford](../09_graphs/9e_bellman_ford.md)).

In all three, an early choice removed an option that a later step needed.

## Deciding whether greedy works

1. **Write down the greedy rule.** Smallest first, earliest end, furthest reach, cheapest so far.
2. **Look for a counterexample of two to four elements.** Try inputs designed to make the rule's first choice bad, like the coin and knapsack examples above.
3. **If none is found, try an exchange argument or a stays-ahead argument.** If either goes through, the rule is correct.
4. **If a counterexample is found, use DP**, which tries every choice instead of one ([dynamic programming](../10_dynamic_programming/10a_dynamic_programming.md)).

Greedy fits most often when the answer is a feasibility check or a single number computed in one scan, and the input has a natural order, such as times, positions or sizes. It fits least often when items are chosen from a set under a capacity or an exact target, which is the knapsack shape.

## Cost

Most greedy solutions are one pass, O(n), often after an O(n log n) sort, which then dominates. They usually need O(1) extra space. A DP for the same problem, when one is needed, often costs O(n · W) time and space for a capacity `W`.

## Common mistakes

- **Checking only the given examples.** The examples in a problem statement are chosen to explain it, not to break wrong solutions.
- **Using a greedy rule from a similar problem.** Fractional knapsack is greedy and 0/1 knapsack is not. Coins 1, 5, 10, 25 are greedy and coins 1, 3, 4 are not.
- **Sorting by the wrong key.** Interval scheduling sorted by start instead of end returns a wrong count with no error, as shown above.
- **Using greedy to count.** Problems that ask for the number of ways need every option counted, which is DP. Greedy commits to one option.
