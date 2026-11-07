/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isAnagram = function (s, t) {
  if (s.length !== t.length) return false;

  const sortStr = (str) => [...str].sort().join("");
  return sortStr(s) === sortStr(t);
};
