/**
 * @param {string} s
 * @param {string} p
 * @return {boolean}
 */
var isMatch = function (s, p) {
  const n = s.length, m = p.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(-1));

  const matches = (i, j) => p[j - 1] === '.' || s[i - 1] === p[j - 1]; // s[i-1] vs p[j-1]

  const f = (i, j) => {
    if (j === 0) return i === 0; // empty pattern matches only empty s
    if (dp[i][j] !== -1) return dp[i][j];

    let res;
    if (p[j - 1] === '*') {
      res = f(i, j - 2); // zero copies
      if (!res && i > 0 && matches(i, j - 1)) res = f(i - 1, j); // one more copy
    } else {
      res = i > 0 && matches(i, j) && f(i - 1, j - 1);
    }
    return (dp[i][j] = res);
  };

  return f(n, m);
};
