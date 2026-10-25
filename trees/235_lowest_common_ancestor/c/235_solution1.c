#include "tree_node.h"

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p,
                                      struct TreeNode *q) {
  if (p->val > q->val)
    return lowestCommonAncestor(root, q, p);

  while (root) {
    if (root->val >= p->val && root->val <= q->val)
      return root;

    if (root->val < p->val)
      root = root->right;
    else
      root = root->left;
  }

  return root;
}
