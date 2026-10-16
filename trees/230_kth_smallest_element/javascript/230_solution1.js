const TreeNode = require("./tree_node");

var kthSmallest = function (root, k) {
  let res = 0;

  const dfs = (node) => {
    if (!node || k === 0) return;

    dfs(node.left);
    k--;

    if (k === 0) {
      res = node.val;
      return;
    }

    dfs(node.right);
  };

  dfs(root);
  return res;
};
