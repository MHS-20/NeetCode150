/**
 * @param {number[][]} grid
 * @return {number}
 */
var swimInWater = function (grid) {
  const n = grid.length;
  const dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];

  const canReach = (t) => {
    if (grid[0][0] > t) return false;
    const visited = Array.from({ length: n }, () => new Array(n).fill(false));
    const q = [[0, 0]];
    visited[0][0] = true;

    for (let head = 0; head < q.length; head++) {
      const [r, c] = q[head];
      if (r === n - 1 && c === n - 1) return true;
      for (const [dr, dc] of dirs) {
        const nr = r + dr, nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
        if (visited[nr][nc] || grid[nr][nc] > t) continue;
        visited[nr][nc] = true;
        q.push([nr, nc]);
      }
    }
    return false;
  };

  let lo = 0, hi = n * n - 1;
  while (lo < hi) {
    const mid = lo + ((hi - lo) >> 1);
    if (canReach(mid)) hi = mid; // works: try lower
    else lo = mid + 1; // fails: need more water
  }
  return lo;
};
