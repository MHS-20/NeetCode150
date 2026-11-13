/**
 * @param {string} s
 * @return {number}
 */
var countSubstrings = function (s) {
  const n = s.length;
  let count = 0;
  const dp = Array.from({ length: n }, () => new Array(n).fill(false));

  for (let i = 0; i < n; i++) {
    dp[i][i] = true;
    count++;
  }

  for (let len = 2; len <= n; len++) {
    for (let i = 0; i + len - 1 < n; i++) {
      const j = i + len - 1;

      if (s[i] === s[j] && (len === 2 || dp[i + 1][j - 1])) {
        dp[i][j] = true;
        count++;
      }
    }
  }

  return count;
};
