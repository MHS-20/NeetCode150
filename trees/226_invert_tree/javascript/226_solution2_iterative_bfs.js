const TreeNode = require("./tree_node");

var invertTree = function (root) {
  if (!root) return null;

  // index-based queue: avoids the O(n) cost of Array.shift()
  const queue = [root];
  for (let head = 0; head < queue.length; head++) {
    const cur = queue[head];

    [cur.left, cur.right] = [cur.right, cur.left];

    if (cur.left) queue.push(cur.left);
    if (cur.right) queue.push(cur.right);
  }

  return root;
};
