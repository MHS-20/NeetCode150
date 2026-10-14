#include "tree_node.h"
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> res;
    dfs(root, 0, res);
    return res;
  }

private:
  void dfs(TreeNode *node, int depth, vector<vector<int>> &res) {
    if (!node)
      return;

    // create vector for new depth
    if (depth == res.size())
      res.push_back({});

    res[depth].push_back(node->val);

    dfs(node->left, depth + 1, res);
    dfs(node->right, depth + 1, res);
  }
};
