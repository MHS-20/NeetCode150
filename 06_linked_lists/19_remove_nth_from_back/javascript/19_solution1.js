const ListNode = require("./list_node");

var removeNthFromEnd = function (head, n) {
  const dummy = new ListNode(0, head);
  let left = dummy;
  let right = dummy;

  // create a gap of n nodes between left and right
  for (let i = 0; i < n; i++) right = right.next;

  // move both until right is on the last node;
  // left is then on the node before the target
  while (right.next) {
    right = right.next;
    left = left.next;
  }

  left.next = left.next.next;

  return dummy.next;
};
