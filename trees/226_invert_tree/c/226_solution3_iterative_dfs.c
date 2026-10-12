#include "tree_node.h"
#include <stdlib.h>

#define MAX_NODES 100 // constraint: number of nodes is in [0, 100]

struct TreeNode *invertTree(struct TreeNode *root) {
  struct TreeNode *stack[MAX_NODES];
  int top = 0;
  if (root)
    stack[top++] = root;

  while (top > 0) {
    struct TreeNode *cur = stack[--top];

    struct TreeNode *tmp = cur->left;
    cur->left = cur->right;
    cur->right = tmp;

    if (cur->left)
      stack[top++] = cur->left;
    if (cur->right)
      stack[top++] = cur->right;
  }

  return root;
}
