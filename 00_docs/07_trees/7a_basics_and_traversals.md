# Binary Trees: Terms, Height and Traversals

A binary tree problem almost always visits the nodes in one of four orders: preorder, inorder, postorder or level by level. Choosing the order is most of the design. The order decides whether a node is handled before or after its children, and so whether information flows down from the root or up from the leaves. The cost of most tree operations depends on the tree's height, which ranges from about `log₂ n` to `n - 1` depending on its shape.

The examples follow the C++ solutions in `07_trees/`. Every trace was produced by running the same steps on the input shown.

## Terms

A binary tree is a set of nodes in which each node holds a value and has up to two children, `left` and `right`. One node, the **root**, has no parent. Every other node has exactly one parent.

```
            1          ← depth 0
          /   \
         2     3       ← depth 1
        / \     \
       4   5     6     ← depth 2
```

- **Leaf:** a node with no children. Here, 4, 5 and 6.
- **Depth of a node:** the number of edges from the root down to it. Node 4 has depth 2.
- **Height of a node:** the number of edges on the longest path from it down to a leaf. The height of the tree is the height of its root, 2 here.
- **Level `i`:** all nodes at depth `i`.

### Counting height in nodes or in edges

Height can be counted in edges, as above, or in nodes. The two differ by one. Counted in edges, a single node has height 0 and an empty tree has height -1. Counted in nodes, a single node has height 1 and an empty tree has height 0.

The repo's solutions count in **nodes**: `height(nullptr)` returns 0 in Balanced Binary Tree (110) and Diameter (543), and Maximum Depth (104) returns 3 for the tree above. Mixing the two counts in one solution gives answers that are off by one.

### Two named shapes

- **Complete:** every level is full except possibly the last, which is filled from the left. Binary heaps are complete trees.
- **Perfect:** every level is full, so all leaves are at the same depth.

## How many nodes fit in a given height

In a perfect tree, each level has twice as many nodes as the level above, because each node has two children:

```
level 0:  1 node       total 1
level 1:  2 nodes      total 3
level 2:  4 nodes      total 7
level 3:  8 nodes      total 15
```

A perfect tree with `L` levels holds `1 + 2 + 4 + … + 2^(L-1) = 2^L - 1` nodes. Two facts follow:

- **The last level holds more than half the nodes.** 8 is more than `1 + 2 + 4 = 7`. In a balanced tree about half the nodes are leaves.
- **The number of levels is about `log₂ n`.** Solving `n = 2^L - 1` for `L` gives `L = log₂(n + 1)`. A perfect tree with 1 048 575 nodes has 20 levels.

### When the height is not `log n`

Nothing in the definition of a binary tree keeps it balanced. Inserting 1, 2, 3, 4, 5 in that order into a binary search tree ([BST](7c_binary_search_trees.md)) without rebalancing puts each new value to the right of the last:

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

This tree has height `n - 1` in edges, and searching it takes O(n), as in a linked list. Balanced trees such as AVL and red-black trees do extra work on insert and delete to keep the height at O(log n). A plain binary tree has no such guarantee. Unless a problem says the tree is balanced, the worst-case height is `n - 1`.

## What tree operations cost

| Operation | Balanced tree | Skewed tree |
|---|---|---|
| search, insert or delete in a BST | O(log n) | O(n) |
| visit every node | O(n) | O(n) |
| recursion stack | O(log n) | O(n) |
| BFS queue | O(n): the last level holds about n/2 nodes | O(1) |

- **Following one path from the root down**, as BST search does, costs O(height).
- **Visiting every node**, as traversals, height and validity checks do, costs O(n) whatever the shape.

