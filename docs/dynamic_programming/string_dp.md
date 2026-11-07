# String DP: Two Sequences, One Table

Five problems in this repo share one table shape: Longest Common Subsequence (1143), Edit Distance (72), Distinct Subsequences (115), Interleaving String (97) and Regular Expression Matching (10). Each compares two strings, and each fills `dp[i][j]` from the same three neighbouring cells. They differ in three places: what a cell stores, which neighbours it reads, and what the first row and column hold. With the shared part learned once, a new problem in this family comes down to filling in those three choices.

This file assumes the basics in [`dynamic_programming.md`](dynamic_programming.md) (memoization vs tabulation) and [`dp_1d_vs_2d.md`](dp_1d_vs_2d.md) (why two sequences need two dimensions, and how to collapse the table to one row).

## The state: prefix lengths, not positions

For strings `a` (length `n`) and `b` (length `m`):

> `dp[i][j]` = the answer for the first `i` characters of `a` and the first `j` characters of `b`.

`i` and `j` are **lengths**, so they run from `0` to `n` and `0` to `m`, and the table is `(n+1) × (m+1)`. The last character of each prefix is therefore `a[i-1]` and `b[j-1]`, which is why every solution in `dp_2D/` compares `a[i-1] == b[j-1]` and never `a[i] == b[j]`.

The extra row and column hold the empty prefix (`i = 0` or `j = 0`). Without them, the first real row would need its own special-case code. With them, the base case becomes data in the table, and the main double loop runs from 1 with no bounds checks. The answer is always in the bottom-right cell, `dp[n][m]`.

## The three moves

```
                 column j-1        column j

   row i-1    dp[i-1][j-1]       dp[i-1][j]
                 (diagonal)  \       (up)
                              (1)     | (2)
                                 \    v
   row i      dp[i][j-1]  --(3)-->  dp[i][j]
                 (left)
```

Every transition looks at the last characters, `a[i-1]` and `b[j-1]`, decides what happens to them, and reads the cell for the shorter prefixes that remain:

1. **Diagonal, `dp[i-1][j-1]`.** Both last characters are used up together: they match, are paired, or one replaces the other.
2. **Up, `dp[i-1][j]`.** Only `a[i-1]` is used up (taken, deleted or skipped), and `b` keeps all `j` characters.
3. **Left, `dp[i][j-1]`.** Only `b[j-1]` is used up, and `a` keeps all `i` characters.

Each of the five problems is a choice of which arrows are allowed, under what condition, and how the values they bring in are combined (max, min, sum, or OR).

| Problem | Cell holds | Last chars match | Last chars differ | Combine |
|---|---|---|---|---|
| LCS (1143) | length of LCS | `1 + diag` | `up`, `left` | max |
| Edit Distance (72) | fewest edits | `diag` (free) | `1 + up` (delete), `1 + left` (insert), `1 + diag` (replace) | min |
| Distinct Subsequences (115) | number of ways | `up + diag` | `up` | sum |
| Interleaving String (97) | can it be built | see below | see below | OR |
| Regex Matching (10) | does it match | `diag` | `false`, or the `*` rules | OR |

## The problems, one at a time

### Longest Common Subsequence (1143)

```cpp
if (a[i-1] == b[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
```

A matching pair extends the best subsequence of both shorter prefixes by one. When the characters differ, at least one of them is not in the LCS, so the answer is the better of dropping `a[i-1]` (up) or dropping `b[j-1]` (left). The base row and column are 0, because an empty string shares nothing with anything.

### Edit Distance (72)

```cpp
dp[i][0] = i;  dp[0][j] = j;          // delete all i chars / insert all j chars
if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
else dp[i][j] = 1 + min({dp[i-1][j],  // delete a[i-1]
                         dp[i][j-1],  // insert b[j-1]
                         dp[i-1][j-1]}); // replace
```

This one has non-zero base cases. Turning `i` characters into the empty string takes `i` deletions, and building `j` characters from nothing takes `j` insertions. Every arrow corresponds to one edit operation, which is why each costs `+1`, except the diagonal on a match, which costs 0.

Worked example, `horse` → `ros`, answer 3:

