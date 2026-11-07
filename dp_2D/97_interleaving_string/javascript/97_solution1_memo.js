/**
 * @param {string} s1
 * @param {string} s2
 * @param {string} s3
 * @return {boolean}
 */
var isInterleave = function (s1, s2, s3) {
  const n = s1.length, m = s2.length;
  if (n + m !== s3.length) return false;

  const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(-1));

  const f = (i, j) => {
    if (i === n && j === m) return true; // used everything
    if (dp[i][j] !== -1) return dp[i][j];

    const k = i + j; // position in s3
    let res = false;
    if (i < n && s1[i] === s3[k]) res = f(i + 1, j); // take from s1
    if (!res && j < m && s2[j] === s3[k]) res = f(i, j + 1); // take from s2

    return (dp[i][j] = res);
  };

  return f(0, 0);
};
