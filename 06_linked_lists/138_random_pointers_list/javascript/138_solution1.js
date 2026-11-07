const Node = require("./node");

var copyRandomList = function (head) {
  const copyOf = new Map([[null, null]]); // null original -> null copy

  // pass 1: create all copies (no links yet)
  for (let cur = head; cur; cur = cur.next) copyOf.set(cur, new Node(cur.val));

  // pass 2: wire up next and random
  for (let cur = head; cur; cur = cur.next) {
    copyOf.get(cur).next = copyOf.get(cur.next);
    copyOf.get(cur).random = copyOf.get(cur.random);
  }

  return copyOf.get(head);
};
