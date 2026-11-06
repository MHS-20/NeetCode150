#include <stdlib.h>
#include <string.h>

int numDecodings(char *s) {
  int n = strlen(s);
  int *dp = calloc(n + 1, sizeof(int));
  dp[0] = 1;
  dp[1] = s[0] != '0' ? 1 : 0;

  for (int i = 2; i <= n; i++) {
    if (s[i - 1] != '0')
      dp[i] += dp[i - 1];

    int two = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
    if (two >= 10 && two <= 26)
      dp[i] += dp[i - 2];
  }
  int res = dp[n];
  free(dp);
  return res;
}
