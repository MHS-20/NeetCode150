#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// C has no built-in hash set, so check the piece against each word
static bool inDict(const char *piece, int len, char **wordDict,
                   int wordDictSize) {
  for (int k = 0; k < wordDictSize; k++) {
    if ((int)strlen(wordDict[k]) == len &&
        strncmp(piece, wordDict[k], len) == 0)
      return true;
  }
  return false;
}

bool wordBreak(char *s, char **wordDict, int wordDictSize) {
  int n = strlen(s);

  int maxLen = 0;
  for (int k = 0; k < wordDictSize; k++) {
    int len = strlen(wordDict[k]);
    if (len > maxLen)
      maxLen = len;
  }

  bool *dp = calloc(n + 1, sizeof(bool));
  dp[0] = true;

  for (int i = 1; i <= n; i++) {
    // A piece longer than maxLen can't be a word, so start j no earlier than
    // i - maxLen
    for (int j = i - maxLen > 0 ? i - maxLen : 0; j < i; j++) {
      if (dp[j] && inDict(s + j, i - j, wordDict, wordDictSize)) {
        dp[i] = true;
        break;
      }
    }
  }
  bool res = dp[n];
  free(dp);
  return res;
}
