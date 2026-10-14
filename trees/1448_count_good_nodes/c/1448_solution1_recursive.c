#include "tree_node.h"
#include <limits.h>

static void dfs(struct TreeNode *root, int max, int *count) {
  if (!root)
    return;
  if (root->val >= max) {
    (*count)++;
    max = root->val;
  }
  dfs(root->left, max, count);
  dfs(root->right, max, count);
}

int goodNodes(struct TreeNode *root) {
  int count = 0;
  dfs(root, INT_MIN, &count);
  return count;
}
