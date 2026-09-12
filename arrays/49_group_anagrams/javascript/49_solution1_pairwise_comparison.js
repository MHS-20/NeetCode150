/**
 * @param {string[]} strs
 * @return {string[][]}
 */
var groupAnagrams = function (strs) {
  const result = [];

  for (const s of strs) {
    let placed = false;
    for (const group of result) {
      if (isAnagram(s, group[0])) {
        group.push(s);
        placed = true;
        break;
      }
    }

    if (!placed) {
      result.push([s]);
    }
  }

  return result;
};

function isAnagram(s, t) {
  if (s.length !== t.length) return false;

  const freq = new Map();
  for (const c of s) freq.set(c, (freq.get(c) || 0) + 1);
  for (const c of t) {
    const count = (freq.get(c) || 0) - 1;
    if (count < 0) return false;
    freq.set(c, count);
  }
  return true;
}
