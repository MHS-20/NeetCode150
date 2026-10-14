const TreeNode = require("./tree_node");

var lowestCommonAncestor = function (root, p, q) {
  const lo = Math.min(p.val, q.val);
  const hi = Math.max(p.val, q.val);

  // the LCA is the first node whose value falls between p and q
  while (root) {
    if (root.val < lo) root = root.right;
    else if (root.val > hi) root = root.left;
    else return root;
  }

  return null;
};
