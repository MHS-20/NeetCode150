const TreeNode = require("./tree_node");

var buildTree = function (preorder, inorder) {
  const inIndex = new Map();
  inorder.forEach((v, i) => inIndex.set(v, i));

  let preIdx = 0;
  const build = (inLo, inHi) => {
    if (inLo > inHi) return null;

    const rootVal = preorder[preIdx++];
    const mid = inIndex.get(rootVal);

    const cur = new TreeNode(rootVal);
    cur.left = build(inLo, mid - 1);
    cur.right = build(mid + 1, inHi);
    return cur;
  };

  return build(0, inorder.length - 1);
};
