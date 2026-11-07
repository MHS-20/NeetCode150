#include "tree_node.h"
#include <algorithm>

using namespace std;

class Solution {
public:
  int maxDepth(TreeNode *root) { return findDepth(root, 0); }

  int findDepth(TreeNode *root, int count) {
    if (!root)
      return count;
    return max(findDepth(root->left, count + 1),
               findDepth(root->right, count + 1));
  }
};
