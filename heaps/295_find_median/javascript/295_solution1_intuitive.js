class Heap {
  // cmp(a, b) < 0 means a comes out first
  constructor(cmp) {
    this.cmp = cmp;
    this.data = [];
  }

  top() {
    return this.data[0];
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
      if (this.cmp(h[p], h[i]) <= 0) break;
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
      let best = i;
      const l = 2 * i + 1,
        r = 2 * i + 2;
      if (l < h.length && this.cmp(h[l], h[best]) < 0) best = l;
      if (r < h.length && this.cmp(h[r], h[best]) < 0) best = r;
      if (best === i) return top;
      [h[best], h[i]] = [h[i], h[best]];
      i = best;
    }
  }
}

class MedianFinder {
  constructor() {
    this.maxHeap = new Heap((a, b) => b - a); // left half
    this.minHeap = new Heap((a, b) => a - b); // right half
  }

  addNum(num) {
    if (this.minHeap.size() > 0 && num >= this.minHeap.top()) this.minHeap.push(num);
    else this.maxHeap.push(num);

    if (this.maxHeap.size() > this.minHeap.size() + 1) this.minHeap.push(this.maxHeap.pop());

    if (this.minHeap.size() > this.maxHeap.size()) this.maxHeap.push(this.minHeap.pop());
  }

  findMedian() {
    if ((this.minHeap.size() + this.maxHeap.size()) % 2 === 0)
      return (this.minHeap.top() + this.maxHeap.top()) / 2;
    return this.maxHeap.top();
  }
}
