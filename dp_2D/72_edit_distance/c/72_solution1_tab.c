#include <stdlib.h>
#include <string.h>

static int min3(int a, int b, int c) {
  int m = a < b ? a : b;
  return m < c ? m : c;
}

int minDistance(char *word1, char *word2) {
  int n = strlen(word1), m = strlen(word2);
  int w = m + 1;
  int *dp = malloc((n + 1) * w * sizeof(int)); // dp[i * w + j]

  for (int i = 0; i <= n; i++)
    dp[i * w] = i; // delete all
  for (int j = 0; j <= m; j++)
    dp[j] = j; // insert all

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i * w + j] = dp[(i - 1) * w + (j - 1)];
      else
        dp[i * w + j] = 1 + min3(dp[(i - 1) * w + j],        // delete
                                 dp[i * w + (j - 1)],        // insert
                                 dp[(i - 1) * w + (j - 1)]); // replace
    }
  }
  int res = dp[n * w + m];
  free(dp);
  return res;
}
