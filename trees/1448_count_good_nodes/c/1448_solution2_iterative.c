#include "tree_node.h"
#include <limits.h>

#define MAX_NODES 100000 // constraint: number of nodes is in [1, 10^5]

struct Frame {
  struct TreeNode *node;
  int maxSoFar;
};

int goodNodes(struct TreeNode *root) {
  static struct Frame stack[MAX_NODES];
  int top = 0, count = 0;
  stack[top++] = (struct Frame){root, INT_MIN};

  while (top > 0) {
    struct Frame f = stack[--top];
    if (!f.node)
      continue;

    if (f.node->val >= f.maxSoFar) {
      count++;
      f.maxSoFar = f.node->val;
    }

    // each node pushes at most two children, so the stack stays within bounds
    if (f.node->right)
      stack[top++] = (struct Frame){f.node->right, f.maxSoFar};
    if (f.node->left)
      stack[top++] = (struct Frame){f.node->left, f.maxSoFar};
  }
  return count;
}
