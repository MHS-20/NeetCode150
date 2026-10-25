const TreeNode = require("./tree_node");

var lowestCommonAncestor = function (root, p, q) {
  if (p.val > q.val) return lowestCommonAncestor(root, q, p);

  if (root.val >= p.val && root.val <= q.val) return root;

  if (q.val < root.val) return lowestCommonAncestor(root.left, p, q);
  else return lowestCommonAncestor(root.right, p, q);
};