```
         ""  r  o  s
    ""    0  1  2  3
    h     1  1  2  3
    o     2  2  1  2      o == o: copy the diagonal (1)
    r     3  2  2  2
    s     4  3  3  2      s == s: copy the diagonal (2)
    e     5  4  4  3      e ≠ s: 1 + min(2, 4, 3) = 3, via up (delete 'e')
```

### Distinct Subsequences (115)

Count how many ways `t` appears as a subsequence of `s`.

```cpp
dp[i][0] = 1;                          // empty t: one way (pick nothing)
dp[0][j] = 0;  (j > 0)                 // empty s cannot produce non-empty t
dp[i][j] = dp[i-1][j];                 // skip s[i-1]
if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];  // or use it for t[j-1]
```

This problem never reads **left**. Characters of `s` may be skipped, but every character of `t` has to be matched, so there is no move that drops `t[j-1]`. The values are counts, so the two options are added rather than compared.

Worked example, `s = "babgbag"`, `t = "bag"`, answer 5:

```
         ""  b  a  g
    ""    1  0  0  0
    b     1  1  0  0
    a     1  1  1  0
    b     1  2  1  0      b == b: 1 (up) + 1 (diag) = 2
    g     1  2  1  1
    b     1  3  1  1
    a     1  3  4  1      a == a: 1 (up) + 3 (diag) = 4
    g     1  3  4  5      g == g: 1 (up) + 4 (diag) = 5
```

Counts in this problem grow quickly. Intermediate cells can exceed 32 bits even when the final answer fits, which is why the C++ tabulation uses `unsigned long long`. An unsigned type wraps around on overflow instead of being undefined behaviour, and the final cast back to `int` gives the right value when the true answer fits in 32 bits.

### Interleaving String (97)

Decide whether `s3` can be formed by interleaving `s1` and `s2` while keeping each one's internal order.

There are three strings but only two indices. After using `i` characters of `s1` and `j` of `s2`, exactly `i + j` characters of `s3` have been produced, so the position in `s3` is derived rather than stored. The next character to explain is `s3[i+j-1]`.

```cpp
if (n + m != s3.size()) return false;
dp[0][0] = true;
int k = i + j - 1;
bool fromS1 = i > 0 && dp[i-1][j] && s1[i-1] == s3[k];   // up
bool fromS2 = j > 0 && dp[i][j-1] && s2[j-1] == s3[k];   // left
dp[i][j] = fromS1 || fromS2;
```

This problem never reads the **diagonal**. Each character of `s3` comes from exactly one source string, so one step only ever advances `i` or `j`, never both. The `i > 0` and `j > 0` guards replace a separately initialised first row and column: the loops start at 0 and the guards stop the reads from going out of bounds.

### Regular Expression Matching (10)

`s` is the text, `p` the pattern, where `.` matches any character and `x*` matches zero or more copies of `x`. A helper `matches(i, j)` is true when `p[j-1] == '.'` or `s[i-1] == p[j-1]`.

```cpp
dp[0][0] = true;
if (p[j-1] == '*') {
    dp[i][j] = dp[i][j-2];                        // zero copies: drop "x*"
    if (i > 0 && matches(i, j-1))
        dp[i][j] = dp[i][j] || dp[i-1][j];        // one more copy: consume s[i-1]
} else {
    dp[i][j] = i > 0 && matches(i, j) && dp[i-1][j-1];
}
```

Two things break the three-arrow pattern here.

**`*` reads two columns back.** The token `x*` is two characters of pattern, so "use zero copies" removes both of them and jumps from `j` to `j-2`.

**"One more copy" reads up, and stays in column `j`.** After `x*` matches `s[i-1]`, the same `x*` remains available for `s[i-2]`, `s[i-3]` and so on. That is why the move consumes a character of `s` (row `i-1`) but keeps the pattern unchanged (column `j`). A self-loop on `j` is how one table cell represents "any number of copies".

**Row 0 is not all false, so the loops start at `i = 0`.** An empty string still matches patterns like `a*b*`, and that is computed by the `j-2` rule in row 0. In the other problems row 0 is a fixed base case, but here it has to be filled by the recurrence.

