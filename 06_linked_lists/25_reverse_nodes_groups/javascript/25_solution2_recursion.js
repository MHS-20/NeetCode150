const ListNode = require("./list_node");

var reverseKGroup = function (head, k) {
  // check that k nodes exist
  let node = head;
  for (let i = 0; i < k; i++) {
    if (node === null) return head; // fewer than k: leave as is
    node = node.next;
  }
  // node is now the (k+1)-th node, i.e. the start of the rest

  let prev = reverseKGroup(node, k); // already-processed rest
  let cur = head;
  for (let i = 0; i < k; i++) {
    const next = cur.next;
    cur.next = prev;
    prev = cur;
    cur = next;
  }
  return prev; // new head of this group
};
