/**
 * @param {string} s
 * @param {string} p
 * @return {boolean}
 */
var isMatch = function (s, p) {
  const n = s.length, m = p.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(false));
  dp[0][0] = true;

  const matches = (i, j) => p[j - 1] === '.' || s[i - 1] === p[j - 1]; // s[i-1] vs p[j-1]

  for (let i = 0; i <= n; i++) {
    for (let j = 1; j <= m; j++) {
      if (p[j - 1] === '*') {
        dp[i][j] = dp[i][j - 2]; // zero copies
        if (i > 0 && matches(i, j - 1)) dp[i][j] = dp[i][j] || dp[i - 1][j]; // one more copy
      } else {
        dp[i][j] = i > 0 && matches(i, j) && dp[i - 1][j - 1];
      }
    }
  }
  return dp[n][m];
};
