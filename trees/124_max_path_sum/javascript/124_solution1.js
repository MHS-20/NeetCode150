const TreeNode = require("./tree_node");

var maxPathSum = function (root) {
  let mx = -Infinity;

  const dfs = (node) => {
    if (!node) return 0;

    const l = Math.max(0, dfs(node.left));
    const r = Math.max(0, dfs(node.right));

    mx = Math.max(mx, l + r + node.val);
    return Math.max(l, r) + node.val;
  };

  dfs(root);
  return mx;
};
