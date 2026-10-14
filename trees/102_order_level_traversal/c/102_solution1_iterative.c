#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 2000 // constraint: number of nodes is in [0, 2000]

// returns an array of levels; sets *returnSize to the level count and
// (*returnColumnSizes)[i] to the size of level i
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
  *returnSize = 0;
  *returnColumnSizes = malloc(MAX_NODES * sizeof(int));
  int **res = malloc(MAX_NODES * sizeof(int *));
  if (!root)
    return res;

  struct TreeNode **queue = malloc(MAX_NODES * sizeof(struct TreeNode *));
  int head = 0, tail = 0;
  queue[tail++] = root;

  while (head < tail) {
    int sz = tail - head;
    int *cur = malloc(sz * sizeof(int));

    for (int i = 0; i < sz; i++) {
      struct TreeNode *node = queue[head++];

      cur[i] = node->val;
      if (node->left)
        queue[tail++] = node->left;
      if (node->right)
        queue[tail++] = node->right;
    }

    (*returnColumnSizes)[*returnSize] = sz;
    res[(*returnSize)++] = cur;
  }

  free(queue);
  return res;
}
