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
 * @param {character[]} tasks
 * @param {number} n
 * @return {number}
 */
var leastInterval = function (tasks, n) {
  const arr = new Array(26).fill(0);
  for (const ch of tasks) arr[ch.charCodeAt(0) - 65]++;

  const pq = new MaxHeap(); // remaining counts
  for (const c of arr) if (c > 0) pq.push(c);

  const timer = []; // [count, nextTime]
  let head = 0;
  let time = 0;

  while (pq.size() > 0 || head < timer.length) {
    if (head < timer.length && timer[head][1] <= time) pq.push(timer[head++][0]);

    if (pq.size() > 0) {
      const count = pq.pop() - 1;
      if (count > 0) timer.push([count, time + n + 1]);
    }

    time++;
  }

  return time;
};
