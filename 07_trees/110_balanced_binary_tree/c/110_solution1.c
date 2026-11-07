#include "tree_node.h"
#include <stdbool.h>
#include <stdlib.h>

// returns the subtree height, or -1 as soon as any subtree is unbalanced
static int height(struct TreeNode *node) {
  if (!node)
    return 0;

  int l = height(node->left);
  if (l == -1)
    return -1;

  int r = height(node->right);
  if (r == -1)
    return -1;

  if (abs(l - r) > 1)
    return -1;

  return 1 + (l > r ? l : r);
}

bool isBalanced(struct TreeNode *root) { return height(root) != -1; }
