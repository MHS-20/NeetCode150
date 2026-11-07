#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 100 // constraint: number of nodes is in [0, 100]

// returns the rightmost value of each level; sets *returnSize to the level count
int *rightSideView(struct TreeNode *root, int *returnSize) {
  int *res = malloc(MAX_NODES * sizeof(int));
  *returnSize = 0;
  if (!root)
    return res;

  struct TreeNode *queue[MAX_NODES];
  int head = 0, tail = 0;
  queue[tail++] = root;

  while (head < tail) {
    int sz = tail - head;
    for (int i = 0; i < sz; i++) {
      struct TreeNode *node = queue[head++];

      if (i == sz - 1)
        res[(*returnSize)++] = node->val;

      if (node->left)
        queue[tail++] = node->left;
      if (node->right)
        queue[tail++] = node->right;
    }
  }
  return res;
}
