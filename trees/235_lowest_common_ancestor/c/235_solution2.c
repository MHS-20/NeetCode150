#include "tree_node.h"

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p,
                                      struct TreeNode *q) {
  if (p->val > q->val)
    return lowestCommonAncestor(root, q, p);

  if (root->val >= p->val && root->val <= q->val)
    return root;

  if (q->val < root->val)
    return lowestCommonAncestor(root->left, p, q);
  else
    return lowestCommonAncestor(root->right, p, q);
}
