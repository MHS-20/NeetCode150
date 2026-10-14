#include "tree_node.h"
#include <queue>
#include <vector>

using namespace std;

vector<int> rightSideView(TreeNode *root) {
  vector<int> res;
  if (!root)
    return res;

  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; i++) {
      TreeNode *node = q.front();
      q.pop();

      if (i == sz - 1)
        res.push_back(node->val);

      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
  }
  return res;
}
