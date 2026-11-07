const TreeNode = require("./tree_node");

var goodNodes = function (root) {
  let count = 0;
  const stack = [[root, -Infinity]];

  while (stack.length > 0) {
    let [node, maxSoFar] = stack.pop();
    if (!node) continue;

    if (node.val >= maxSoFar) {
      count++;
      maxSoFar = node.val;
    }

    stack.push([node.left, maxSoFar], [node.right, maxSoFar]);
  }
  return count;
};
