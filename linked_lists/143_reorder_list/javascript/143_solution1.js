const ListNode = require("./list_node");

var reorderList = function (head) {
  if (!head || !head.next) return;

  // 1. find the end of the first half
  let slow = head;
  let fast = head;
  while (fast.next && fast.next.next) {
    slow = slow.next;
    fast = fast.next.next;
  }

  // 2. cut the list and reverse the second half
  let prev = null;
  let curr = slow.next;
  slow.next = null; // split into two lists

  while (curr) {
    const next = curr.next;
    curr.next = prev;
    prev = curr;
    curr = next;
  }
  let second = prev; // head of reversed second half

  // 3. merge: alternate nodes from first and second
  let first = head;
  while (second) {
    const next1 = first.next;
    const next2 = second.next;

    first.next = second;
    second.next = next1;

    first = next1;
    second = next2;
  }
};
