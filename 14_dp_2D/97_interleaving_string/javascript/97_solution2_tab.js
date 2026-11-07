/**
 * @param {string} s1
 * @param {string} s2
 * @param {string} s3
 * @return {boolean}
 */
var isInterleave = function (s1, s2, s3) {
  const n = s1.length, m = s2.length;
  if (n + m !== s3.length) return false;

  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(false));
  dp[0][0] = true; // empty + empty = empty

  for (let i = 0; i <= n; i++) {
    for (let j = 0; j <= m; j++) {
      if (i === 0 && j === 0) continue;
      const k = i + j - 1; // last char of s3 prefix
      const fromS1 = i > 0 && dp[i - 1][j] && s1[i - 1] === s3[k];
      const fromS2 = j > 0 && dp[i][j - 1] && s2[j - 1] === s3[k];
      dp[i][j] = fromS1 || fromS2;
    }
  }
  return dp[n][m];
};
