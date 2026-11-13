#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int countSubstrings(char *s) {
  int n = strlen(s);
  int count = 0;
  bool *dp = calloc(n * n, sizeof(bool)); // dp[i * n + j]: s[i..j] is a palindrome

  for (int i = 0; i < n; i++) {
    dp[i * n + i] = true;
    count++;
  }

  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;

      if (s[i] == s[j] && (len == 2 || dp[(i + 1) * n + (j - 1)])) {
        dp[i * n + j] = true;
        count++;
      }
    }
  }

  free(dp);
  return count;
}
