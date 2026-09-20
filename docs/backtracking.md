# Backtracking

## What it is

DFS over a tree of *decisions* rather than over a graph of nodes. At each step you choose an option, recurse to see where that choice leads, then undo the choice and try the next one. The tree is not a data structure anywhere in memory — it exists only as the shape of the recursion.

```
subsets of [1,2,3]                  at each level: include this element, or don't

                    []
           /                 \
        [1]                   []            ← decide about 1
       /    \               /    \
   [1,2]    [1]         [2]       []         ← decide about 2
   /   \    /  \        /  \      /  \
[1,2,3][1,2][1,3][1]  [2,3][2]  [3]  []      ← decide about 3
```

Eight leaves, and each leaf is one answer. That is the whole method: enumerate a combinatorial space without ever materialising it.

Use it when the problem asks for **all** solutions, or for **one** solution to a constraint-satisfaction problem, and no formula or DP state captures the structure. If the problem asks only for a *count* or an *optimum*, check for a DP formulation first — backtracking is exponential and DP is usually polynomial (see `dynamic_programming.md`).

## The template

Every backtracking solution is this shape. Recognising it means the only real work is filling in the three slots.

```python
def backtrack(state, path, out):
    if is_complete(state):
        out.append(path[:])          # copy — see pitfalls
        return
    for choice in candidates(state):
        if not valid(choice, state):
            continue
        make(choice)                 # mutate state / append to path
        backtrack(next_state, path, out)
        undo(choice)                 # restore — the "backtrack"
```

The `make` / recurse / `undo` sandwich is the identifying feature. One mutable structure is threaded through the entire recursion and restored on the way out, so at any moment it holds exactly the current path and nothing else.

## Complexity: count the leaves

> **total = (number of nodes in the decision tree) × (work per node)**

Estimate the node count as `branching factor ^ depth`, then add the cost of building each output.

| Problem | Tree shape | Complexity |
|---|---|---|
| Subsets | 2 choices × n levels | O(2ⁿ · n) |
| Permutations | n, then n−1, then n−2 … | O(n! · n) |
| Combinations of size k | C(n, k) leaves | O(C(n,k) · k) |
| Letter combinations of a phone number | ≤ 4 per digit | O(4ⁿ · n) |
| N-Queens | n columns, heavy pruning | O(n!) upper bound, far less in practice |
| Word Search in a grid | 4 directions, path length L | O(R·C·4^L) |

The trailing `· n` is not decoration — it is the cost of copying each completed path into the output, and it is often the dominant factor in practice. Space is O(depth) for the recursion plus however large the output is.

Exponential is not a defect here. `2ⁿ` subsets genuinely exist, so any algorithm that lists them is `Ω(2ⁿ)`; backtracking is optimal up to the pruning. What pruning buys is a smaller constant and a smaller effective branching factor, not a better class.

## Pruning is where the real work is

Two ways to cut branches, and the first is much better:

**Check validity before recursing.** Reject a choice at the moment it is made, so the entire subtree below it is never entered. N-Queens placing a queen only on a safe square skips an enormous amount of the `nⁿ` naive space.

**Check feasibility of the remainder.** If the target is 7 and the current sum is already 9 with only positive candidates left, return immediately. Sorting the candidates first makes this a `break` rather than a `continue`, since everything after is also too large:

```python
for i in range(start, len(nums)):
    if total + nums[i] > target:
        break                 # sorted, so all later candidates also overflow
```

Generating a complete candidate and validating it at the leaf is the version to avoid — it does the full exponential work with none of the savings.

## Duplicates, and the two ways to control them

This is where most wrong answers come from. Two separate mechanisms, for two separate problems.

**Avoiding reuse of the same element** (combinations vs. permutations). Pass a `start` index so the recursion only ever looks forward. Order stops mattering, and `[1,2]` and `[2,1]` collapse into one.

```python
def backtrack(start, path):
    out.append(path[:])
    for i in range(start, len(nums)):
        path.append(nums[i])
        backtrack(i + 1, path)      # i + 1 → each element used once
        path.pop()                  # i → element reusable (Combination Sum)
```

Permutations need every element available at every level instead, so they use a `used` boolean array and iterate from 0 each time.

**Avoiding duplicate results from duplicate input values.** Sort the input, then skip a candidate that equals its predecessor *at the same level*:

```python
nums.sort()
for i in range(start, len(nums)):
    if i > start and nums[i] == nums[i - 1]:
        continue                     # same value already tried at this level
```

The `i > start` guard is what makes this correct: the duplicate is allowed *deeper* in the path (so `[1,1]` is still produced) but not as a sibling choice (so `[1,1]` is not produced twice). Getting this condition wrong is the single most common bug in the Subsets II / Combination Sum II family.

## The problem families

**Subsets / power set.** Include-or-exclude at each element. `2ⁿ` results.

**Combinations.** Subsets with a size or sum constraint. `start` index, prune on the constraint.

**Permutations.** All orderings. `used` array, or swap-in-place to save the array.

**Partitioning a string.** Palindrome Partitioning, Restore IP Addresses. The choice at each step is *where to cut*; recurse on the suffix after the cut.

**Grid path search.** Word Search. Mark the current cell as visited before recursing into the four neighbours, then unmark it — a `visited` set scoped to the current path, unlike the global one in graph traversal. This distinction matters: in BFS/DFS connectivity a node is marked once and never unmarked, because you only need to reach it; in backtracking it must be unmarked, because a later path may legitimately use the same cell.

**Constraint satisfaction.** N-Queens, Sudoku. The value is entirely in the validity check; keep column/diagonal occupancy in sets so `valid()` is O(1) rather than a board scan.

## Pitfalls

- **Appending the path without copying.** `out.append(path)` stores a reference to a list that the recursion keeps mutating — every entry in the output ends up identical, usually empty. Always `path[:]` or `list(path)`.
- **Forgetting to undo.** State leaks into sibling branches and the results are silently wrong rather than crashing.
- **Undoing something other than what was done.** `path.pop()` after appending one element, two pops after appending two. Keep `make` and `undo` symmetric and adjacent so the mismatch is visible.
- **Mixing up the two duplicate mechanisms.** `start`-index control and sort-then-skip solve different problems; a missing `start` produces permutations where combinations were wanted, and a missing skip produces repeated identical results.
- **`i + 1` vs. `i` in the recursive call.** One element each, or elements reusable. A single character separates Combination Sum from Combination Sum II.
- **Using backtracking where DP applies.** If the question is "how many ways" or "what is the minimum", the exponential enumeration is usually unnecessary.
