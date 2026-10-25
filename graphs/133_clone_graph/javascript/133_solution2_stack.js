const _Node = require("./node");

/**
 * @param {_Node} node
 * @return {_Node}
 */
var cloneGraph = function (node) {
  if (!node) return null;

  const clones = new Map([[node, new _Node(node.val)]]);
  const st = [node];

  while (st.length > 0) {
    const cur = st.pop();
    for (const neighbor of cur.neighbors) {
      if (!clones.has(neighbor)) {
        clones.set(neighbor, new _Node(neighbor.val));
        st.push(neighbor);
      }
      clones.get(cur).neighbors.push(clones.get(neighbor));
    }
  }
  return clones.get(node);
};
