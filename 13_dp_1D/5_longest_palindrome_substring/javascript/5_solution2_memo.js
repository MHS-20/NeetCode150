/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function (s) {
  const n = s.length;
  const memo = Array.from({ length: n }, () => new Array(n).fill(-1)); // -1 unknown, 0 no, 1 yes

  const isPal = (i, j) => {
    if (i >= j) return true; // length 0 or 1
    if (memo[i][j] === -1) memo[i][j] = s[i] === s[j] && isPal(i + 1, j - 1) ? 1 : 0;
    return memo[i][j] === 1;
  };

  let bestStart = 0, bestLen = 0;
  for (let i = 0; i < n; i++) {
    for (let j = i; j < n; j++) {
      if (j - i + 1 > bestLen && isPal(i, j)) {
        bestLen = j - i + 1;
        bestStart = i;
      }
    }
  }
  return s.substring(bestStart, bestStart + bestLen);
};
