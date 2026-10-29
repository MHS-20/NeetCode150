/**
 * Definition of Interval:
 * class Interval {
 *   constructor(start, end) {
 *     this.start = start;
 *     this.end = end;
 *   }
 * }
 */

/**
 * @param {Interval[]} intervals
 * @returns {number}
 */
var minMeetingRooms = function (intervals) {
  let mx = 0;

  // binary min-heap of end times: JS has no built-in priority queue
  const heap = [];
  const push = (x) => {
    heap.push(x);
    let i = heap.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (heap[p] <= heap[i]) break;
      [heap[p], heap[i]] = [heap[i], heap[p]];
      i = p;
    }
  };
  const pop = () => {
    const last = heap.pop();
    if (heap.length > 0) {
      heap[0] = last;
      let i = 0;
      for (;;) {
        let s = i;
        const l = 2 * i + 1;
        const r = l + 1;
        if (l < heap.length && heap[l] < heap[s]) s = l;
        if (r < heap.length && heap[r] < heap[s]) s = r;
        if (s === i) break;
        [heap[s], heap[i]] = [heap[i], heap[s]];
        i = s;
      }
    }
  };

  intervals.sort((a, b) => a.start - b.start);

  for (const i of intervals) {
    while (heap.length > 0 && heap[0] <= i.start) pop();
    push(i.end);
    mx = Math.max(mx, heap.length);
  }

  return mx;
};
