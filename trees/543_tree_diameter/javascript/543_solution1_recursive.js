const TreeNode = require("./tree_node");

var diameterOfBinaryTree = function (root) {
  let best = 0;

  const height = (node) => {
    if (!node) return 0;

    const l = height(node.left);
    const r = height(node.right);

    best = Math.max(best, l + r);
    return 1 + Math.max(l, r);
  };

  height(root);
  return best;
};
