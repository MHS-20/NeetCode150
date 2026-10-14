#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 100 // constraint: number of nodes is in [0, 100]

// visit right first, so the first node seen at each depth is the rightmost
static void dfs(struct TreeNode *node, int depth, int *res, int *size) {
  if (!node)
    return;

  if (depth == *size)
    res[(*size)++] = node->val;

  dfs(node->right, depth + 1, res, size);
  dfs(node->left, depth + 1, res, size);
}

// returns the rightmost value of each level; sets *returnSize to the level count
int *rightSideView(struct TreeNode *root, int *returnSize) {
  int *res = malloc(MAX_NODES * sizeof(int));
  *returnSize = 0;
  dfs(root, 0, res, returnSize);
  return res;
}
