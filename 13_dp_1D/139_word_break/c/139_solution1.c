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
  bool *dp = calloc(n + 1, sizeof(bool));
  dp[0] = true; // empty prefix is segmentable

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      if (dp[j] && inDict(s + j, i - j, wordDict, wordDictSize)) {
        dp[i] = true;
        break; // one valid split is enough
      }
    }
  }
  bool res = dp[n];
  free(dp);
  return res;
}
