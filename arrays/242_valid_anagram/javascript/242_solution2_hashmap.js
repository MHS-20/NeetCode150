/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isAnagram = function (s, t) {
  if (s.length !== t.length) return false;

  const counts = new Map();
  for (const c of s) {
    counts.set(c, (counts.get(c) || 0) + 1);
  }

  for (const c of t) {
    const remaining = counts.get(c);
    if (!remaining) return false;
    counts.set(c, remaining - 1);
  }

  return true;
};
