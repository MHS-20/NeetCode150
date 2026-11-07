/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {boolean}
 */
var wordBreak = function (s, wordDict) {
  const n = s.length;
  const words = new Set(wordDict);
  const dp = new Array(n + 1).fill(false);
  dp[0] = true; // empty prefix is segmentable

  for (let i = 1; i <= n; i++) {
    for (let j = 0; j < i; j++) {
      if (dp[j] && words.has(s.substring(j, i))) {
        dp[i] = true;
        break; // one valid split is enough
      }
    }
  }
  return dp[n];
};
