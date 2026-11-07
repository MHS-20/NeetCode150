/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function (s) {
  const n = s.length;
  const dp = Array.from({ length: n }, () => new Array(n).fill(false));
  let bestStart = 0, bestLen = 1;

  // Every single character is a palindrome
  for (let i = 0; i < n; i++) dp[i][i] = true;

  // Fill by increasing substring length
  for (let len = 2; len <= n; len++) {
    for (let i = 0; i + len - 1 < n; i++) {
      const j = i + len - 1;

      if (s[i] === s[j] && (len === 2 || dp[i + 1][j - 1])) {
        dp[i][j] = true;
        if (len > bestLen) {
          bestStart = i;
          bestLen = len;
        }
      }
    }
  }
  return s.substring(bestStart, bestStart + bestLen);
};
