#include "tree_node.h"
#include <stdlib.h>

#define OFFSET 3000 // constraint: -3000 <= node values <= 3000

static struct TreeNode *build(int *preorder, int *preIdx, int inLo, int inHi,
                              int *inIndex) {
  if (inLo > inHi)
    return NULL;

  int rootVal = preorder[(*preIdx)++];
  int mid = inIndex[rootVal + OFFSET];

  struct TreeNode *cur = malloc(sizeof(struct TreeNode));
  cur->val = rootVal;
  cur->left = build(preorder, preIdx, inLo, mid - 1, inIndex);
  cur->right = build(preorder, preIdx, mid + 1, inHi, inIndex);
  return cur;
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder,
                           int inorderSize) {
  static int inIndex[2 * OFFSET + 1];
  for (int i = 0; i < inorderSize; i++)
    inIndex[inorder[i] + OFFSET] = i;

  int preIdx = 0;
  return build(preorder, &preIdx, 0, inorderSize - 1, inIndex);
}
