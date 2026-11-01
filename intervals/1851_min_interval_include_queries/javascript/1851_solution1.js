/**
 * @param {number[][]} intervals
 * @param {number[]} queries
 * @return {number[]}
 */
var minInterval = function (intervals, queries) {
  const result = new Array(queries.length);
  const idx = queries.map((_, k) => k);
  const heap = new MinHeap((a, b) => a[0] - b[0] || a[1] - b[1]); // [size, end]

  intervals.sort((a, b) => a[0] - b[0]);
  idx.sort((a, b) => queries[a] - queries[b]);

  let i = 0;
  const n = intervals.length;
  for (const j of idx) {
    const q = queries[j];

    while (i < n && intervals[i][0] <= q) {
      heap.push([intervals[i][1] - intervals[i][0] + 1, intervals[i][1]]);
      i++;
    }

    while (heap.size() && heap.peek()[1] < q) heap.pop();

    result[j] = heap.size() ? heap.peek()[0] : -1;
  }

  return result;
};

// JS has no built-in heap
class MinHeap {
  constructor(cmp) {
    this.a = [];
    this.cmp = cmp;
  }
  size() {
    return this.a.length;
  }
  peek() {
    return this.a[0];
  }
  push(x) {
    const a = this.a;
    a.push(x);
    for (let i = a.length - 1; i > 0; ) {
      const p = (i - 1) >> 1;
      if (this.cmp(a[i], a[p]) >= 0) break;
      [a[i], a[p]] = [a[p], a[i]];
      i = p;
    }
  }
  pop() {
    const a = this.a;
    const top = a[0];
    const last = a.pop();
    if (a.length) {
      a[0] = last;
      for (let i = 0; ; ) {
        let c = 2 * i + 1;
        if (c >= a.length) break;
        if (c + 1 < a.length && this.cmp(a[c + 1], a[c]) < 0) c++;
        if (this.cmp(a[c], a[i]) >= 0) break;
        [a[i], a[c]] = [a[c], a[i]];
        i = c;
      }
    }
    return top;
  }
}
