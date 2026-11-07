#include "tree_node.h"
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    unordered_map<int, int> idxs;

    for (int i = 0; i < inorder.size(); i++)
      idxs[inorder[i]] = i;

    int preIdx = 0;
    return build(preorder, preIdx, 0, (int)inorder.size() - 1, idxs);
  }

  TreeNode *build(vector<int> &preorder, int &preIdx, int inLo, int inHi,
                  unordered_map<int, int> &inIndex) {
    if (inLo > inHi)
      return nullptr;

    int rootVal = preorder[preIdx++];
    int mid = inIndex[rootVal];

    TreeNode *cur = new TreeNode(rootVal);
    cur->left = build(preorder, preIdx, inLo, mid - 1, inIndex);
    cur->right = build(preorder, preIdx, mid + 1, inHi, inIndex);
    return cur;
  }
};
