# Backtracking: the Template and the Decision Tree

Backtracking lists every answer to a problem by making one decision at a time: choose an option, recurse to make the remaining decisions, then undo the choice and try the next option. The decisions form a tree, called the **decision tree**, and the recursion walks it depth first. The tree is never stored. It exists only as the pattern of recursive calls, and one shared path is changed and restored as the recursion moves through it.

Backtracking fits when a problem asks for **all** answers (all subsets, all permutations, all valid boards), or for any answer to a puzzle with constraints. If the problem asks only for a count or a best value, DP is usually much faster ([dynamic programming](../10_dynamic_programming/10a_dynamic_programming.md)).

The examples follow the C++ solutions in `10_backtracking/`. Every trace was produced by running the same steps on the input shown.

## The template

```cpp
void backtrack(/* position in the decisions */, vector<int> &path, vector<vector<int>> &out) {
    if (/* every decision is made */) {
        out.push_back(path);           // record a copy of the answer
        return;
    }
    for (/* each option at this decision */) {
        if (/* the option breaks a rule */) continue;
        path.push_back(option);        // 1. choose
        backtrack(/* next decision */, path, out);   // 2. explore
        path.pop_back();               // 3. undo
    }
}
```

The three steps choose, explore and undo always come together. `path` is one vector shared by every call. At any moment it holds the choices on the way from the root of the decision tree to the current call, and nothing else.

### Why the undo is needed

After the recursive call returns, the next option is tried at the **same** decision. `path` must look exactly as it did before the first option was chosen. Without `pop_back`, the first option's value stays in `path`, and every later answer contains it. The output is then wrong, but nothing crashes.

### Why the answer is copied

`out.push_back(path)` in C++ copies the vector, which is what is wanted. In Python, `out.append(path)` stores a reference to the one shared list instead. The recursion keeps changing that list, so every entry of `out` ends up as the same list, which is empty once the recursion has undone every choice. Python solutions append `path[:]` or `list(path)`. In Java, `new ArrayList<>(path)` does the same.

## Subsets (78): two ways to shape the tree

The task: list every subset of an array of distinct numbers. The repo has two solutions, and they draw two different decision trees for the same output.

### Shape 1: include or skip each element

Each level of the tree decides one element: put it in the subset, or leave it out. Every subset is a leaf:

```cpp
void backtrack(vector<int> &nums, int idx, vector<int> &cur, vector<vector<int>> &result) {
    if (idx == nums.size()) {
        result.push_back(cur);
        return;
    }
    cur.push_back(nums[idx]);                 // include nums[idx]
    backtrack(nums, idx + 1, cur, result);
    cur.pop_back();                           // undo
    backtrack(nums, idx + 1, cur, result);    // skip nums[idx]
}
```

For `[1, 2, 3]`:

```
                          []
              include 1 /    \ skip 1
                    [1]        []
          inc 2  /   \ skip   /   \
            [1,2]    [1]    [2]    []
            /  \     /  \   /  \   /  \          include / skip 3
      [1,2,3][1,2][1,3][1][2,3][2][3]  []        ← 8 leaves, 8 subsets
```

The leaves come out in that order: `[1,2,3], [1,2], [1,3], [1], [2,3], [2], [3], []`.

### Shape 2: choose the next element to add

Each call records the current subset, then tries adding each element **after** the last one added. Every node of the tree, not only the leaves, is an answer:

```cpp
void backtrack(vector<int> &nums, int start, vector<int> &cur, vector<vector<int>> &result) {
    result.push_back(cur);                    // every path is a subset
    for (int i = start; i < nums.size(); i++) {
        cur.push_back(nums[i]);
        backtrack(nums, i + 1, cur, result);
        cur.pop_back();
    }
}
```

```
                 []
           /     |     \
        [1]     [2]    [3]
        /  \      |
    [1,2] [1,3] [2,3]
      |
   [1,2,3]
```

The output order is the preorder of this tree: `[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]`.

The `start` index is what prevents repeats. The loop only looks at elements after the last one added, so a subset is always built in index order. `[2, 1]` is never built, because after 2 the loop starts at index 2. Without `start` (looping from 0 every time), the tree would build every ordering of every subset.

Both shapes produce all 8 subsets. Shape 1 has exactly two branches per node, which suits problems where each element is taken or left. Shape 2 suits problems where each step picks the next item from what remains, such as combinations and partitions.

## Letter Combinations of a Phone Number (17)

Each digit maps to 3 or 4 letters, and the task is to list every string made of one letter per digit. Each level of the tree is one digit, and the options are its letters:

```cpp
void backtrack(const string &digits, int idx, string &cur, vector<string> &result) {
    if (idx == digits.size()) {
        result.push_back(cur);
        return;
    }
    for (char ch : mapping[digits[idx] - '0']) {
        cur.push_back(ch);
        backtrack(digits, idx + 1, cur, result);
        cur.pop_back();
    }
}
```

For `"23"`, digit 2 gives `abc` and digit 3 gives `def`, so the tree has 3 branches at the first level and 3 under each: `ad, ae, af, bd, be, bf, cd, ce, cf`. There are no rules to check, so every leaf is an answer.

## Cost: count the nodes

```
total time = (number of nodes in the decision tree) × (work per node)
```

The number of nodes is roughly the number of options per level raised to the number of levels. Recording an answer copies the path, which costs its length.

| Problem | Tree | Time |
|---|---|---|
| Subsets (78) | 2 options, n levels | O(2ⁿ · n) |
| Permutations (46) | n options, then n − 1, … | O(n! · n) |
| Letter Combinations (17) | up to 4 options per digit | O(4ⁿ · n) |
| Combination Sum (39) | depends on target and smallest value | exponential |
| N-Queens (51) | n options per row, most cut early | below O(n!) |
| Word Search (79) | 4 directions, word length L | O(R · C · 4^L) |

The factor `n` in the first rows is the cost of copying each answer into the output. Extra space is O(depth) for the recursion and the path, plus the output itself.

When a problem asks for all subsets, there are `2ⁿ` of them, so any solution that lists them takes at least `2ⁿ` steps. Backtracking cannot beat that bound. Cutting branches early, covered in [constraints and pruning](8c_backtracking_constraints.md), makes it much faster when most branches cannot lead to an answer.

## Backtracking and graph DFS

Backtracking is a DFS, but it differs from DFS on a graph in one detail. A graph DFS marks a node as visited and never unmarks it, because reaching each node once is enough. Backtracking unmarks on the way back, because a different path may need the same element or cell. Word Search (79) shows this in [constraints and pruning](8c_backtracking_constraints.md#word-search-79).
