# Backtracking: Combinations, Permutations and Duplicates

Most backtracking problems list subsets, combinations or permutations, often with rules on reuse and duplicates. Three questions decide the code:

- **Can an element be used more than once?** This decides whether the recursive call moves past the current element or stays on it.
- **Does order matter?** If not, a `start` index stops the tree from building the same set in different orders. If it does, every unused element is an option at every level.
- **Does the input contain equal values?** If so, equal values have to be skipped in the right place, or the same answer is produced more than once.

The template and the two tree shapes are in [backtracking basics](8a_basics.md). The examples follow the C++ solutions in `10_backtracking/`, and every trace was produced by running the same steps on the input shown.

## Combination Sum (39): reuse allowed

The task: the candidates are distinct, and each can be used any number of times. List every combination that adds up to `target`.

The repo uses the include-or-skip shape. "Include" adds the current candidate and **stays on it**, so it can be added again. "Skip" moves past it for good:

```cpp
void backtrack(..., int idx, int sum) {
    if (sum == target) { result.push_back(cur); return; }
    if (sum > target || idx >= candidates.size()) return;
    cur.push_back(candidates[idx]);
    backtrack(..., idx, sum + candidates[idx]);      // stay on idx: reuse allowed
    cur.pop_back();
    backtrack(..., idx + 1, sum);                    // move on: never use idx again
}
```

For `candidates = [2, 3, 6, 7]`, `target = 7`, the result is `[[2, 2, 3], [7]]`.

`[2, 3, 2]` is never built. Once the recursion skips 2, it never comes back to it, so every combination lists its values in candidate order. The check `sum > target` cuts a branch as soon as it overshoots, which works because every candidate is positive.

## Combination Sum II (40): each element once, with equal values

The task: the candidates may contain equal values, and each element can be used at most once. List every combination that adds up to `target`, with no combination repeated.

Two changes from problem 39:

1. **Include moves to `idx + 1`.** Each element is used at most once.
2. **Skip moves past every copy of the value.** The candidates are sorted first, so equal values are next to each other.

```cpp
sort(candidates.begin(), candidates.end());
...
cur.push_back(candidates[idx]);
backtrack(..., idx + 1, sum + candidates[idx]);      // use this copy
cur.pop_back();
int i = idx + 1;
while (i < candidates.size() && candidates[i] == candidates[idx])
    i++;                                             // skip every copy of the value
backtrack(..., i, sum);
```

### Why skipping every copy removes repeats

Take sorted candidates `[1, 1, 2, …]`, with the two 1s at indices 0 and 1. Without the `while` loop, "skip index 0, include index 1" builds the same combinations as "include index 0, skip index 1". Both start with a single 1. The output would contain each of those combinations twice.

With the loop, the decision for the value 1 becomes: include the first copy (and decide about the next copy later), or skip **all** copies. A combination with exactly one 1 can then only be built one way: include index 0, then skip index 1 and any later copies.

For `candidates = [10, 1, 2, 7, 6, 1, 5]`, `target = 8`, sorted to `[1, 1, 2, 5, 6, 7, 10]`, the result is:

```
[1, 1, 6]   [1, 2, 5]   [1, 7]   [2, 6]
```

## Subsets II (90): the same skip for subsets

The task: list every subset of an array that may contain equal values, with no subset repeated. The solution is Subsets (78) with the same sort and the same skip as problem 40.

For `[1, 2, 2]`:

```
with the skip:      [1,2,2] [1,2] [1] [2,2] [2] []
without the skip:   [1,2,2] [1,2] [1,2] [1] [2,2] [2] [2] []
```

Without the skip, `[1, 2]` and `[2]` each appear twice: once using the first 2, and once using the second.

### The same rule in the loop shape

The loop shape ([shape 2](8a_basics.md#shape-2-choose-the-next-element-to-add)) writes the skip as a condition on the loop index:

```cpp
sort(nums.begin(), nums.end());
for (int i = start; i < nums.size(); i++) {
    if (i > start && nums[i] == nums[i - 1])
        continue;                        // this value was already tried at this level
    cur.push_back(nums[i]);
    backtrack(nums, i + 1, cur, result);
    cur.pop_back();
}
```

`i > start` is the key part. The skip applies only to **siblings**, the options tried at the same level. The first copy of a value at each level is still tried, and the next copy can still be added **deeper**, below it. So `[2, 2]` is built once, by choosing the first 2 and then the second, but `[2]` is not built twice. Writing `i > 0` instead would also skip the second 2 deeper in the tree, and `[2, 2]` would never be built.

The 3Sum skip in [two pointers](../03_two_pointers/3a_opposite_ends.md#skipping-duplicates) is the same rule: after sorting, never start from the same value twice at the same position.

## Permutations (46): order matters

The task: list every ordering of an array of distinct numbers.

For permutations every element that is not yet used is an option at every level, so the `start` index does not apply. The repo's solution places one element per position by **swapping**: position `idx` takes each of the elements from `idx` to the end in turn, and the swap is undone afterwards:

```cpp
void backtrack(..., vector<int> &cur, int idx) {
    if (idx == nums.size()) { result.push_back(cur); return; }
    for (int i = idx; i < nums.size(); i++) {
        swap(cur[idx], cur[i]);        // choose cur[i] for position idx
        backtrack(..., cur, idx + 1);
        swap(cur[idx], cur[i]);        // undo
    }
}
```

Positions `0 .. idx-1` are fixed, and positions `idx ..` hold the elements still unused. The swap moves the chosen element into position `idx` and keeps the unused ones together after it, so no separate `used` array is needed.

For `[1, 2, 3]`, the output is:

```
[1,2,3]  [1,3,2]  [2,1,3]  [2,3,1]  [3,2,1]  [3,1,2]
```

The last two are in that order because, at position 0, choosing 3 swaps it with 1, which leaves `[3, 2, 1]`. Position 1 then tries 2 first.

The common alternative keeps a `used[]` array, loops over every index at every level, and skips the used ones. It costs O(n) per level to scan, the same order as the swaps.

The repo's second solution writes the same search without a loop: one recursive call tries the current candidate for position `idx`, and a second call moves to the next candidate for the same position.

## Summary

| Problem | Reuse | Order matters | Equal values | Recursive call after including `i` | Skip rule |
|---|---|---|---|---|---|
| Subsets (78) | no | no | no | `i + 1` | none |
| Subsets II (90) | no | no | yes | `i + 1` | sort; skip equal siblings |
| Combination Sum (39) | yes | no | no | `i` | none |
| Combination Sum II (40) | no | no | yes | `i + 1` | sort; skip equal siblings |
| Permutations (46) | no | yes | no | next position, any unused element | none |

`i` versus `i + 1` in the recursive call is the whole difference between 39 and 40's reuse rules. The skip of equal siblings is the whole difference between 78 and 90.
