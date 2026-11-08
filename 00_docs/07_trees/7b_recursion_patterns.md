# Recursion on Trees: Passing Information Down and Up

A recursive tree function can move information in two directions. It can pass a value **down**, as an argument from a node to its children, or pass a value **up**, as a return value from the children to the node. Most tree problems use one of the two, and a few use both at once. Deciding which values go down and which come up is most of the work in writing the function.

The examples follow the C++ solutions in `07_trees/`. Every trace was produced by running the same steps on the input shown. Heights are counted in nodes, as in the repo: an empty tree has height 0 ([terms](7a_basics_and_traversals.md#counting-height-in-nodes-or-in-edges)).

## Passing information down

When a node's answer depends on its **ancestors**, the function takes the needed information as an argument and passes an updated copy to each child. This is a preorder traversal: the node is handled before its children.

### Count Good Nodes in Binary Tree (1448)

A node is **good** if no node on the path from the root to it has a larger value. Each node needs one fact about its ancestors: the largest value on the path so far.

```cpp
void dfs(TreeNode *node, int max, int &count) {
    if (!node) return;
    if (node->val >= max) {
        count++;
        max = node->val;
    }
    dfs(node->left, max, count);
    dfs(node->right, max, count);
}
```

`max` is passed **by value**. Each child receives its own copy, so a larger value found in the left subtree does not affect the right subtree. `count` is passed by reference, because it is one total shared by the whole tree.

On this tree:

```
        3
       / \
      1   4
     /   / \
    3   1   5
```

```
path         max on the path before this node   good?
3            (none)                              yes, max becomes 3
3, 1         3                                   no
3, 1, 3      3                                   yes (3 >= 3)
3, 4         3                                   yes, max becomes 4
3, 4, 1      4                                   no
3, 4, 5      4                                   yes, max becomes 5
```

The answer is 4. The repo's second solution does the same with an explicit stack of `(node, maxSoFar)` pairs, which carries the value down in the pair instead of in an argument.

## Passing information up

When a node's answer depends on its **subtrees**, the function returns a value, and each node combines the values returned by its two children. This is a postorder traversal: the node is handled after its children.

### Maximum Depth of Binary Tree (104)

```cpp
int maxDepth(TreeNode *node) {
    if (!node) return 0;
    return 1 + max(maxDepth(node->left), maxDepth(node->right));
}
```

The depth of a tree is one more than the depth of its deeper subtree. An empty tree has depth 0.

### Same Tree (100) and Subtree of Another Tree (572)

Two trees are the same if their roots have equal values and their left subtrees and right subtrees are the same. Each call returns a `bool` up:

```cpp
bool isSameTree(TreeNode *p, TreeNode *q) {
    if (!p && !q) return true;          // both empty
    if (!p || !q) return false;         // only one is empty
    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}
```

The two null checks must come in this order. After the first, at least one of the two is non-null, so the second catches the case where only one is.

Subtree of Another Tree (572) asks whether `subRoot` equals the subtree starting at some node of `root`. It tries `isSameTree` at every node of `root`. With `m` nodes in `root` and `n` in `subRoot`, that costs O(m · n) in the worst case.

### Balanced Binary Tree (110): a special return value

A tree is balanced if, at every node, the heights of the two subtrees differ by at most 1.

A direct solution checks each node by calling a separate height function on both of its children. The height function visits the whole subtree, so on a skewed tree this costs O(n²).

The repo's solution computes heights once, from the bottom up, and returns **-1** to mean "this subtree is not balanced". A real height is never negative, so -1 cannot be mistaken for one:

```cpp
int height(TreeNode *node) {
    if (!node) return 0;
    int l = height(node->left);
    if (l == -1) return -1;              // left subtree already unbalanced
    int r = height(node->right);
    if (r == -1) return -1;
    if (abs(l - r) > 1) return -1;       // this node is unbalanced
    return 1 + max(l, r);
}
```

On this tree:

```
          1
         / \
        2   2
       / \
      3   3
     / \
    4   4
```

```
node             left height   right height   returns
4 (each)              0             0            1
3 (left)              1             1            2
3 (right)             0             0            1
2 (left)              2             1            3
2 (right)             0             0            1
1                     3             1           -1    difference is 2
```

The tree is not balanced. Each node is visited once, so the solution is O(n).

The -1 also stops early: once a subtree returns -1, its parent returns -1 straight away, without visiting its other subtree.

## Passing up one value and recording another

Some problems ask about a **path** that may bend at a node: it goes up from one subtree, through the node, and down into the other. A parent cannot extend a bent path, because the path already uses both of the node's children. So the function computes two different values at each node:

- **What it returns:** the best path that starts at this node and goes **straight down** one side. The parent can extend this path.
- **What it records:** the best path that **bends** at this node, using both sides. This is a candidate for the final answer, stored in a variable outside the recursion.

Returning the bent path instead of the straight one is the usual mistake. The parent would extend a path that already uses both children of the node, which is not a valid path.

### Diameter of Binary Tree (543)

The diameter is the number of edges on the longest path between any two nodes. A path that bends at a node goes down `l` edges into the left subtree and `r` into the right, where `l` and `r` are the heights of the two subtrees, so it has `l + r` edges.

```cpp
int height(TreeNode *node, int &best) {
    if (!node) return 0;
    int l = height(node->left, best);
    int r = height(node->right, best);
    best = max(best, l + r);         // record: the path bending here
    return 1 + max(l, r);            // return: the straight path, for the parent
}
```

On this tree:

```
        1
       / \
      2   3
     / \
    4   5
```

```
node   l   r   bends here (l + r)   returns 1 + max(l, r)   best
 4     0   0          0                     1                 0
 5     0   0          0                     1                 0
 2     1   1          2                     2                 2
 3     0   0          0                     1                 2
 1     2   1          3                     3                 3
```

The answer is 3, the path 4 → 2 → 1 → 3 (or 5 → 2 → 1 → 3).

The longest path does not have to pass through the root. If the root had only a left child, the best path could bend at a node far below it. Recording the best at **every** node covers that case.

### Binary Tree Maximum Path Sum (124)

The same structure, with sums instead of lengths. Values can be negative, so a subtree whose best straight path has a negative sum is left out, by treating it as 0:

```cpp
int dfs(TreeNode *node, int &mx) {
    if (!node) return 0;
    int l = max(0, dfs(node->left, mx));    // drop a negative branch
    int r = max(0, dfs(node->right, mx));
    mx = max(mx, l + r + node->val);        // record: the path bending here
    return max(l, r) + node->val;           // return: the straight path
}
```

`mx` starts at `INT_MIN`, not 0. If every value is negative, the answer is the largest single value, which is below 0.

On this tree:

```
      -10
      /  \
     9    20
         /  \
        15   7
```

```
node   l    r    bends here     returns          best
  9    0    0    9              9                  9
 15    0    0    15             15                15
  7    0    0    7              7                 15
 20   15    7    15+7+20 = 42   15+20 = 35        42
-10    9   35    9+35-10 = 34   35-10 = 25        42
```

The answer is 42, the path 15 → 20 → 7. It does not include the root. At node 20 the function records 42, the bent path, but returns 35, the straight path 15 → 20, because that is the most the root could extend.
