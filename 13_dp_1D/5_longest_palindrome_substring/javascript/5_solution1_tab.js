/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function (s) {
  const n = s.length;
  const memo = Array.from({ length: n }, () => new Array(n).fill(false));
  let bestStart = 0, bestLen = 0;

  for (let i = n - 1; i >= 0; i--) {
    for (let j = i; j < n; j++) {
      if (s[i] === s[j] && (j - i < 2 || memo[i + 1][j - 1])) {
        memo[i][j] = true;
        if (j - i + 1 > bestLen) {
          bestLen = j - i + 1;
          bestStart = i;
        }
      }
    }
  }

  return s.substring(bestStart, bestStart + bestLen);
};
