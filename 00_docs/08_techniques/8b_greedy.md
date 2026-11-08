# Greedy Algorithms

## What it is

Take the choice that looks best right now, never reconsider it, and arrive at a globally optimal answer anyway. No table, no recursion, usually one pass.

That last clause is the whole difficulty. A greedy algorithm is trivial to write and hard to *justify* — the code is five lines and the question is always whether those five lines are correct. Dynamic programming explores every combination of choices and is therefore safe by construction; greedy commits to one and must argue that committing costs nothing.

## When it works

Two conditions, both required.

**Greedy choice property.** The locally best choice is contained in some globally optimal solution. Taking it never forecloses the optimum — at worst it reaches a different optimum of equal value.

**Optimal substructure.** After committing to that choice, what remains is the same problem on a smaller input. This condition is shared with DP; it is the first one that separates the two.

The standard way to establish the first condition is an **exchange argument**:

> Suppose some optimal solution does not contain the greedy choice. Show that swapping one of its elements for the greedy choice keeps it valid and no worse. The optimum therefore can include the greedy choice, so taking it is safe.

Interval scheduling makes this concrete. Greedy keeps the interval that **ends earliest**. Suppose an optimal schedule starts with some other interval instead. Swap that first interval for the earliest-ending one: it still conflicts with nothing, since it finishes no later than what it replaced, and the count is unchanged. So an optimum exists that begins with the greedy choice, and by induction greedy is optimal throughout.

When such an argument cannot be made, greedy is wrong — and it will still produce plausible-looking output on the examples.

## When it fails

**Coin Change with arbitrary denominations.** Coins `[1, 3, 4]`, target 6. Greedy takes the largest coin first: 4, then 1, then 1 — three coins. The optimum is 3 + 3, two coins. Taking the 4 destroyed the possibility of the better answer, so the greedy choice property does not hold. This needs DP.

With US denominations `[1, 5, 10, 25]`, greedy *is* optimal — but that is a property of those specific values, not of the problem. The distinction matters: greedy correctness depends on the input structure, not the question being asked.

**0/1 Knapsack.** Picking the highest value-per-weight item first fails whenever that item's weight blocks a better pair. Capacity 10, items `(w=6, v=30)` and two of `(w=5, v=20)`: greedy takes the first for 30, then nothing else fits. Taking the two smaller ones gives 40. The *fractional* version, where items can be cut, is greedy-optimal — the constraint that breaks it is indivisibility.

**Shortest path with negative edges.** Dijkstra is greedy — it finalises the closest unvisited node and never revisits it. A negative edge can make a longer-looking route cheaper later, which invalidates exactly that commitment, so Dijkstra needs non-negative weights and Bellman-Ford does not.

The pattern in all three: greedy fails when an early commitment removes options that a later step needed.

## How to decide, in practice

Under interview time pressure, the sequence that works:

1. **Guess a greedy rule.** Largest first, earliest deadline, ends soonest, closest, cheapest.
2. **Attack it with small adversarial cases.** Deliberately try to construct an input where the greedy choice loses. Two or three elements is usually enough — the `[1, 3, 4]` counterexample above is size three.
3. **If no counterexample appears, sketch the exchange argument.** If the swap clearly works, commit.
4. **If a counterexample appears, switch to DP.** The exponential space of choices is exactly what a table is for (see [`10a_dynamic_programming.md`](../10_dynamic_programming/10a_dynamic_programming.md)).

A useful signal from the problem statement: greedy tends to fit when the answer is a **count**, a **feasibility check**, or a **single scan quantity**, and the input has an obvious ordering. It tends to fail when the question asks for the minimum *number* of items chosen from a set with a capacity or exact-target constraint — that family is almost always knapsack-shaped.

## Complexity

Greedy is usually O(n) after an O(n log n) sort, and the sort dominates. That is the actual payoff: where DP would need O(n·W) time and a table of the same size, greedy needs one pass and O(1) space. Choosing greedy when it is valid is often the difference between a solution that fits in memory and one that does not.

## The recurring shapes

**Sort, then sweep.** Most interval problems (see [`8c_intervals.md`](8c_intervals.md)). Non-Overlapping Intervals sorts by end and keeps everything compatible.

**Track a running best or a reachable frontier.**

*Jump Game* — can you reach the end? Keep the furthest index reachable so far; if the current index ever exceeds it, the answer is no.

```
nums = [2, 3, 1, 1, 4]

i=0  reach = max(0, 0+2) = 2
i=1  1 ≤ 2 ok,  reach = max(2, 1+3) = 4
i=2  2 ≤ 4 ok,  reach = 4
...  reach ≥ last index → True
```

No choice is ever reconsidered, because a further reach is never worse than a nearer one.

*Best Time to Buy and Sell Stock* — track the minimum price seen and the best profit against it. One pass.

*Maximum Subarray (Kadane's)* — at each element, either extend the current run or start fresh from here. Dropping a negative prefix is never wrong, since it can only reduce whatever follows.

```
nums = [-2, 1, -3, 4, -1, 2, 1]

cur = max(x, cur + x)     best = max(best, cur)
 -2 → cur -2, best -2
  1 → cur  1  (restart beats -1), best 1
 -3 → cur -2, best 1
  4 → cur  4  (restart), best 4
 -1 → cur  3, best 4
  2 → cur  5, best 5
  1 → cur  6, best 6
```

Kadane's sits exactly on the boundary between greedy and DP — it is a 1D DP whose table collapsed to a single variable.

**Feasibility by a global argument.** *Gas Station*: if total gas is at least total cost, a solution exists; the start is the index after wherever the running tank last went negative, because no station before that point could have made it through either.

**Counting with a rule.** Partition Labels (extend the current partition to the last occurrence of every character seen in it), Task Scheduler (schedule the most frequent task first, since it constrains the idle slots).

**Heap-assisted greedy.** When "best right now" changes as the input arrives, a priority queue supplies it in O(log n) — the top-K family in [`2e_heaps_and_priority_queues.md`](../02_data_structures/2e_heaps_and_priority_queues.md).

## Pitfalls

- **Testing on the provided examples only.** Problem examples are chosen to illustrate, not to break things. Build your own adversarial case.
- **Confusing "works on the samples" with proof.** Greedy failures are subtle and data-dependent; a wrong greedy passes many tests.
- **Carrying over a known-greedy result to a variant.** Fractional knapsack is greedy, 0/1 is not. Dijkstra is greedy, negative weights break it. US coins are greedy, arbitrary coins are not.
- **Sorting by the wrong key.** In interval scheduling, sorting by start instead of end gives a wrong answer with no error.
- **Reaching for greedy on a "count the ways" problem.** Counting almost always needs DP; greedy answers "what is the best", not "how many are there".
