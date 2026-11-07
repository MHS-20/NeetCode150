const ListNode = require("./list_node");

var reverseKGroup = function (head, k) {
  const dummy = new ListNode(0, head);
  let groupPrev = dummy;

  for (;;) {
    // find the k-th node of this group
    let kth = groupPrev;
    for (let i = 0; i < k && kth !== null; i++) kth = kth.next;
    if (kth === null) break; // fewer than k nodes left

    const groupStart = groupPrev.next;
    const groupNext = kth.next; // first node after the group

    // reverse k nodes, starting with prev = groupNext so the
    // old head ends up pointing to the rest of the list
    let prev = groupNext;
    let cur = groupStart;
    while (cur !== groupNext) {
      const next = cur.next;
      cur.next = prev;
      prev = cur;
      cur = next;
    }

    groupPrev.next = kth; // previous part -> new group head
    groupPrev = groupStart; // old head is now the group's tail
  }

  return dummy.next;
};
