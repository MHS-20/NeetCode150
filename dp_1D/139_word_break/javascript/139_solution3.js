/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {boolean}
 */
var wordBreak = function (s, wordDict) {
  const n = s.length;
  const dp = new Array(n + 1).fill(false);
  dp[0] = true;

  for (let i = 1; i <= n; i++) {
    for (const w of wordDict) {
      const len = w.length;
      // Does word w end exactly at position i?
      if (len <= i && dp[i - len] && s.startsWith(w, i - len)) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[n];
};
