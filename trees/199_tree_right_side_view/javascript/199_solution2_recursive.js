const TreeNode = require("./tree_node");

var rightSideView = function (root) {
  const res = [];

  // visit right first, so the first node seen at each depth is the rightmost
  const dfs = (node, depth) => {
    if (!node) return;

    if (depth === res.length) res.push(node.val);

    dfs(node.right, depth + 1);
    dfs(node.left, depth + 1);
  };

  dfs(root, 0);
  return res;
};
