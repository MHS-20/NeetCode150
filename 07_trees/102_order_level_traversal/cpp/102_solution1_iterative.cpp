#include "tree_node.h"
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> levelOrder(TreeNode *root) {
  vector<vector<int>> res;
  if (!root)
    return res;

  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    int sz = q.size();
    vector<int> cur;

    for (int i = 0; i < sz; i++) {
      TreeNode *node = q.front();
      q.pop();

      cur.push_back(node->val);
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    res.push_back(cur);
  }
  return res;
}
