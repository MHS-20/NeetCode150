# Backtracking with Constraints: Pruning, Boards and Grids

In the problems on this page, most branches of the decision tree break a rule long before they reach a leaf. Checking the rule when a choice is made, before recursing, skips the whole subtree below a bad choice. This is called **pruning**. A version that builds every complete candidate and checks it at the end does the full exponential work and keeps none of the savings.

The template is in [backtracking basics](8a_backtracking_basics.md). The examples follow the C++ solutions in `10_backtracking/`, and every trace was produced by running the same steps on the input shown.

## Generate Parentheses (22): two counters as the rule

The task: list every balanced string of `n` pairs of parentheses.

Each position is `(` or `)`, so there are `2^(2n)` strings, but most are unbalanced. Two counters decide which characters are allowed at each step:

- `(` is allowed while `opened < n`: there are pairs left to open.
- `)` is allowed while `closed < opened`: there is an open `(` to close.

Any string built under these two rules is balanced, so no check is needed at the end.

```cpp
void backtrack(int n, int opened, int closed, string &cur, vector<string> &res) {
    if (closed == n) {                 // implies opened == n
        res.push_back(cur);
        return;
    }
    if (opened < n) {
        cur.push_back('(');
        backtrack(n, opened + 1, closed, cur, res);
        cur.pop_back();
    }
    if (closed < opened) {
        cur.push_back(')');
        backtrack(n, opened, closed + 1, cur, res);
        cur.pop_back();
    }
}
```

For `n = 3` the result is `((())), (()()), (())(), ()(()), ()()()`. The recursion makes 22 calls in total. Building every string of length 6 and checking each would visit `2^6 = 64` leaves and many more internal nodes.

The repo's first solution passes `cur + '('` as a new string instead of changing a shared one. It needs no undo, because each call has its own copy, but it copies the string at every call instead of only when an answer is recorded.

## N-Queens (51): constant-time safety checks

The task: place `n` queens on an `n × n` board so that no two share a row, a column or a diagonal. List every solution.

Each row gets exactly one queen, so the recursion goes row by row and the options are the columns. A column is allowed if no earlier queen is in the same column or on either diagonal through that square.

### Identifying diagonals with `r + c` and `r - c`

On one `/` diagonal, moving up a row moves one column right, so `r + c` stays the same. On one `\` diagonal, moving down a row moves one column right, so `r - c` stays the same. For `n = 4`:

```
r + c  (/ diagonals)          r - c + 3  (\ diagonals)
  c:  0 1 2 3                   c:  0 1 2 3
r=0:  0 1 2 3                 r=0:  3 2 1 0
r=1:  1 2 3 4                 r=1:  4 3 2 1
r=2:  2 3 4 5                 r=2:  5 4 3 2
r=3:  3 4 5 6                 r=3:  6 5 4 3
```

Squares with the same number share a diagonal. `r + c` ranges over `0 .. 2n-2`, and `r - c` over `-(n-1) .. n-1`. Adding `n - 1` shifts the second range to `0 .. 2n-2`, so both fit in arrays of size `2n - 1`.

The solution keeps three boolean arrays, one for columns and one for each kind of diagonal. Checking a square is three lookups, O(1), instead of a scan of the board:

```cpp
for (int col = 0; col < n; col++) {
    int d1 = row + col;
    int d2 = row - col + n - 1;
    if (cols[col] || diag1[d1] || diag2[d2])
        continue;                                  // pruned: under attack
    board[row][col] = 'Q';
    cols[col] = diag1[d1] = diag2[d2] = true;      // choose
    backtrack(n, row + 1, board, result);          // explore
    board[row][col] = '.';
    cols[col] = diag1[d1] = diag2[d2] = false;     // undo
}
```

For `n = 4` there are two solutions:

```
. Q . .        . . Q .
. . . Q        Q . . .
Q . . .        . . . Q
. . Q .        . Q . .
```

The search places a queen 16 times in total to find them. Without pruning, the row-by-row tree has `4^4 = 256` complete boards to check.

## Word Search (79)

The task: decide whether a word can be traced in a grid of letters by moving between horizontally or vertically adjacent cells, using each cell at most once.

The search starts from every cell. From a cell matching `word[idx]`, it tries the four neighbours for `word[idx + 1]`. A cell must not be reused **on the same path**, so it is marked while the path goes through it, and unmarked when the search backs out of it:

```cpp
bool dfs(vector<vector<char>> &board, const string &word, int idx, int row, int col) {
    char ch = word[idx];
    if (ch != board[row][col]) return false;       // pruned: wrong letter
    if (idx == word.size() - 1) return true;
    board[row][col] = '#';                          // mark: on the current path
    for (auto [dr, dc] : dirs) {
        int nr = row + dr, nc = col + dc;
        if (nr < 0 || nr >= board.size() || nc < 0 || nc >= board[0].size())
            continue;
        if (dfs(board, word, idx + 1, nr, nc)) return true;
    }
    board[row][col] = ch;                           // unmark: path backs out
    return false;
}
```

Writing `#` into the board marks the cell without a separate `visited` array. `#` never matches a letter of the word, so the letter check rejects a marked cell.

For this board:

```
A B C E
S F C S
A D E E
```

- `"ABCCED"` is found: A(0,0) → B(0,1) → C(0,2) → C(1,2) → E(2,2) → D(2,1).
- `"ABCB"` is not. After A → B → C, the only B next to that C is the one already on the path, and it is marked `#`.

### The unmark must run on every exit

The repo's solution returns `true` as soon as the rest of the word is found, before `board[row][col] = ch` runs. Every cell on the successful path keeps its `#`. Running `"ABCCED"` leaves the board as:

```
# # # E
S F # S
A D # E
```

LeetCode checks only the returned value, so the solution is accepted. But the board is not restored. A second search on the same board, for `"SEE"`, then returns false, because one of the E cells it needs is still marked. On a fresh board `"SEE"` is found. Restoring the cell before returning, on the success path too, keeps the board unchanged for the caller.

### Cost

Each search from a starting cell explores at most 4 directions per letter, and 3 after the first step because the previous cell is marked. With `L` letters and `R · C` starting cells, the cost is O(R · C · 3^L).

## Palindrome Partitioning (131)

The task: split a string into pieces that are all palindromes, and list every such split.

The decision at each step is **where the next piece ends**. From position `start`, each end `i` from `start` to the end of the string is an option. A piece that is not a palindrome is pruned before recursing:

```cpp
void backtrack(const string &s, int start, vector<string> &path, vector<vector<string>> &result) {
    if (start == s.size()) {
        result.push_back(path);
        return;
    }
    for (int i = start; i < s.size(); i++) {
        if (!isPalindrome(s, start, i)) continue;    // pruned
        path.push_back(s.substr(start, i - start + 1));
        backtrack(s, i + 1, path, result);
        path.pop_back();
    }
}
```

For `"aab"`:

```
start 0:  "a"   palindrome → start 1:  "a"  → start 2: "b"  → done: [a, a, b]
                                       "ab"  not a palindrome: pruned
          "aa"  palindrome → start 2:  "b"  → done: [aa, b]
          "aab" not a palindrome: pruned
```

The result is `[["a", "a", "b"], ["aa", "b"]]`.

`isPalindrome` scans the piece each time it is called, so the same piece can be checked many times. A table `pal[i][j]`, filled once in O(n²) as in [interval DP](../10_dynamic_programming/10e_interval_dp.md), turns each check into one lookup.
