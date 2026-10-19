class MedianFinder {
  constructor() {
    this.cnt = new Array(101).fill(0);
    this.below = 0; // numbers < 0
    this.above = 0; // numbers > 100
    this.total = 0;
  }

  kth(k) {
    let seen = this.below; // outliers below the range come first in sorted order
    for (let v = 0; v <= 100; v++) {
      seen += this.cnt[v];
      if (seen >= k) return v;
    }
    return -1;
  }

  addNum(num) {
    if (num < 0) this.below++;
    else if (num > 100) this.above++;
    else this.cnt[num]++;
    this.total++;
  }

  findMedian() {
    const a = this.kth(Math.floor((this.total + 1) / 2));
    const b = this.kth(Math.floor(this.total / 2) + 1);
    return (a + b) / 2;
  }
}
