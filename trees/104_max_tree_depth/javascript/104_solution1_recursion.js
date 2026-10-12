const TreeNode = require("./tree_node");

var maxDepth = function (root) {
  const findDepth = (node, count) => {
    if (!node) return count;
    return Math.max(findDepth(node.left, count + 1), findDepth(node.right, count + 1));
  };

  return findDepth(root, 0);
};
