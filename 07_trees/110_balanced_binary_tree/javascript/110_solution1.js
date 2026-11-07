const TreeNode = require("./tree_node");

var isBalanced = function (root) {
  // returns the subtree height, or -1 as soon as any subtree is unbalanced
  const height = (node) => {
    if (!node) return 0;

    const l = height(node.left);
    if (l === -1) return -1;

    const r = height(node.right);
    if (r === -1) return -1;

    if (Math.abs(l - r) > 1) return -1;

    return 1 + Math.max(l, r);
  };

  return height(root) !== -1;
};
