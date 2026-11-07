#include "tree_node.h"
#include <queue>

using namespace std;

class Solution {
public:
  int maxDepth(TreeNode *root) {
    queue<TreeNode *> q;
    if (root)
      q.push(root);

    int depth = 0;
    while (!q.empty()) {
      int size = q.size();
      depth++;

      for (int i = 0; i < size; i++) {
        TreeNode *cur = q.front();
        q.pop();

        if (cur->left)
          q.push(cur->left);
        if (cur->right)
          q.push(cur->right);
      }
    }

    return depth;
  }
};
