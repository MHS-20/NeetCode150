/**
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
var minDistance = function (word1, word2) {
  const n = word1.length, m = word2.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(-1));

  const f = (i, j) => {
    if (i === 0) return j; // insert the remaining j chars
    if (j === 0) return i; // delete the remaining i chars
    if (dp[i][j] !== -1) return dp[i][j];

    if (word1[i - 1] === word2[j - 1]) return (dp[i][j] = f(i - 1, j - 1)); // free match

    const del = f(i - 1, j);
    const ins = f(i, j - 1);
    const rep = f(i - 1, j - 1);
    return (dp[i][j] = 1 + Math.min(del, ins, rep));
  };

  return f(n, m);
};
