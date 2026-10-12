#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 100 // constraint: number of nodes is in [0, 100]

struct TreeNode *invertTree(struct TreeNode *root) {
  if (!root)
    return NULL;

  struct TreeNode *queue[MAX_NODES];
  int head = 0, tail = 0;
  queue[tail++] = root;

  while (head < tail) {
    struct TreeNode *cur = queue[head++];

    struct TreeNode *tmp = cur->left;
    cur->left = cur->right;
    cur->right = tmp;

    if (cur->left)
      queue[tail++] = cur->left;
    if (cur->right)
      queue[tail++] = cur->right;
  }

  return root;
}
