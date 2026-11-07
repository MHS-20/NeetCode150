/**
 * @param {string[]} words
 * @return {string}
 */
var foreignDictionary = function (words) {
  const adj = new Map(); // letter -> set of letters that must come after it
  const state = new Map(); // 0 = unvisited, 1 = visiting, 2 = done
  const result = [];

  // Returns false if a cycle is found
  const dfs = (u) => {
    state.set(u, 1);
    for (const v of adj.get(u)) {
      if (state.get(v) === 1) return false; // back edge: cycle
      if (state.get(v) === 0 && !dfs(v)) return false; // propagate failure
    }
    state.set(u, 2);
    result.push(u); // post-order
    return true;
  };

  // 1. Register every letter
  for (const w of words)
    for (const c of w)
      if (!adj.has(c)) {
        adj.set(c, new Set());
        state.set(c, 0);
      }

  // 2. Build edges (no in-degree needed)
  for (let i = 0; i + 1 < words.length; i++) {
    const a = words[i], b = words[i + 1];
    const len = Math.min(a.length, b.length);
    let j = 0;
    while (j < len && a[j] === b[j]) j++;

    if (j === len) {
      if (a.length > b.length) return "";
      continue;
    }
    adj.get(a[j]).add(b[j]); // duplicates are harmless here
  }

  // 3. DFS from every unvisited letter
  for (const c of adj.keys()) if (state.get(c) === 0 && !dfs(c)) return "";

  // 4. Post-order is reversed topological order
  return result.reverse().join("");
};
