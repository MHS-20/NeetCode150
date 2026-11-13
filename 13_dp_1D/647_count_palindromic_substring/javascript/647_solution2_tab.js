/**
 * @param {string} s
 * @return {number}
 */
var countSubstrings = function (s) {
  const n = s.length;
  let count = 0;
  const memo = Array.from({ length: n }, () => new Array(n).fill(false));

  for (let i = n - 1; i >= 0; i--) {
    for (let j = i; j < n; j++) {
      if (s[i] === s[j] && (j - i < 2 || memo[i + 1][j - 1])) {
        memo[i][j] = true;
        count++;
      }
    }
  }

  return count;
};
