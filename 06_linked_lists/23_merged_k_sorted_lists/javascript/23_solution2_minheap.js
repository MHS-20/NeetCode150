const ListNode = require("./list_node");

// minimal binary min-heap of ListNodes keyed on val
class MinHeap {
  constructor() {
    this.data = [];
  }

  get size() {
    return this.data.length;
  }

  push(node) {
    const d = this.data;
    d.push(node);
    let i = d.length - 1;
    while (i > 0) {
      const parent = (i - 1) >> 1;
      if (d[parent].val <= d[i].val) break;
      [d[parent], d[i]] = [d[i], d[parent]];
      i = parent;
    }
  }

  pop() {
    const d = this.data;
    const top = d[0];
    const last = d.pop();
    if (d.length > 0) {
      d[0] = last;
      let i = 0;
      for (;;) {
        let smallest = i;
        const l = 2 * i + 1;
        const r = l + 1;
        if (l < d.length && d[l].val < d[smallest].val) smallest = l;
        if (r < d.length && d[r].val < d[smallest].val) smallest = r;
        if (smallest === i) break;
        [d[smallest], d[i]] = [d[i], d[smallest]];
        i = smallest;
      }
    }
    return top;
  }
}

var mergeKLists = function (lists) {
  const minHeap = new MinHeap();

  // seed with the head of each non-empty list
  for (const head of lists) if (head !== null) minHeap.push(head);

  const dummy = new ListNode();
  let cur = dummy;

  while (minHeap.size > 0) {
    const smallest = minHeap.pop();

    cur.next = smallest;
    cur = cur.next;

    // the only new candidate is the successor of the node we just took
    if (smallest.next !== null) minHeap.push(smallest.next);
  }

  return dummy.next;
};
