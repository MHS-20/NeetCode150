#include "tree_node.h"
#include <climits>

class Solution {
public:
  bool isValidBST(TreeNode *root) { return dfs(root, LONG_MIN, LONG_MAX); }

  bool dfs(TreeNode *root, long lowerbound, long upperbound) {
    if (!root)
      return true;

    if (root->val <= lowerbound || root->val >= upperbound)
      return false;

    return dfs(root->right, root->val, upperbound) &&
           dfs(root->left, lowerbound, root->val);
  }
};
