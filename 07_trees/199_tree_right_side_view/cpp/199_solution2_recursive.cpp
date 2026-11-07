#include "tree_node.h"
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> rightSideView(TreeNode *root) {
    vector<int> res;
    dfs(root, 0, res);
    return res;
  }

private:
  void dfs(TreeNode *node, int depth, vector<int> &res) {
    if (!node)
      return;

    if (depth == res.size())
      res.push_back(node->val);

    dfs(node->right, depth + 1, res);
    dfs(node->left, depth + 1, res);
  }
};
