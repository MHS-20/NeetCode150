#include "tree_node.h"

#define MAX_NODES 10000 // constraint: number of nodes is in [0, 10^4]

int maxDepth(struct TreeNode *root) {
  static struct TreeNode *queue[MAX_NODES];
  int head = 0, tail = 0;
  if (root)
    queue[tail++] = root;

  int depth = 0;
  while (head < tail) {
    int size = tail - head;
    depth++;

    for (int i = 0; i < size; i++) {
      struct TreeNode *cur = queue[head++];

      if (cur->left)
        queue[tail++] = cur->left;
      if (cur->right)
        queue[tail++] = cur->right;
    }
  }

  return depth;
}
