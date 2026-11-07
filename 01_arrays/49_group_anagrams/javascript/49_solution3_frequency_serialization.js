/**
 * @param {string[]} strs
 * @return {string[][]}
 */
var groupAnagrams = function (strs) {
  const groups = new Map();

  for (const s of strs) {
    const key = serializeFrequency(s);
    if (!groups.has(key)) groups.set(key, []);
    groups.get(key).push(s);
  }

  return Array.from(groups.values());
};

function serializeFrequency(s) {
  const alphabet = new Array(26).fill(0);
  for (const c of s) alphabet[c.charCodeAt(0) - "a".charCodeAt(0)]++;

  return alphabet.join("#");
}
