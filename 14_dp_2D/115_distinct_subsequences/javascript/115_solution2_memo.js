/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var numDistinct = function (s, t) {
  const n = s.length, m = t.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(-1));

  const f = (i, j) => {
    if (j === 0) return 1; // t fully matched
    if (i === 0) return 0; // s ran out first
    if (dp[i][j] !== -1) return dp[i][j];

    let ways = f(i - 1, j); // skip s[i-1]
    if (s[i - 1] === t[j - 1]) ways += f(i - 1, j - 1); // pick it

    return (dp[i][j] = ways);
  };

  return f(n, m);
};
