const TreeNode = require("./tree_node");

var serialize = function (root) {
  const ser = [];

  const dfs = (node) => {
    if (!node) {
      ser.push("N#");
      return;
    }
    ser.push(node.val + "#");
    dfs(node.left);
    dfs(node.right);
  };

  dfs(root);
  return ser.join("");
};

var deserialize = function (data) {
  const tokens = data.split("#");
  let pos = 0;

  const dfs = () => {
    const tok = tokens[pos++];
    if (tok === "N") return null;

    const node = new TreeNode(Number(tok));
    node.left = dfs(); // advances pos past the left subtree
    node.right = dfs(); // continues from there
    return node;
  };

  return dfs();
};
