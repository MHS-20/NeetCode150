/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function (s) {
  // Grow outward from the center (left, right) while the ends match.
  // Returns the length of the palindrome found.
  const expand = (left, right) => {
    while (left >= 0 && right < s.length && s[left] === s[right]) {
      left--;
      right++;
    }
    return right - left - 1;
  };

  let bestStart = 0, bestLen = 0;

  for (let i = 0; i < s.length; i++) {
    const oddLen = expand(i, i); // center on a character: "aba"
    const evenLen = expand(i, i + 1); // center between two characters: "abba"
    const len = Math.max(oddLen, evenLen);

    if (len > bestLen) {
      bestLen = len;
      bestStart = i - Math.floor((len - 1) / 2);
    }
  }
  return s.substring(bestStart, bestStart + bestLen);
};
