#include "tree_node.h"
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
  int maxPathSum(TreeNode *root) {
    int mx = INT_MIN;
    dfs(root, mx);
    return mx;
  }

  int dfs(TreeNode *root, int &mx) {
    if (!root)
      return 0;

    int l = max(0, dfs(root->left, mx));
    int r = max(0, dfs(root->right, mx));

    mx = max(mx, l + r + root->val);
    return max(l, r) + root->val;
  }
};
