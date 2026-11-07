/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isAnagram = function (s, t) {
  // for...of iterates by Unicode code point (handles surrogate pairs
  // correctly), unlike indexing/charCodeAt which walk UTF-16 code units.
  const codePoints = (str) => [...str];

  const a = codePoints(s);
  const b = codePoints(t);
  if (a.length !== b.length) return false;

  const counts = new Map();
  for (const c of a) counts.set(c, (counts.get(c) || 0) + 1);
  for (const c of b) {
    const remaining = counts.get(c);
    if (!remaining) return false;
    counts.set(c, remaining - 1);
  }

  return true;
};
