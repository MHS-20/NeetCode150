#include "tree_node.h"

class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    if (!root)
      return nullptr;

    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    invertTree(root->left);
    invertTree(root->right);

    return root;
  }
};
