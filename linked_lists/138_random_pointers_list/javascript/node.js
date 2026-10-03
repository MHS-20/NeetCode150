// Definition for a Node.
function Node(val, next, random) {
  this.val = val;
  this.next = next === undefined ? null : next;
  this.random = random === undefined ? null : random;
}

module.exports = Node;
