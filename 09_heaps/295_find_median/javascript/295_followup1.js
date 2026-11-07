class MedianFinder {
  constructor() {
    this.cnt = new Array(101).fill(0);
    this.total = 0;
  }

  // k-th smallest, 1-indexed
  kth(k) {
    let seen = 0;
    for (let v = 0; v <= 100; v++) {
      seen += this.cnt[v];
      if (seen >= k) return v;
    }
    return -1; // unreachable if 1 <= k <= total
  }

  addNum(num) {
    this.cnt[num]++;
    this.total++;
  }

  findMedian() {
    const a = this.kth(Math.floor((this.total + 1) / 2));
    const b = this.kth(Math.floor(this.total / 2) + 1);
    return (a + b) / 2;
  }
}
