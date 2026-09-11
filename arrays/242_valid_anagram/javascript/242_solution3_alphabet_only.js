// works if chars are a-z only
/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isAnagram = function (s, t) {
  if (s.length !== t.length) return false;

  const count = new Array(26).fill(0);
  const aCode = "a".charCodeAt(0);

  for (let i = 0; i < s.length; i++) {
    count[s.charCodeAt(i) - aCode]++;
    count[t.charCodeAt(i) - aCode]--;
  }

  return count.every((c) => c === 0);
};
