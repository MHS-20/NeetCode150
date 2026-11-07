/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var numDistinct = function (s, t) {
  const n = s.length, m = t.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(0));
  for (let i = 0; i <= n; i++) dp[i][0] = 1; // empty t: one way

  for (let i = 1; i <= n; i++) {
    for (let j = 1; j <= m; j++) {
      dp[i][j] = dp[i - 1][j]; // skip cur s[i-1]
      if (s[i - 1] === t[j - 1]) dp[i][j] += dp[i - 1][j - 1]; // pick it
    }
  }
  return dp[n][m];
};
