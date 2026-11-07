/**
 * @param {number} m
 * @param {number} n
 * @return {number}
 */
var uniquePaths = function (m, n) {
  const dp = Array.from({ length: m }, () => new Array(n).fill(0));
  dp[m - 1][n - 1] = 1;

  for (let i = m - 1; i >= 0; i--) {
    for (let j = n - 1; j >= 0; j--) {
      if (i === m - 1 && j === n - 1) continue;
      const down = i + 1 < m ? dp[i + 1][j] : 0;
      const right = j + 1 < n ? dp[i][j + 1] : 0;
      dp[i][j] = down + right;
    }
  }
  return dp[0][0];
};
