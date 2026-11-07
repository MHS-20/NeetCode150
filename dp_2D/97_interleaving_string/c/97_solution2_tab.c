#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isInterleave(char *s1, char *s2, char *s3) {
  int n = strlen(s1), m = strlen(s2);
  if (n + m != (int)strlen(s3))
    return false;

  int w = m + 1;
  bool *dp = calloc((n + 1) * w, sizeof(bool)); // dp[i * w + j]
  dp[0] = true;                                 // empty + empty = empty

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0 && j == 0)
        continue;
      int k = i + j - 1; // last char of s3 prefix
      bool fromS1 = i > 0 && dp[(i - 1) * w + j] && s1[i - 1] == s3[k];
      bool fromS2 = j > 0 && dp[i * w + (j - 1)] && s2[j - 1] == s3[k];
      dp[i * w + j] = fromS1 || fromS2;
    }
  }
  bool res = dp[n * w + m];
  free(dp);
  return res;
}
