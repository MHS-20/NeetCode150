/**
 * @param {string[]} words
 * @return {string}
 */
var foreignDictionary = function (words) {
  const adj = new Map(); // letter -> set of letters that must come after it
  const indeg = new Map();
  for (const w of words)
    for (const c of w)
      if (!adj.has(c)) {
        adj.set(c, new Set());
        indeg.set(c, 0);
      }

  for (let i = 0; i + 1 < words.length; i++) {
    const a = words[i];
    const b = words[i + 1];
    const len = Math.min(a.length, b.length);
    let j = 0;
    while (j < len && a[j] === b[j]) j++;

    if (j === len) {
      if (a.length > b.length) return ""; // b is a proper prefix of a: invalid
      continue;
    }
    if (!adj.get(a[j]).has(b[j])) { // avoid double-counting
      adj.get(a[j]).add(b[j]);
      indeg.set(b[j], indeg.get(b[j]) + 1);
    }
  }

  // Kahn's algorithm
  let q = [...indeg.keys()].filter((c) => indeg.get(c) === 0);
  let result = "";
  while (q.length > 0) {
    const next = []; // fresh array per level: Array.shift() is O(n)
    for (const u of q) {
      result += u;
      for (const v of adj.get(u)) {
        indeg.set(v, indeg.get(v) - 1);
        if (indeg.get(v) === 0) next.push(v);
      }
    }
    q = next;
  }

  return result.length === adj.size ? result : "";
};
