const TreeNode = require("./tree_node");

var levelOrder = function (root) {
  const res = [];

  const dfs = (node, depth) => {
    if (!node) return;

    // create array for new depth
    if (depth === res.length) res.push([]);

    res[depth].push(node.val);

    dfs(node.left, depth + 1);
    dfs(node.right, depth + 1);
  };

  dfs(root, 0);
  return res;
};
