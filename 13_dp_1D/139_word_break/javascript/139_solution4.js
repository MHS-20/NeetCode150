class TrieNode {
  constructor() {
    this.children = new Array(26).fill(null);
    this.isWord = false;
  }
}

/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {boolean}
 */
var wordBreak = function (s, wordDict) {
  const idx = (c) => c.charCodeAt(0) - 97;

  // Build the trie from the dictionary
  const root = new TrieNode();
  for (const w of wordDict) {
    let node = root;
    for (const c of w) {
      if (!node.children[idx(c)]) node.children[idx(c)] = new TrieNode();
      node = node.children[idx(c)];
    }
    node.isWord = true;
  }

  const n = s.length;
  const dp = new Array(n + 1).fill(false);
  dp[0] = true;

  for (let j = 0; j < n; j++) {
    if (!dp[j]) continue; // only start a word where the prefix is segmentable

    // Walk s and the trie together, starting at j
    let node = root;
    for (let k = j; k < n; k++) {
      node = node.children[idx(s[k])];
      if (!node) break; // no dictionary word continues this way
      if (node.isWord) dp[k + 1] = true; // s[j..k] is a word, so the first k+1 chars are segmentable
    }
  }
  return dp[n];
};