For recursive tree code, the total cost is the number of nodes visited times the work done at each node. Most solutions do O(1) work per node, so they are O(n). Doing O(n) work at each node, for example calling a separate height function from every node, makes the solution O(n²) even though it still recurses once per node. Balanced Binary Tree (110) avoids this in [recursion patterns](7b_recursion_patterns.md#balanced-binary-tree-110-a-special-return-value).

The recursion stack holds one frame per level of the current path, so its size is the height of the tree, not the number of nodes. On a skewed tree with 100 000 nodes, a recursive solution makes 100 000 nested calls, which can overflow the stack. An explicit stack, shown below, avoids this.

## Depth-first traversals

A depth-first traversal goes down one branch to the bottom before moving to the next. The three orders differ only in when the node itself is handled, relative to its two subtrees:

```cpp
void traverse(TreeNode *node) {
    if (!node) return;
    // preorder: handle node here
    traverse(node->left);
    // inorder: handle node here
    traverse(node->right);
    // postorder: handle node here
}
```

On this tree:

```
        1
      /   \
     2     3
    / \
   4   5
```

| Order | Node handled | Result | Used for |
|---|---|---|---|
| preorder | before both subtrees | 1 2 4 5 3 | passing information down; copying or serialising a tree |
| inorder | between the subtrees | 4 2 5 1 3 | visiting a BST in sorted order |
| postorder | after both subtrees | 4 5 2 3 1 | combining results from the children; freeing a tree |

Inorder gives sorted order on a BST because every value in the left subtree is smaller than the node and every value in the right subtree is larger, so "left, node, right" lists them in increasing order. Kth Smallest Element in a BST (230) uses this ([BST](7c_binary_search_trees.md#kth-smallest-element-in-a-bst-230)).

### Iterative traversals with an explicit stack

Recursion uses the call stack to remember which nodes still have work left. An explicit stack does the same job in a loop.

**Preorder** is the simplest: pop a node, handle it, push its children. Invert Binary Tree (226) uses this form in its third solution: it pops a node, swaps its children, and pushes them.

```cpp
stack<TreeNode *> st;
if (root) st.push(root);
while (!st.empty()) {
    TreeNode *cur = st.top();
    st.pop();
    swap(cur->left, cur->right);   // handle the node
    if (cur->left)  st.push(cur->left);
    if (cur->right) st.push(cur->right);
}
```

**Inorder** has to delay each node until its whole left subtree is done. The loop goes as far left as possible, pushing every node on the way. When it can go no further, it pops a node, handles it, and moves to that node's right subtree:

```cpp
stack<TreeNode *> st;
TreeNode *cur = root;
while (cur || !st.empty()) {
    while (cur) {              // go left, remembering each node
        st.push(cur);
        cur = cur->left;
    }
    cur = st.top();
    st.pop();
    visit(cur);                // the left subtree of cur is finished
    cur = cur->right;
}
```

On the tree above:

```
push 1, 2, 4 (going left)       stack: 1 2 4
pop 4, visit 4                  stack: 1 2       4 has no right child
pop 2, visit 2                  stack: 1         go right to 5
push 5, pop 5, visit 5          stack: 1
pop 1, visit 1                  stack: (empty)   go right to 3
push 3, pop 3, visit 3          stack: (empty)
```

The visits come out as 4, 2, 5, 1, 3, the inorder sequence. The stack never holds more than one path from the root, so its size is at most the height of the tree.

## Breadth-first traversal: level by level

A breadth-first traversal (BFS) visits all nodes at depth 0, then all at depth 1, and so on. It uses a queue. Reading the queue's size before each level tells the loop where the level ends, because at that moment the queue holds exactly that level:

```cpp
queue<TreeNode *> q;
q.push(root);
while (!q.empty()) {
    int sz = q.size();                 // number of nodes on this level
    vector<int> cur;
    for (int i = 0; i < sz; i++) {
        TreeNode *node = q.front();
        q.pop();
        cur.push_back(node->val);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    res.push_back(cur);
}
```

For Binary Tree Level Order Traversal (102) on this tree:

```
      3
     / \
    9   20
       /  \
      15   7
```

```
level   size   values      queue after the level
  0      1     [3]         9, 20
  1      2     [9, 20]     15, 7
  2      2     [15, 7]     (empty)
```

The result is `[[3], [9, 20], [15, 7]]`. Maximum Depth (104) runs the same loop and counts the levels instead of storing them.

BFS suits questions about depth: the shallowest node with some property, or the first or last node on every level. DFS suits questions about subtrees. The BFS queue can hold a whole level, about `n/2` nodes in a balanced tree, so BFS uses O(n) space where recursive DFS uses O(height).

### Binary Tree Right Side View (199), two ways

The task: list the value of the rightmost node on each level.

**With BFS**, the rightmost node on a level is the last one taken from the queue for that level, at `i == sz - 1`.

**With DFS**, the solution visits the right child before the left, and records a node when it is the first node reached at its depth. Because right comes first, the first node reached at each depth is the rightmost one:

```cpp
void dfs(TreeNode *node, int depth, vector<int> &res) {
    if (!node) return;
    if (depth == res.size())          // first node seen at this depth
        res.push_back(node->val);
    dfs(node->right, depth + 1, res);
    dfs(node->left, depth + 1, res);
}
```

On this tree:

```
      1
     / \
    2   3
     \   \
      5   4
```

DFS reaches 1 at depth 0, then 3 at depth 1, then 4 at depth 2, and records each of them. Nodes 2 and 5 are reached later at depths already recorded, so they are skipped. The result is `[1, 3, 4]`.

## Storing a complete tree in an array

A complete tree can be stored in an array with no pointers. The node at index `i` has its children and parent at:

```
index:    0    1    2    3    4    5    6
        [ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ]

left(i)   = 2i + 1
right(i)  = 2i + 2
parent(i) = (i - 1) / 2       (integer division)
```

Binary heaps are stored this way ([heaps](../02_data_structures/2e_heaps_and_priority_queues.md)). The layout only works for complete trees. A tree with gaps would leave empty slots in the array, and a skewed tree of `n` nodes would need about `2^n` slots.
