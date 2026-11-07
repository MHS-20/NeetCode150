#include "tree_node.h"

static int find_depth(struct TreeNode *root, int count) {
  if (!root)
    return count;

  int l = find_depth(root->left, count + 1);
  int r = find_depth(root->right, count + 1);
  return l > r ? l : r;
}

int maxDepth(struct TreeNode *root) { return find_depth(root, 0); }
