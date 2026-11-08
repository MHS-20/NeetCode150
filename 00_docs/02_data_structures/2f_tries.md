# Tries (Prefix Trees)

## The structure

A trie stores strings by **sharing their common prefixes**. Each edge carries one character, and a path from the root spells a prefix. The node reached by that path represents every word starting with it.

```
words: "cat", "car", "card", "dog"

              (root)
              /    \
             c      d
             |      |
             a      o
            / \     |
           t   r    g*
           *   *
               |
               d*

* = a word ends here
```

"car" and "card" share four edges; "cat" and "car" share two. The saving is the point — a dictionary of English words has enormous prefix overlap.

The `*` flag matters as much as the edges. Without a boolean marking "a word ends at this node", the trie above cannot distinguish `"car"` (a real word) from `"ca"` (only a prefix). Searching for a word checks the flag; searching for a prefix does not.

## A node

```python
class TrieNode:
    def __init__(self):
        self.children = {}        # char → TrieNode
        self.is_word = False
```

For a lowercase-only alphabet, an array of 26 slots replaces the dict. It is faster — indexing by `ord(c) - ord('a')` avoids hashing entirely, and the memory is contiguous — but it allocates 26 pointers per node whether they are used or not. Use the array when the alphabet is small and fixed, the dict when it is large, sparse, or unknown.

## Operations and complexity

Every operation walks one character at a time down from the root, so the cost is the **length of the string**, not the size of the dictionary.

| Operation | Cost |
|---|---|
| insert a word of length L | O(L) |
| search for a word of length L | O(L) |
| check a prefix of length L | O(L) |
| list all words with a prefix | O(L + output) |
| space | O(total characters), at most O(N·L) |

```python
def insert(self, word):
    node = self.root
    for c in word:
        if c not in node.children:
            node.children[c] = TrieNode()
        node = node.children[c]
    node.is_word = True

def search(self, word):
    node = self._walk(word)
    return node is not None and node.is_word

def starts_with(self, prefix):
    return self._walk(prefix) is not None

def _walk(self, s):
    node = self.root
    for c in s:
        if c not in node.children:
            return None
        node = node.children[c]
    return node
```

**The number of stored words never appears in the complexity.** A trie holding ten words and one holding ten million answer a five-character query in the same five steps. That independence is the reason the structure exists.

## Why not a hash set

For exact lookup, a hash set is simpler and about as fast: hashing a length-L string is O(L) too. The trie wins on the operations a hash set cannot do at all.

| Query | Hash set | Trie |
|---|---|---|
| "is `cat` in the dictionary" | O(L) | O(L) |
| "is any word prefixed by `ca`" | **O(N·L)** — scan everything | O(L) |
| "all words starting with `ca`" | O(N·L) | O(L + output) |
| "words matching `c.t`" (wildcards) | O(N·L) | prune during DFS |
| memory on overlapping words | full copy of each | shared prefixes |

A hash of `"car"` bears no relation to the hash of `"ca"` — hashing deliberately destroys that relationship (see [`2a_hashing.md`](2a_hashing.md)). A trie preserves it structurally, which is exactly what prefix queries need.

## What it's used for

**Autocomplete and prefix search.** Walk to the prefix node, then DFS below it to collect every word in that subtree.

**Wildcard matching.** Design Add and Search Words, where `.` matches any character. At a `.`, recurse into every child instead of one:

```python
def search(node, word, i):
    if i == len(word):
        return node.is_word
    c = word[i]
    if c == '.':
        return any(search(child, word, i + 1) for child in node.children.values())
    return c in node.children and search(node.children[c], word, i + 1)
```

A `.` costs a branching factor of 26 at that position, so a query of `k` wildcards is O(26ᵏ · L) in the worst case.

**Word Search II** — the problem that justifies the structure. Finding one word in a grid is a backtracking DFS (see [`8a_backtracking.md`](../08_techniques/8a_backtracking.md)); finding *all* of several thousand words means running that search once per word. Instead, build a trie of the whole word list and run a single DFS over the grid, carrying a trie node alongside the grid position. The moment the path spells something that is not a prefix of any word, the trie node has no matching child and the entire branch is abandoned.

```
grid path "ca"  →  trie node exists  →  keep exploring
grid path "cz"  →  no child 'z'      →  prune immediately
```

Thousands of separate searches collapse into one pruned traversal. This is the general pattern: **a trie turns "check against a dictionary" into a pruning test that costs O(1) per step.**

**Other uses.** IP routing tables (longest-prefix match), word break with a dictionary, and — with bits instead of characters — maximum XOR pair problems, where a binary trie over 32-bit integers finds the best partner in 32 steps.

## The cost

Space. Each node carries a children container plus a flag, so a trie over strings with little shared prefix uses far more memory than storing the strings themselves. A 26-pointer array node is 200+ bytes to hold one character. Compressed variants (radix trees / Patricia tries) merge chains of single-child nodes into one edge labelled with a whole substring, which helps considerably, though they are rarely needed in interviews.

## Pitfalls

- **Forgetting `is_word`.** Search then returns true for any prefix, and `"ca"` reports as a word.
- **Not returning to the root.** Each new query starts at `self.root`; reusing a stale node from the previous query silently searches a subtree.
- **Deleting by clearing `is_word` only.** Correct in behaviour, but the nodes stay allocated. Genuine deletion prunes bottom-up, removing each node that has no children and is not itself a word end.
- **Building the trie inside the loop.** In Word Search II the trie is built once before the grid traversal; rebuilding it per cell restores the complexity the trie was meant to remove.
- **Assuming lowercase.** The 26-slot array breaks on uppercase, digits, or Unicode. Check the constraints before choosing it over a dict.
