#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *longestPalindrome(char *s) {
  int n = strlen(s), bestLen = 0, bestStart = 0;
  bool *memo = calloc(n * n, sizeof(bool)); // memo[i * n + j]: s[i..j] is a palindrome

  for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
      if (s[i] == s[j] && (j - i < 2 || memo[(i + 1) * n + (j - 1)])) {
        memo[i * n + j] = true;
        if (j - i + 1 > bestLen) {
          bestLen = j - i + 1;
          bestStart = i;
        }
      }
    }
  }
  free(memo);

  char *res = malloc(bestLen + 1);
  memcpy(res, s + bestStart, bestLen);
  res[bestLen] = '\0';
  return res;
}
