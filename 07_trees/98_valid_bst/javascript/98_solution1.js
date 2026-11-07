const TreeNode = require("./tree_node");

var isValidBST = function (root) {
  const dfs = (node, lowerbound, upperbound) => {
    if (!node) return true;
    if (node.val <= lowerbound || node.val >= upperbound) return false;
    return (
      dfs(node.right, node.val, upperbound) &&
      dfs(node.left, lowerbound, node.val)
    );
  };

  return dfs(root, -Infinity, Infinity);
};
