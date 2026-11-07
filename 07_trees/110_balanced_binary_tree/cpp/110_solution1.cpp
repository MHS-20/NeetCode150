#include "tree_node.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution {
public:
  bool isBalanced(TreeNode *root) { return height(root) != -1; }

private:
  int height(TreeNode *node) {
    if (!node)
      return 0;

    int l = height(node->left);
    if (l == -1)
      return -1;

    int r = height(node->right);
    if (r == -1)
      return -1;

    if (abs(l - r) > 1)
      return -1;

    return 1 + max(l, r);
  }
};
