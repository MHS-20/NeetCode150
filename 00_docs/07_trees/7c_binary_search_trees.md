# Binary Search Trees

A **binary search tree** (BST) is a binary tree with an ordering rule: for every node, all values in its left subtree are smaller than the node's value, and all values in its right subtree are larger. The rule lets a search follow one path from the root instead of visiting every node, so it costs O(height). It also means an inorder traversal lists the values in sorted order. Every problem on this page uses one of these two consequences.

The examples follow the C++ solutions in `07_trees/`. Every trace was produced by running the same steps on the input shown. LeetCode's BST problems assume distinct values, and so does this page.

## The ordering rule applies to whole subtrees

The rule is about **all** nodes in each subtree, not only a node's two children. This tree satisfies "left child smaller, right child larger" at every node, but it is not a BST:

```
        5
       / \
      4   6
         / \
        3   7
```

Node 3 is in the right subtree of 5, so it must be larger than 5. It is smaller.

## Searching

To find a value `x`, start at the root. If `x` is smaller than the node, go left. If larger, go right. The ordering rule guarantees that `x` cannot be in the other subtree, so each step rules out a whole subtree. The search follows one path, which costs O(height): O(log n) for a balanced tree and O(n) for a skewed one ([height](7a_basics_and_traversals.md#when-the-height-is-not-log-n)).

## Validate Binary Search Tree (98)

The task: decide whether a tree is a BST.

Checking each node against its two children is not enough, as the tree above shows. The check at node 6 compares it with 3 and 7 and passes. The problem is between 3 and the root 5, two levels up.

### Passing down an allowed range

Each node has a range of values it is allowed to hold, set by its ancestors. The root may hold any value. Going **left** from a node with value `v` sets the upper bound to `v`, since everything in the left subtree must be smaller. Going **right** sets the lower bound to `v`. The bounds are passed down, as in [passing information down](7b_recursion_patterns.md#passing-information-down):

```cpp
bool dfs(TreeNode *node, long lower, long upper) {
    if (!node) return true;
    if (node->val <= lower || node->val >= upper)
        return false;
    return dfs(node->right, node->val, upper) &&
           dfs(node->left, lower, node->val);
}
// called as dfs(root, LONG_MIN, LONG_MAX)
```

On the tree above:

```
node   allowed range      in range?
  5    (-inf, +inf)       yes
  6    (5, +inf)          yes
  7    (6, +inf)          yes
  3    (5, 6)             no: 3 is not greater than 5
```

The solution returns false at node 3. Node 4 is never checked, because `&&` stops at the first false.

The starting bounds are `LONG_MIN` and `LONG_MAX`, not `INT_MIN` and `INT_MAX`. A node can hold the value `INT_MAX`, and with `INT_MAX` as the upper bound, the test `node->val >= upper` would reject that valid node. The 64-bit bounds lie outside every possible `int` value. Pointers to the bounding nodes, with null meaning "no bound", work as well.

### Checking the inorder sequence instead

A tree is a BST exactly when its inorder traversal is strictly increasing. Another solution traverses inorder and checks that each value is larger than the previous one. On the tree above, inorder gives `4, 5, 3, 6, 7`, and 3 after 5 shows the tree is not a BST. Both solutions are O(n).

## Kth Smallest Element in a BST (230)

The task: find the `k`th smallest value.

Inorder traversal visits the values in increasing order, so the answer is the `k`th node visited. The solution counts down `k` during an inorder traversal and stops when it reaches 0:

```cpp
void dfs(TreeNode *node, int &k, int &res) {
    if (!node || k == 0) return;
    dfs(node->left, k, res);
    if (k == 0) return;               // answer found in the left subtree
    k--;                              // node is visited here, in sorted order
    if (k == 0) {
        res = node->val;
        return;
    }
    dfs(node->right, k, res);
}
```

`k` is passed by reference so that every call shares one counter.

On this tree with `k = 3`:

```
          5
         /         3   6
       /       2   4
     /
    1
```

Inorder visits 1, 2, 3, 4, 5, 6. The counter goes 2, 1, 0 at nodes 1, 2 and 3, and `res` is set to 3. The call for node 3 returns to node 5, which finds `k == 0` right after its left call and returns too. Nodes 4, 5 and 6 are never counted.

The check after the left call is what stops the traversal. Without it, node 5 would run `k--` after the answer was found, `k` would become -1, and the `k == 0` check at the top would never stop anything again: the traversal would go on through node 6 with `k = -2`. The answer would still be 3, because `res` is only set when `k` is exactly 0, but every remaining node would be visited.

With the check, the cost is O(height + k): the traversal walks down to the smallest value, then visits `k` nodes.

## Lowest Common Ancestor of a BST (235)

The **lowest common ancestor** (LCA) of two nodes `p` and `q` is the deepest node that has both of them in its subtree. A node counts as being in its own subtree, so if `p` is an ancestor of `q`, the answer is `p`.

In a BST, the values decide which side each node is on. Starting from the root, with `p` the smaller of the two:

- If the current node is **smaller than both**, both are in its right subtree. Go right.
- If it is **larger than both**, both are in its left subtree. Go left.
- Otherwise `p <= node <= q`. Either the two are on different sides, or one of them is the current node. Either way, no deeper node has both in its subtree, so the current node is the answer.

```cpp
if (p->val > q->val) swap(p, q);       // make p the smaller one
while (root) {
    if (root->val >= p->val && root->val <= q->val)
        return root;
    root = (root->val < p->val) ? root->right : root->left;
}
```

The repo's solution swaps by calling itself with `q` and `p` exchanged. Its second solution is the recursive form of the same walk.

On this tree:

```
            6
          /   \
         2     8
        / \   / \
       0   4 7   9
          / \
         3   5
```

| p, q | path | answer | why |
|---|---|---|---|
| 2, 8 | 6 | 6 | 2 < 6 < 8: the two are on different sides of 6 |
| 2, 4 | 6, 2 | 2 | both smaller than 6, go left; at 2, p is the node itself |
| 3, 5 | 6, 2, 4 | 4 | left at 6, right at 2, and 3 < 4 < 5 |

The walk follows one path, so it costs O(height) and O(1) extra space. In a general binary tree the values give no direction. There, the LCA is found with a postorder traversal that returns whether `p` or `q` was found in each subtree.
