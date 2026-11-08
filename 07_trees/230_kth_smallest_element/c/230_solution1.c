#include "tree_node.h"

static void dfs(struct TreeNode *root, int *idx, int *res) {
  if (!root || *idx == 0)
    return;

  dfs(root->left, idx, res);
  if (*idx == 0)
    return; // answer found in the left subtree
  (*idx)--;

  if (*idx == 0) {
    *res = root->val;
    return;
  }

  dfs(root->right, idx, res);
}

int kthSmallest(struct TreeNode *root, int k) {
  int res = 0;
  dfs(root, &k, &res);
  return res;
}
