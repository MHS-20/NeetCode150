#include "tree_node.h"

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p,
                                      struct TreeNode *q) {
  int lo = p->val < q->val ? p->val : q->val;
  int hi = p->val < q->val ? q->val : p->val;

  // the LCA is the first node whose value falls between p and q
  while (root) {
    if (root->val < lo)
      root = root->right;
    else if (root->val > hi)
      root = root->left;
    else
      return root;
  }

  return NULL;
}
