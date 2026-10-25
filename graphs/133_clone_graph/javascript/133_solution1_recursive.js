const _Node = require("./node");

/**
 * @param {_Node} node
 * @return {_Node}
 */
var cloneGraph = function (node) {
  const clones = new Map();

  const clone = (node) => {
    if (!node) return null;

    if (!clones.has(node)) {
      clones.set(node, new _Node(node.val));
      for (const cur of node.neighbors) {
        clones.get(node).neighbors.push(clone(cur));
      }
    }

    return clones.get(node);
  };

  return clone(node);
};
