/**
 * @param {string} s
 * @return {number}
 */
var numDecodings = function (s) {
  const n = s.length;
  const dp = new Array(n + 1).fill(0);
  dp[0] = 1;
  dp[1] = s[0] !== '0' ? 1 : 0;

  for (let i = 2; i <= n; i++) {
    if (s[i - 1] !== '0') dp[i] += dp[i - 1];

    const two = Number(s.substring(i - 2, i));
    if (two >= 10 && two <= 26) dp[i] += dp[i - 2];
  }
  return dp[n];
};
