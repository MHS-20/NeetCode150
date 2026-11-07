/**
 * @param {number} m
 * @param {number} n
 * @return {number}
 */
var uniquePaths = function (m, n) {
  const dp = Array.from({ length: m }, () => new Array(n).fill(-1));

  const solve = (i, j) => {
    if (i === 0 && j === 0) return 1; // reached the start
    if (i < 0 || j < 0) return 0; // fell off the grid
    if (dp[i][j] !== -1) return dp[i][j]; // already computed

    const up = solve(i - 1, j);
    const left = solve(i, j - 1);
    return (dp[i][j] = up + left);
  };

  return solve(m - 1, n - 1);
};
