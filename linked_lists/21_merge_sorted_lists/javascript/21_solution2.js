const ListNode = require("./list_node");

var mergeTwoLists = function (a, b) {
  if (a === null) return b;
  if (b === null) return a;

  if (a.val <= b.val) {
    a.next = mergeTwoLists(a.next, b);
    return a;
  }
  b.next = mergeTwoLists(a, b.next);
  return b;
};
