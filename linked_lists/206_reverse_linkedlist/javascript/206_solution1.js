const ListNode = require("./list_node");

var reverseList = function (head) {
  let prev = null;
  let cur = head;

  while (cur !== null) {
    const next = cur.next;
    cur.next = prev;
    prev = cur;
    cur = next;
  }

  return prev;
};
