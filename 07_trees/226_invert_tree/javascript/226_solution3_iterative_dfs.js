const TreeNode = require("./tree_node");

var invertTree = function (root) {
  const stack = [];
  if (root) stack.push(root);

  while (stack.length > 0) {
    const cur = stack.pop();

    [cur.left, cur.right] = [cur.right, cur.left];

    if (cur.left) stack.push(cur.left);
    if (cur.right) stack.push(cur.right);
  }

  return root;
};
