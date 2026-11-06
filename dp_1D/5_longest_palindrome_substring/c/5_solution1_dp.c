#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *longestPalindrome(char *s) {
  int n = strlen(s);
  bool *dp = calloc(n * n, sizeof(bool)); // dp[i * n + j]: s[i..j] is a palindrome
  int bestStart = 0, bestLen = 1;

  // Every single character is a palindrome
  for (int i = 0; i < n; i++)
    dp[i * n + i] = true;

  // Fill by increasing substring length
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;

      if (s[i] == s[j] && (len == 2 || dp[(i + 1) * n + (j - 1)])) {
        dp[i * n + j] = true;
        if (len > bestLen) {
          bestStart = i;
          bestLen = len;
        }
      }
    }
  }
  free(dp);

  char *res = malloc(bestLen + 1);
  memcpy(res, s + bestStart, bestLen);
  res[bestLen] = '\0';
  return res;
}
