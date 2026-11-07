#include "tree_node.h"
#include <string>

using namespace std;

class Codec {
public:
  string serialize(TreeNode *root) {
    string ser;
    serDfs(root, ser);
    return ser;
  }

  void serDfs(TreeNode *root, string &ser) {
    if (!root) {
      ser += "N#";
      return;
    }
    ser += to_string(root->val) + "#";
    serDfs(root->left, ser);
    serDfs(root->right, ser);
  }

  TreeNode *deserialize(string data) {
    int pos = 0;
    return desDfs(data, pos);
  }

  TreeNode *desDfs(const string &data, int &pos) {
    int end = data.find('#', pos); // next delimiter
    string tok = data.substr(pos, end - pos);
    pos = end + 1; // move cursor past '#'

    if (tok == "N")
      return nullptr;

    TreeNode *root = new TreeNode(stoi(tok));
    root->left = desDfs(data, pos);  // advances pos past the left subtree
    root->right = desDfs(data, pos); // continues from there
    return root;
  }
};
