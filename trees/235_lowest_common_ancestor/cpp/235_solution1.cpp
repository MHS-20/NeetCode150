#include "tree_node.h"

class Solution {
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (p->val > q->val)
      return lowestCommonAncestor(root, q, p);

    while (root) {
      if (root->val >= p->val && root->val <= q->val)
        return root;

      if (root->val < p->val)
        root = root->right;
      else if (root->val > q->val)
        root = root->left;
    }

    return root;
  }
};
