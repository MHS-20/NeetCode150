#include "tree_node.h"
#include <limits.h>

static int max(int a, int b) { return a > b ? a : b; }

static int dfs(struct TreeNode *root, int *mx) {
  if (!root)
    return 0;

  int l = max(0, dfs(root->left, mx));
  int r = max(0, dfs(root->right, mx));

  *mx = max(*mx, l + r + root->val);
  return max(l, r) + root->val;
}

int maxPathSum(struct TreeNode *root) {
  int mx = INT_MIN;
  dfs(root, &mx);
  return mx;
}