Worked example, `s = "aab"`, `p = "c*a*b"`, true (1 = match):

```
         ""  c  *  a  *  b
    ""    1  0  1  0  1  0      "c*" and "c*a*" both match the empty string
    a     0  0  0  1  1  0
    a     0  0  0  0  1  0      "a*" absorbs the second 'a' by reading up
    b     0  0  0  0  0  1      b == b: diagonal from the cell above-left
```

## Top-down form

Every problem here also has a memoized version in its `cpp/` folder. The recursive function takes the same `(i, j)` prefix lengths and returns `dp[i][j]`:

```cpp
int f(int i, int j) {
    if (i == 0 || j == 0) return base;   // the table's row 0 / column 0
    if (dp[i][j] != -1) return dp[i][j];
    // the same match / no-match recurrence, calling f instead of reading cells
    return dp[i][j] = ...;
}
// answer: f(n, m)
```

Base cases that the tabulation stores in the first row and column become early returns in the recursion. The memo table needs a "not computed yet" marker that cannot be a real answer. These solutions use `-1`. For boolean results, the Java and Rust ports use `null`/`None`, because `false` is a real answer.

Recursion depth is up to `n + m`, one level per character removed. That is fine in C++, but Python's default limit of 1000 calls can be reached with strings of a few hundred characters each. The Python memo ports for 1143, 72, 97 and 115 raise it with `sys.setrecursionlimit`. The regex port does not need to, because LeetCode limits both of its strings to 20 characters.

## Recognising the family

The signals in a problem statement:

- **Two strings (or arrays) are given, and the answer relates one to the other**: transform one into the other, find shared structure, count occurrences, check whether one generates the other.
- **Order matters but gaps are allowed**: "subsequence", "interleave", "delete characters", "wildcard". Contiguous substrings of a *single* string are a different shape (interval DP: Longest Palindromic Substring 5, Palindromic Substrings 647).
- **Brute force would branch on every character**: keep it or skip it, match it here or later. Each branch removes characters from the end, so the subproblems are prefix pairs, and there are only `(n+1)(m+1)` of them.

Then answer three questions to write the recurrence:

1. **What does `dp[i][j]` hold?** A length, a cost, a count, or true/false. That fixes the combine operator: max, min, sum, or OR.
2. **Which moves are legal?** Can a character of `a` be dropped (up)? Of `b` (left)? Can they be paired (diagonal), and only on a match?
3. **What do row 0 and column 0 hold?** Work out the answer when one string is empty. This is where most wrong answers come from: edit distance needs `i` and `j`, distinct subsequences needs 1 down column 0 and 0 along row 0, and regex needs row 0 computed by the recurrence.

## Complexity and space

All five run in O(n·m) time with O(n·m) space: `(n+1)(m+1)` cells, each computed in O(1). Regex is also O(1) per cell, since `*` only adds a fixed number of reads.

Each cell reads only row `i` and row `i-1`, so the table can shrink to one or two rows of length `m+1`, O(m) space. The diagonal value has to be saved before it is overwritten; [`dp_1d_vs_2d.md`](dp_1d_vs_2d.md#collapsing-2d-to-1d) shows the pattern. Keep the full table when the problem asks for the actual subsequence or the actual list of edits, because rebuilding them means walking back from `dp[n][m]` through the cells.

## Pitfalls

- **Off-by-one on characters.** `dp[i][j]` is about lengths, so the characters are `a[i-1]` and `b[j-1]`. Writing `a[i]` reads one past the prefix, and at `i = n` it reads past the end of the string.
- **Forgetting the length check.** Interleaving String must return false when `n + m != len(s3)` before indexing, or `s3[i+j-1]` can go out of range.
- **Wrong base row.** Initialising all of row 0 to false in regex, or all of column 0 to 0 in distinct subsequences, gives wrong answers on inputs like `("", "a*")` or any `t = ""`.
- **Overflow in counting problems.** Distinct Subsequences can overflow 32 bits mid-table; use a 64-bit unsigned type for the intermediate cells.
- **Asymmetric moves.** Distinct Subsequences never reads left, and Interleaving String never reads the diagonal. Copying the LCS recurrence without checking which moves are legal adds moves the problem does not allow.
