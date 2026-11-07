#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool wordBreak(char *s, char **wordDict, int wordDictSize) {
  int n = strlen(s);
  bool *dp = calloc(n + 1, sizeof(bool));
  dp[0] = true;

  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < wordDictSize; k++) {
      int len = strlen(wordDict[k]);
      // Does word k end exactly at position i?
      if (len <= i && dp[i - len] &&
          strncmp(s + i - len, wordDict[k], len) == 0) {
        dp[i] = true;
        break;
      }
    }
  }
  bool res = dp[n];
  free(dp);
  return res;
}
