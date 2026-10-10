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

  // 2. cut the list and push the second half onto a stack
  const stack = [];
  for (let curr = slow.next; curr; curr = curr.next) stack.push(curr);
  slow.next = null; // split into two lists

  // 3. merge: popping the stack yields the second half in reverse
  let first = head;
  while (stack.length) {
    const second = stack.pop();
    second.next = first.next;
    first.next = second;
    first = second.next;
  }
};
