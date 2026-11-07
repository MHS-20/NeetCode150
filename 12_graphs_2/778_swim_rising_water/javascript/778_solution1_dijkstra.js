/**
 * @param {number[][]} grid
 * @return {number}
 */
var swimInWater = function (grid) {
  const n = grid.length;
  const visited = Array.from({ length: n }, () => new Array(n).fill(false));
  const pq = new MinHeap((a, b) => a[0] - b[0]); // [elev, r, c]
  const dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];

  pq.push([grid[0][0], 0, 0]);
  visited[0][0] = true;
  let t = 0;

  while (pq.size()) {
    const [elev, r, c] = pq.pop();
    t = Math.max(t, elev);
    if (r === n - 1 && c === n - 1) return t;

    for (const [dr, dc] of dirs) {
      const nr = r + dr, nc = c + dc;
      if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc]) continue;
      visited[nr][nc] = true;
      pq.push([grid[nr][nc], nr, nc]);
    }
  }
  return -1;
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
