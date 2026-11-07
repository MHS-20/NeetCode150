const ListNode = require("./list_node");

function mergeTwo(a, b) {
  const dummy = new ListNode();
  let cur = dummy;
  while (a !== null && b !== null) {
    if (a.val <= b.val) {
      cur.next = a;
      a = a.next;
    } else {
      cur.next = b;
      b = b.next;
    }
    cur = cur.next;
  }
  cur.next = a !== null ? a : b;
  return dummy.next;
}

var mergeKLists = function (lists) {
  const n = lists.length;
  if (n === 0) return null;

  for (let step = 1; step < n; step *= 2)
    for (let i = 0; i + step < n; i += 2 * step)
      lists[i] = mergeTwo(lists[i], lists[i + step]);

  return lists[0];
};
