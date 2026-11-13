/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function (s) {
  let bestStart = 0, bestLen = 0;

  const expand = (l, r) => {
    // bounds first, so s[l] and s[r] are only read when valid
    while (l >= 0 && r < s.length && s[l] === s[r]) {
      l--;
      r++;
    }
    // pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
    const len = r - l - 1;
    if (len > bestLen) {
      bestLen = len;
      bestStart = l + 1;
    }
  };

  for (let i = 0; i < s.length; i++) {
    // odd-length palindromes, centered on s[i]
    expand(i, i);
    // even-length palindromes, centered between s[i] and s[i+1]
    expand(i, i + 1);
  }

  return s.substring(bestStart, bestStart + bestLen);
};
