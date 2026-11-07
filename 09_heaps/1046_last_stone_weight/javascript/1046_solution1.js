class MaxHeap {
  constructor() {
    this.data = [];
  }

  size() {
    return this.data.length;
  }

  top() {
    return this.data[0];
  }

  push(val) {
    const h = this.data;
    h.push(val);
    let i = h.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (h[p] >= h[i]) break;
      [h[p], h[i]] = [h[i], h[p]];
      i = p;
    }
  }

  pop() {
    const h = this.data;
    const top = h[0];
    const last = h.pop();
    if (h.length === 0) return top;
    h[0] = last;
    let i = 0;
    for (;;) {
      let max = i;
      const l = 2 * i + 1,
        r = 2 * i + 2;
      if (l < h.length && h[l] > h[max]) max = l;
      if (r < h.length && h[r] > h[max]) max = r;
      if (max === i) return top;
      [h[max], h[i]] = [h[i], h[max]];
      i = max;
    }
  }
}

/**
 * @param {number[]} stones
 * @return {number}
 */
var lastStoneWeight = function (stones) {
  const pq = new MaxHeap();
  for (const s of stones) pq.push(s);

  while (pq.size() > 1) {
    const y = pq.pop();
    const x = pq.pop();
    if (y !== x) pq.push(y - x);
  }

  return pq.size() === 0 ? 0 : pq.top();
};
