#include "tree_node.h"
#include <stack>
#include <utility>

using namespace std;

class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    stack<TreeNode *> st;
    if (root)
      st.push(root);

    while (!st.empty()) {
      TreeNode *cur = st.top();
      st.pop();

      swap(cur->left, cur->right);

      if (cur->left)
        st.push(cur->left);
      if (cur->right)
        st.push(cur->right);
    }

    return root;
  }
};
