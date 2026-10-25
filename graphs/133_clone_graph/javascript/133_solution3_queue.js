const _Node = require("./node");

/**
 * @param {_Node} node
 * @return {_Node}
 */
var cloneGraph = function (node) {
  if (!node) return null;

  const clones = new Map([[node, new _Node(node.val)]]);
  // index-based queue: Array.shift() is O(n)
  const q = [node];

  for (let head = 0; head < q.length; head++) {
    const cur = q[head];
    for (const neighbor of cur.neighbors) {
      if (!clones.has(neighbor)) {
        clones.set(neighbor, new _Node(neighbor.val));
        q.push(neighbor);
      }
      clones.get(cur).neighbors.push(clones.get(neighbor));
    }
  }
  return clones.get(node);
};
