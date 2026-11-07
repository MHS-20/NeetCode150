class MinHeap {
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
      if (h[p] <= h[i]) break;
      [h[p], h[i]] = [h[i], h[p]];
      i = p;
    }
  }

  pop() {
    const h = this.data;
    const last = h.pop();
    if (h.length === 0) return;
    h[0] = last;
    let i = 0;
    for (;;) {
      let min = i;
      const l = 2 * i + 1,
        r = 2 * i + 2;
      if (l < h.length && h[l] < h[min]) min = l;
      if (r < h.length && h[r] < h[min]) min = r;
      if (min === i) return;
      [h[min], h[i]] = [h[i], h[min]];
      i = min;
    }
  }
}

class KthLargest {
  constructor(k, nums) {
    this.cap = k;
    this.pq = new MinHeap();
    for (const n of nums) this.add(n);
  }

  add(val) {
    if (this.pq.size() < this.cap) {
      this.pq.push(val);
    } else if (val > this.pq.top()) {
      this.pq.pop();
      this.pq.push(val);
    }
    return this.pq.top();
  }
}
