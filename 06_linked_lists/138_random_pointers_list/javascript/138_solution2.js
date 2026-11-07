const Node = require("./node");

var copyRandomList = function (head) {
  if (!head) return null;

  // pass 1: interleave copies
  for (let cur = head; cur; cur = cur.next.next) {
    cur.next = new Node(cur.val, cur.next);
  }

  // pass 2: set random pointers
  for (let cur = head; cur; cur = cur.next.next) {
    if (cur.random) cur.next.random = cur.random.next;
  }

  // pass 3: separate the lists
  const copyHead = head.next;
  for (let cur = head; cur; cur = cur.next) {
    const copy = cur.next;
    cur.next = copy.next;
    if (copy.next) copy.next = copy.next.next;
  }

  return copyHead;
};
