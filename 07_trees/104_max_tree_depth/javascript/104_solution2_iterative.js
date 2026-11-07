const TreeNode = require("./tree_node");

var maxDepth = function (root) {
  let level = root ? [root] : [];

  let depth = 0;
  while (level.length > 0) {
    depth++;

    // the next level is every child of the current one
    const next = [];
    for (const cur of level) {
      if (cur.left) next.push(cur.left);
      if (cur.right) next.push(cur.right);
    }
    level = next;
  }

  return depth;
};
