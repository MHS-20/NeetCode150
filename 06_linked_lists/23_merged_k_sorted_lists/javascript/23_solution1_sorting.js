const ListNode = require("./list_node");

var mergeKLists = function (lists) {
  // 1. collect every value from every list
  const vals = [];
  for (let head of lists)
    for (let p = head; p !== null; p = p.next) vals.push(p.val);

  // 2. sort them
  vals.sort((a, b) => a - b);

  // 3. rebuild a new list
  const dummy = new ListNode();
  let cur = dummy;
  for (const v of vals) {
    cur.next = new ListNode(v);
    cur = cur.next;
  }

  return dummy.next;
};
