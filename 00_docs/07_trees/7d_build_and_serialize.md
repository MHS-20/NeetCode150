# Building a Tree from Traversals, and Serialising It

A traversal turns a tree into a sequence. These two problems go the other way: they rebuild the tree from sequences. One traversal alone does not identify a tree, because different trees can give the same sequence. Two traversals together can identify it, and so can one traversal that also records where the empty children are.

The examples follow the C++ solutions in `07_trees/`. Every trace was produced by running the same steps on the input shown. Traversal orders are defined in [traversals](7a_basics_and_traversals.md#depth-first-traversals).

## Why one traversal is not enough

These two trees have the same preorder sequence, `1 2`:

```
    1            1
   /              \
  2                2
```

The sequence shows that 2 comes after 1, but not whether 2 is the left or the right child. A second sequence, or a marker for each empty child, supplies the missing information.

## Construct Binary Tree from Preorder and Inorder Traversal (105)

The task: rebuild a tree with distinct values from its preorder and inorder sequences.

Each sequence gives one piece of information:

- **Preorder** lists a node before its subtrees, so the **first** value of a subtree's preorder is that subtree's root.
- **Inorder** lists the left subtree, then the root, then the right subtree. Once the root's position in the inorder sequence is known, everything to its left is the left subtree and everything to its right is the right subtree.

### The recursion

The solution keeps one index `preIdx` into the preorder sequence, shared by all calls. Each call builds the subtree whose values occupy the inorder range `[inLo, inHi]`:

1. Take the next preorder value as the root, and advance `preIdx`.
2. Find the root's position `mid` in the inorder sequence.
3. Build the left subtree from the inorder range `[inLo, mid - 1]`.
4. Build the right subtree from `[mid + 1, inHi]`.

```cpp
TreeNode *build(vector<int> &preorder, int &preIdx, int inLo, int inHi,
                unordered_map<int, int> &inIndex) {
    if (inLo > inHi) return nullptr;            // empty range: no node
    int rootVal = preorder[preIdx++];
    int mid = inIndex[rootVal];
    TreeNode *cur = new TreeNode(rootVal);
    cur->left = build(preorder, preIdx, inLo, mid - 1, inIndex);
    cur->right = build(preorder, preIdx, mid + 1, inHi, inIndex);
    return cur;
}
```

The left subtree has to be built before the right one. Preorder lists the whole left subtree before the right subtree, so when the left call returns, `preIdx` points at the root of the right subtree.

`inIndex` is a hash map from each value to its position in the inorder sequence, built once before the recursion. Without it, step 2 would search the inorder sequence at every node, costing O(n) per node and O(n²) in total. With it, each node costs O(1) and the whole build is O(n).

### Trace

`preorder = [3, 9, 20, 15, 7]`, `inorder = [9, 3, 15, 20, 7]`:

```
root   inorder range   position of root   left range   right range
 3       [0, 4]               1             [0, 0]        [2, 4]
 9       [0, 0]               0             empty         empty
20       [2, 4]               3             [2, 2]        [4, 4]
15       [2, 2]               2             empty         empty
 7       [4, 4]               4             empty         empty
```

The roots are taken in preorder order: 3, 9, 20, 15, 7. The result is:

```
      3
     / \
    9   20
       /  \
      15   7
```

## Serialize and Deserialize Binary Tree (297)

The task: turn a tree into a string, and the string back into the same tree.

### Serialising: preorder with null markers

Preorder alone loses the shape, as shown above. Writing a marker for every **empty child** puts the shape back: the string then says where each subtree ends. The repo's solution writes each value followed by `#`, and `N#` for each null:

```cpp
void serDfs(TreeNode *node, string &ser) {
    if (!node) {
        ser += "N#";
        return;
    }
    ser += to_string(node->val) + "#";
    serDfs(node->left, ser);
    serDfs(node->right, ser);
}
```

For this tree:

```
    1
   / \
  2   3
     / \
    4   5
```

the string is:

```
1#2#N#N#3#4#N#N#5#N#N#
```

Node 2 is followed by `N#N#`, its two empty children. Every leaf is followed by two `N` markers, so a tree with `n` nodes has `n + 1` of them.

The `#` separator is needed because values can have more than one digit, or a minus sign. Without it, `1` followed by `23` could not be told apart from `12` followed by `3`.

### Deserialising: the same preorder, reading tokens

The reader walks the string in the same preorder. A shared position `pos` moves forward one token at a time:

```cpp
TreeNode *desDfs(const string &data, int &pos) {
    int end = data.find('#', pos);
    string tok = data.substr(pos, end - pos);
    pos = end + 1;                         // move past this token
    if (tok == "N") return nullptr;
    TreeNode *root = new TreeNode(stoi(tok));
    root->left = desDfs(data, pos);        // reads the whole left subtree
    root->right = desDfs(data, pos);       // continues after it
    return root;
}
```

Reading `1#2#N#N#3#4#N#N#5#N#N#`:

```
token   action
1       create 1, read its left subtree
2       create 2 as 1's left, read its left subtree
N       2's left is null
N       2's right is null; 2 is done, back to 1
3       create 3 as 1's right, read its left subtree
4       create 4 as 3's left
N, N    4 has no children
5       create 5 as 3's right
N, N    5 has no children; the string is used up
```

Each `N` ends one branch of the recursion, which is how the reader knows where each subtree stops. Both directions visit each node once, so serialising and deserialising are O(n).
