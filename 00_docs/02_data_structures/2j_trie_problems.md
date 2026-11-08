# Trie Problems

The three problems in `08_tries/` build on each other. Implement Trie (208) is the structure itself. Design Add and Search Words (211) adds a wildcard, which turns one walk down the trie into a search over several branches. Word Search II (212) combines a trie with the grid backtracking of Word Search, so that one search over the grid looks for every word at once. The structure, its costs and its comparison with a hash set are in [tries](2i_tries.md).

The examples follow the C++ solutions in `08_tries/`. Every trace was produced by running the same steps on the input shown.

## Implement Trie (208)

Each node has an array of 26 child pointers, one per lowercase letter, and a flag `is_end` that marks the end of a word:

```cpp
struct Node {
    Node *children[26] = {};
    bool is_end = false;
};
```

- **`insert`** walks the word from the root, creating each missing child, and sets `is_end` on the last node.
- **`search`** walks the word and fails at the first missing child. At the end it returns `is_end`, because reaching a node only proves that the word is a **prefix** of something stored.
- **`startsWith`** walks the same way but returns `true` at the end, whatever `is_end` is.

`search` and `startsWith` differ only in that last line. After inserting `"apple"`, `search("app")` is false and `startsWith("app")` is true.

The repo's class has a destructor that frees the nodes with a postorder walk: children first, then the node. Without it, every node allocated with `new` would leak when the trie is destroyed.

## Design Add and Search Words (211): the wildcard

`search` may contain `.`, which matches any one letter. A normal letter still follows one child. A `.` has to try **every** existing child, because any of them could lead to a match:

```cpp
bool searchFrom(const Node *cur, const string &word, int pos) const {
    for (int i = pos; i < word.size(); i++) {
        char ch = word[i];
        if (ch != '.') {
            cur = cur->children[ch - 'a'];      // one way down
            if (!cur) return false;
        } else {
            for (const Node *n : cur->children)  // every way down
                if (n && searchFrom(n, word, i + 1))
                    return true;
            return false;
        }
    }
    return cur->is_end;
}
```

The repo's first solution walks normal letters in a loop and only recurses at a `.`. That is the "mixed" in its file name. The second solution recurses on every character.

After adding `"bad"`, `"dad"` and `"mad"`:

```
search    path tried                                   result
"pad"     no child 'p' at the root                     false
"bad"     b → a → d, is_end                            true
".ad"     '.' tries b first: b → a → d, is_end         true (stops at the first match)
"b.."     b, then '.' tries a, then '.' tries d        true
"b."      b, then '.' tries a: a is not a word end     false
```

The search returns as soon as one branch matches, so `".ad"` never visits `d` or `m` at the root.

**Cost.** A word with no `.` costs O(L). Each `.` can multiply the branches by up to 26, so a query with `k` dots can cost O(26^k · L) in the worst case. On a real dictionary most branches end early, because few children exist below each node.

## Word Search II (212)

The task: given a grid of letters and a list of words, return every word that can be traced in the grid, moving between adjacent cells and using each cell at most once per word.

Word Search (79) finds one word with a backtracking search from every cell ([backtracking with constraints](../08_backtracking/8c_constraints.md#word-search-79)). Running that once per word repeats the grid search for every word in the list. Words that share a prefix, like `"oath"` and `"oat"`, repeat the same steps.

### One search, with a trie node alongside

The solution puts every word in a trie, then runs **one** backtracking search over the grid. The search carries a trie node as well as a grid position. Moving to a cell with letter `ch` means moving to the trie node's child for `ch`:

- If that child does not exist, no word in the list continues this path. The branch is pruned on the spot.
- If the child marks the end of a word, the word is found.

```cpp
void dfs(vector<vector<char>> &board, Node *node, int r, int c, vector<string> &res) {
    char ch = board[r][c];
    Node *next = node->children[ch - 'a'];
    if (!next) return;                    // no word continues with this letter
    if (!next->word.empty()) {
        res.push_back(next->word);
        next->word.clear();               // report each word once
    }
    board[r][c] = '#';                    // on the current path
    for (auto &d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
        if (board[nr][nc] == '#') continue;
        dfs(board, next, nr, nc, res);
    }
    board[r][c] = ch;                     // off the path again
}
```

Two details in this code:

- **The node stores the whole word**, not just a flag. When the end of a word is reached, the word can be added to the result without rebuilding it from the path.
- **The word is cleared after it is found.** The same word can often be traced along more than one path in the grid. Clearing it means it is reported once, and later paths to the same node find an empty string.

Unlike Word Search (79), this search never returns early, so the cell is always restored by the last line, and the board is unchanged at the end.

### Trace

For this board and the words `["oath", "pea", "eat", "rain"]`:

```
o a a n
e t a e
i h k r
i f l v
```

The result is `["oath", "eat"]`. `"oath"` is traced o(0,0) → a(0,1) → t(1,1) → h(2,1). `"eat"` is traced e(1,3) → a(1,2) → t(1,1). `"pea"` fails at once, because there is no `p` on the board. `"rain"` fails because the only `r`, at (2,3), has no neighbour `a`.

On this board, the trie search makes 41 calls to `dfs`. Running Word Search (79) once per word makes 58 calls. The board and the list are both small here, so the gap is small. It grows with the number of words: each extra word adds a full grid search in the per-word version, but in the trie version it only adds a path to the trie, and words that share a prefix share the search steps.

### Cost

With `R · C` starting cells and words up to length `L`, the search from each cell explores at most `4 · 3^(L-1)` paths: four directions for the first step and three after, because the cell just left is marked. So the search is O(R · C · 4 · 3^(L-1)), whatever the number of words. Building the trie costs O(total letters in the word list).

A common extra optimisation removes trie nodes once all the words below them have been found, so later searches stop even earlier. The repo's solution does not do this. It clears found words, but leaves the nodes in place.
