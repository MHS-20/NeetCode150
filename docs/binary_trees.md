# Binary Trees

## Vocabulary, fixed once

A binary tree is a set of nodes where each node holds a value and up to two children, `left` and `right`. One node is the root; every other node has exactly one parent.

```
            1          ← level 0, depth 0
          /   \
         2     3       ← level 1
        / \     \
       4   5     6     ← level 2
```

- **Depth** of a node — number of edges from the root down to it. Node 4 has depth 2.
- **Height** of a node — number of edges on the longest path down to a leaf. The height of the *tree* is the height of its root; above, that is 2.
- **Leaf** — a node with no children (4, 5, 6).
- **Level** `i` — all nodes at depth `i`.

Height counted in *edges* vs. in *nodes* differs by one. Pick one and state it; most bugs in "height" problems are off-by-one between these two conventions. Edges is the more common convention, and makes an empty tree height `-1`, a single node height `0`.

Two shapes have names worth knowing:

- **Complete** — every level full except possibly the last, which is filled left to right. Heaps are complete trees.
- **Perfect** — every level completely full, all leaves at the same depth.

## Counting nodes and levels

Level `i` of a perfect tree holds **2ⁱ** nodes — each level doubles, because each node has two children.

```
level 0:  1 node      2⁰ = 1      running total 1
level 1:  2 nodes     2¹ = 2      running total 3
level 2:  4 nodes     2² = 4      running total 7
level 3:  8 nodes     2³ = 8      running total 15
```

A perfect tree with `L` levels (so height `h = L - 1` in edges) holds

```
n = 2⁰ + 2¹ + ... + 2^(L-1) = 2^L − 1 = 2^(h+1) − 1
```

Two facts fall straight out of that geometric sum, and both are worth remembering:

**The last level holds more nodes than all the levels above it combined.** 8 > 1+2+4. So roughly **half of all nodes in a balanced tree are leaves**. That is why algorithms that do work only at leaves are not cheaper than ones that touch everything.

**Inverting the formula gives the height.** Solve `n = 2^L − 1` for `L`:

```
L = log₂(n + 1)          levels
h = log₂(n + 1) − 1      height in edges
```

With `n = 1,000,000` nodes, a balanced tree is about 20 levels deep. That is the entire appeal of trees: a million items, twenty comparisons.

For a tree that is merely *balanced* rather than perfect, the levels aren't exactly full, so the relationship becomes bounds rather than an equality: a tree of height `h` holds between `h + 1` nodes (a single chain) and `2^(h+1) − 1` nodes (perfect). Inverted: a tree of `n` nodes has height somewhere between `⌊log₂ n⌋` and `n − 1`.

## Why height is log n — and when it isn't

Each step down the tree ideally halves the number of nodes still under consideration. Halving `n` repeatedly until one node remains takes `log₂ n` steps, by definition of the logarithm.

But nothing in the definition of "binary tree" enforces that halving. Insert 1, 2, 3, 4, 5 into a plain BST in that order:

```
1
 \
  2
   \
    3
     \
      4
       \
        5
```

Height `n − 1`. This is a linked list wearing a tree costume, and every operation on it is O(n). **O(log n) is a property of balance, not of being a tree.** Self-balancing variants (AVL, red-black) do extra rotation work on insert and delete specifically to keep the height at O(log n); a raw binary tree gives no such guarantee.

That is the answer to "why is the complexity log n" — it is log n *because* the height is log n, and the height is log n *only* when the tree is balanced.

## Complexity

| Operation | Balanced | Worst case (skewed) |
|---|---|---|
| Search / insert / delete in a BST | O(log n) | O(n) |
| Full traversal (any order) | O(n) | O(n) |
| Recursion stack space | O(log n) | O(n) |
| BFS queue space | O(n) — last level is ~n/2 | O(1) |

Two different rules produce these numbers, and mixing them up is the usual source of wrong analysis:

- **Anything that walks a single root-to-leaf path** — BST search, insert, delete — is O(h), which is O(log n) when balanced.
- **Anything that must look at every node** — traversals, computing height, summing values, checking validity — is O(n) regardless of shape. You cannot beat O(n) when the answer depends on every node.

For recursive tree code the cost is mechanical:

> **total = (number of nodes visited) × (work done per node)**

