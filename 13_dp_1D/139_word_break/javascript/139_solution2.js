/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {boolean}
 */
var wordBreak = function (s, wordDict) {
  const n = s.length;
  const words = new Set(wordDict);

  let maxLen = 0;
  for (const w of wordDict) maxLen = Math.max(maxLen, w.length);

  const dp = new Array(n + 1).fill(false);
  dp[0] = true;

  for (let i = 1; i <= n; i++) {
    // A piece longer than maxLen can't be a word, so start j no earlier than
    // i - maxLen
    for (let j = Math.max(0, i - maxLen); j < i; j++) {
      if (dp[j] && words.has(s.substring(j, i))) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[n];
};
