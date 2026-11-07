#include "tree_node.h"
#include <climits>
#include <stack>
#include <utility>

using namespace std;

int goodNodes(TreeNode *root) {
  int count = 0;
  stack<pair<TreeNode *, int>> st;
  st.push({root, INT_MIN});

  while (!st.empty()) {
    auto [node, maxSoFar] = st.top();
    st.pop();

    if (!node)
      continue;

    if (node->val >= maxSoFar) {
      count++;
      maxSoFar = node->val;
    }

    st.push({node->left, maxSoFar});
    st.push({node->right, maxSoFar});
  }
  return count;
}
