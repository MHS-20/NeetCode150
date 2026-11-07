/**
 * @param {string} text1
 * @param {string} text2
 * @return {number}
 */
var longestCommonSubsequence = function (text1, text2) {
  const n = text1.length, m = text2.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(-1));

  const solve = (i, j) => {
    if (i === 0 || j === 0) return 0; // one string is empty
    if (dp[i][j] !== -1) return dp[i][j];

    if (text1[i - 1] === text2[j - 1]) return (dp[i][j] = 1 + solve(i - 1, j - 1));
    return (dp[i][j] = Math.max(solve(i - 1, j), solve(i, j - 1)));
  };

  return solve(n, m);
};
