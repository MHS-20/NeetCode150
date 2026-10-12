#include "tree_node.h"

static int height(struct TreeNode *node, int *best) {
  if (!node)
    return 0;

  int l = height(node->left, best);
  int r = height(node->right, best);

  if (l + r > *best)
    *best = l + r;
  return 1 + (l > r ? l : r);
}

int diameterOfBinaryTree(struct TreeNode *root) {
  int best = 0;
  height(root, &best);
  return best;
}
