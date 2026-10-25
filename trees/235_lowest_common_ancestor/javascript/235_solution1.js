const TreeNode = require("./tree_node");

var lowestCommonAncestor = function (root, p, q) {
  if (p.val > q.val) return lowestCommonAncestor(root, q, p);

  while (root) {
    if (root.val >= p.val && root.val <= q.val) return root;

    if (root.val < p.val) root = root.right;
    else root = root.left;
  }

  return root;
};
