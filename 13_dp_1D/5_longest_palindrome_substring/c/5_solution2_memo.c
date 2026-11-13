#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// memo[i * n + j]: -1 unknown, 0 no, 1 yes
static bool isPal(const char *s, int n, signed char *memo, int i, int j) {
  if (i >= j)
    return true; // length 0 or 1
  if (memo[i * n + j] == -1)
    memo[i * n + j] = s[i] == s[j] && isPal(s, n, memo, i + 1, j - 1);
  return memo[i * n + j];
}

char *longestPalindrome(char *s) {
  int n = strlen(s), bestStart = 0, bestLen = 0;
  signed char *memo = malloc(n * n);
  memset(memo, -1, n * n);

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (j - i + 1 > bestLen && isPal(s, n, memo, i, j)) {
        bestLen = j - i + 1;
        bestStart = i;
      }
    }
  }
  free(memo);

  char *res = malloc(bestLen + 1);
  memcpy(res, s + bestStart, bestLen);
  res[bestLen] = '\0';
  return res;
}
