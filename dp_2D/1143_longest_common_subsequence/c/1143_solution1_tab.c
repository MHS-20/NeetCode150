#include <stdlib.h>
#include <string.h>

static int max(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char *text1, char *text2) {
  int n = strlen(text1), m = strlen(text2);
  int w = m + 1;
  int *dp = calloc((n + 1) * w, sizeof(int)); // dp[i * w + j]

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (text1[i - 1] == text2[j - 1])
        dp[i * w + j] = 1 + dp[(i - 1) * w + (j - 1)];
      else
        dp[i * w + j] = max(dp[(i - 1) * w + j], dp[i * w + (j - 1)]);
    }
  }
  int res = dp[n * w + m];
  free(dp);
  return res;
}