Most tree recursion does O(1) per node, giving O(n). It stops being O(n) the moment the per-node work isn't constant — concatenating lists, copying a path, or scanning a subtree inside the recursion makes it O(n²) or worse, even though the code still "just recurses once per node".

Space is the recursion stack, which is the tree's *height*, not its node count — O(log n) balanced, O(n) for a degenerate tree, which is a real stack-overflow risk on large skewed inputs.

## Traversals

### Depth-first: three orders, one line of difference

The names refer to when the *node itself* is handled relative to its children.

```
        1
      /   \
     2     3
    / \
   4   5
```

```python
def inorder(node):
    if not node: return
    inorder(node.left)
    visit(node)              # move this line to change the order
    inorder(node.right)
```

| Order | Position of `visit` | Result above | Typical use |
|---|---|---|---|
| Pre-order | before both | 1 2 4 5 3 | copying/serialising a tree — root first, so it can be rebuilt |
| In-order | between | 4 2 5 1 3 | **on a BST, yields sorted order** |
| Post-order | after both | 4 5 2 3 1 | deleting/freeing, or any value computed from children first |

In-order on a BST being sorted is not a coincidence: the BST invariant says everything left of a node is smaller and everything right is larger, so "left, self, right" is exactly ascending order. Half the BST problems on LeetCode are an in-order traversal with a bit of state carried along.

Post-order is the shape to reach for whenever a node's answer depends on its subtrees — height, diameter, "is this subtree balanced", subtree sums. Compute both children, then combine:

```python
def height(node):
    if not node: return -1
    return 1 + max(height(node.left), height(node.right))
```

### Breadth-first: level by level

Use a queue, and capture its length before each level so you know where the level ends.

```python
from collections import deque

def levels(root):
    if not root: return []
    out, q = [], deque([root])
    while q:
        level = []
        for _ in range(len(q)):      # exactly the current level
            node = q.popleft()
            level.append(node.val)
            if node.left:  q.append(node.left)
            if node.right: q.append(node.right)
        out.append(level)
    return out
```

Use BFS when the answer depends on depth — minimum depth, right-side view, level averages, "first node satisfying X, shallowest". Use DFS when it depends on subtree structure. BFS costs O(n) space because the queue holds a whole level, and the widest level is about half the tree.

## The array trick

A complete binary tree needs no pointers at all. Store it in an array and derive the relationships arithmetically:

```
index:    0    1    2    3    4    5    6
        [ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ]

left(i)   = 2i + 1
right(i)  = 2i + 2
parent(i) = (i − 1) // 2
```

This is how binary heaps are implemented: contiguous memory, no allocation per node, cache-friendly. It only works for *complete* trees — a sparse tree wastes an exponential amount of space in this layout.

## Recurring problem shapes

- **"Compute something about every subtree."** Post-order returning a value up. If you need to return two things (say, a height *and* a boolean), return a tuple rather than recomputing in a second pass — recomputing height inside a recursion is the classic accidental O(n²).
- **"Validate a BST."** Checking `left < node < right` locally is wrong; a node deep in the left subtree can still be larger than the root. Pass down an allowed `(min, max)` range, or do an in-order traversal and check it is strictly increasing.
- **"Path from root."** Pre-order, pushing onto a list on the way down and popping on the way back up.
- **"Path that may bend."** Diameter, maximum path sum. Each node returns the best *straight downward* path to its parent, while separately updating a global best that may pass *through* the node. These are two different quantities, and conflating them is the usual bug.
- **"Lowest common ancestor."** In a BST, walk down while both targets sit on the same side. In a general tree, recurse; a node whose two subtrees each return a hit is the answer.

## Pitfalls

- Forgetting the `None` base case, or checking the child instead of the node — check `if not node: return` at the top and let the recursion handle leaves naturally.
- Confusing height and depth, or edges and nodes. State the convention before writing the code.
- Assuming a BST is balanced. Unless the problem says AVL, red-black, or "balanced", the worst case is O(n).
- Recursing on deep skewed trees in a language without tail-call elimination — O(n) stack frames will overflow. Convert to an explicit stack if `n` is large.
- Counting nodes by formula on a tree that is not perfect. `2^h − 1` is an upper bound for a general tree, not its size.
