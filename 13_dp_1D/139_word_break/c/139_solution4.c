#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
  struct TrieNode *children[26];
  bool isWord;
} TrieNode;

static void freeTrie(TrieNode *node) {
  if (!node)
    return;
  for (int c = 0; c < 26; c++)
    freeTrie(node->children[c]);
  free(node);
}

bool wordBreak(char *s, char **wordDict, int wordDictSize) {
  // Build the trie from the dictionary
  TrieNode *root = calloc(1, sizeof(TrieNode));
  for (int w = 0; w < wordDictSize; w++) {
    TrieNode *node = root;
    for (char *c = wordDict[w]; *c; c++) {
      if (!node->children[*c - 'a'])
        node->children[*c - 'a'] = calloc(1, sizeof(TrieNode));
      node = node->children[*c - 'a'];
    }
    node->isWord = true;
  }

  int n = strlen(s);
  bool *dp = calloc(n + 1, sizeof(bool));
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
        dp[k + 1] = true; // s[j..k] is a word, so the first k+1 chars are segmentable
    }
  }
  bool res = dp[n];
  free(dp);
  freeTrie(root);
  return res;
}
