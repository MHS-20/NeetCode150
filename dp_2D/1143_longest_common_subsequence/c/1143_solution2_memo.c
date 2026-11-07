#include <stdlib.h>
#include <string.h>

static int max(int a, int b) { return a > b ? a : b; }

static int solve(int i, int j, const char *a, const char *b, int w, int *dp) {
  if (i == 0 || j == 0)
    return 0; // one string is empty
  if (dp[i * w + j] != -1)
    return dp[i * w + j];

  if (a[i - 1] == b[j - 1])
    return dp[i * w + j] = 1 + solve(i - 1, j - 1, a, b, w, dp);
  return dp[i * w + j] =
             max(solve(i - 1, j, a, b, w, dp), solve(i, j - 1, a, b, w, dp));
}

int longestCommonSubsequence(char *text1, char *text2) {
  int n = strlen(text1), m = strlen(text2);
  int w = m + 1;
  int *dp = malloc((n + 1) * w * sizeof(int)); // dp[i * w + j]
  for (int k = 0; k < (n + 1) * w; k++)
    dp[k] = -1;
  int res = solve(n, m, text1, text2, w, dp);
  free(dp);
  return res;
}
