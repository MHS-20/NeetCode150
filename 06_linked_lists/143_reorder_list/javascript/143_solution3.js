const ListNode = require("./list_node");

// array used as a deque via front/back indices (shift() would be O(n))
var reorderList = function (head) {
  if (!head || !head.next) return;

  // 1. store every node
  const nodes = [];
  for (let curr = head; curr; curr = curr.next) nodes.push(curr);

  // 2. relink alternating between the front and the back
  let l = 1;
  let r = nodes.length - 1;
  let tail = head; // nodes[0] is already the head
  while (l <= r) {
    tail.next = nodes[r--];
    tail = tail.next;
    if (l <= r) {
      tail.next = nodes[l++];
      tail = tail.next;
    }
  }
  tail.next = null;
};
