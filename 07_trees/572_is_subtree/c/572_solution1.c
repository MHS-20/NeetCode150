#include "tree_node.h"
#include <stdbool.h>

static bool isSameTree(struct TreeNode *r1, struct TreeNode *r2) {
  if (!r1 && !r2)
    return true;
  if (!r1 || !r2)
    return false;
  return r1->val == r2->val && isSameTree(r1->left, r2->left) &&
         isSameTree(r1->right, r2->right);
}

bool isSubtree(struct TreeNode *root, struct TreeNode *subRoot) {
  if (!subRoot)
    return true;
  if (!root)
    return false;
  return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) ||
         isSubtree(root->right, subRoot);
}
