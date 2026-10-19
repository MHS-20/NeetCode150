class MaxHeap {
  constructor(key) {
    this.key = key;
    this.data = [];
  }

  size() {
    return this.data.length;
  }

  push(val) {
    const h = this.data;
    h.push(val);
    let i = h.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (this.key(h[p]) >= this.key(h[i])) break;
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
      if (l < h.length && this.key(h[l]) > this.key(h[max])) max = l;
      if (r < h.length && this.key(h[r]) > this.key(h[max])) max = r;
      if (max === i) return top;
      [h[max], h[i]] = [h[i], h[max]];
      i = max;
    }
  }
}

/**
 * @param {number[][]} points
 * @param {number} k
 * @return {number[][]}
 */
var kClosest = function (points, k) {
  // squared distance, same order as the real one
  const pq = new MaxHeap(([x, y]) => x * x + y * y);

  for (const p of points) {
    pq.push(p);
    if (pq.size() > k) pq.pop();
  }

  return pq.data;
};
