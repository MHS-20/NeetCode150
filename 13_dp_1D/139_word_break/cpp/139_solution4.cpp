#include <string>
#include <vector>

using namespace std;

class Solution {
  struct TrieNode {
    TrieNode *children[26] = {};
    bool isWord = false;
  };

public:
  bool wordBreak(string s, vector<string> &wordDict) {
    // Build the trie from the dictionary
    TrieNode *root = new TrieNode();
    for (auto &w : wordDict) {
      TrieNode *node = root;
      for (char c : w) {
        if (!node->children[c - 'a'])
          node->children[c - 'a'] = new TrieNode();
        node = node->children[c - 'a'];
      }
      node->isWord = true;
    }

    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int j = 0; j < n; j++) {
      if (!dp[j])
        continue; // only start a word where the prefix is segmentable

      // Walk s and the trie together, starting at j
      TrieNode *node = root;
      for (int k = j; k < n; k++) {
        node = node->children[s[k] - 'a'];
        if (!node)
          break; // no dictionary word continues this way
        if (node->isWord)
          dp[k + 1] =
              true; // s[j..k] is a word, so the first k+1 chars are segmentable
      }
    }
    return dp[n];
  }
};
