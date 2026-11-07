/**
 * @param {number[][]} matrix
 * @return {number}
 */
var longestIncreasingPath = function (matrix) {
  const m = matrix.length, n = matrix[0].length;
  const dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];
  const dp = Array.from({ length: m }, () => new Array(n).fill(0)); // 0 = not computed

  const dfs = (i, j) => {
    if (dp[i][j] !== 0) return dp[i][j]; // already computed

    let best = 1; // the cell alone
    for (const [di, dj] of dirs) {
      const ni = i + di, nj = j + dj;
      if (ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] > matrix[i][j]) {
        best = Math.max(best, 1 + dfs(ni, nj));
      }
    }
    return (dp[i][j] = best);
  };

  let res = 0;
  for (let i = 0; i < m; i++)
    for (let j = 0; j < n; j++) res = Math.max(res, dfs(i, j));
  return res;
};
