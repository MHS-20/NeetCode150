#include "tree_node.h"
#include <queue>

using namespace std;

class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    if (!root)
      return nullptr;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode *cur = q.front();
      q.pop();

      TreeNode *tmp = cur->left;
      cur->left = cur->right;
      cur->right = tmp;

      if (cur->left)
        q.push(cur->left);

      if (cur->right)
        q.push(cur->right);
    }

    return root;
  }
};
