const TreeNode = require("./tree_node");

var levelOrder = function (root) {
  const res = [];
  if (!root) return res;

  // index-based queue: avoids the O(n) cost of Array.shift()
  const queue = [root];
  let head = 0;

  while (head < queue.length) {
    const sz = queue.length - head;
    const cur = [];

    for (let i = 0; i < sz; i++) {
      const node = queue[head++];

      cur.push(node.val);
      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    res.push(cur);
  }
  return res;
};
