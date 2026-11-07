#include <stdlib.h>
#include <string.h>

int numDistinct(char *s, char *t) {
  int n = strlen(s), m = strlen(t);
  int w = m + 1;
  // dp[i * w + j]; unsigned so intermediate overflow wraps instead of being UB
  unsigned long long *dp = calloc((n + 1) * w, sizeof(unsigned long long));
  for (int i = 0; i <= n; i++)
    dp[i * w] = 1; // empty t: one way

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i * w + j] = dp[(i - 1) * w + j]; // skip cur s[i-1]
      if (s[i - 1] == t[j - 1])
        dp[i * w + j] += dp[(i - 1) * w + (j - 1)]; // pick it
    }
  }
  int res = (int)dp[n * w + m];
  free(dp);
  return res;
}
