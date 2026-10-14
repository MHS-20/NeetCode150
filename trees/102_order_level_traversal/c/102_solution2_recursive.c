#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 2000 // constraint: number of nodes is in [0, 2000]

static void dfs(struct TreeNode *node, int depth, int **res, int *sizes, int *levels) {
  if (!node)
    return;

  // first visit of a new depth: allocate its row
  if (depth == *levels) {
    res[depth] = malloc(MAX_NODES * sizeof(int));
    sizes[depth] = 0;
    (*levels)++;
  }

  res[depth][sizes[depth]++] = node->val;

  dfs(node->left, depth + 1, res, sizes, levels);
  dfs(node->right, depth + 1, res, sizes, levels);
}

// returns an array of levels; sets *returnSize to the level count and
// (*returnColumnSizes)[i] to the size of level i
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
  int **res = malloc(MAX_NODES * sizeof(int *));
  *returnColumnSizes = malloc(MAX_NODES * sizeof(int));
  *returnSize = 0;

  dfs(root, 0, res, *returnColumnSizes, returnSize);
  return res;
}
