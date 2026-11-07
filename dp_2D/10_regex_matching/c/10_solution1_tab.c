#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const char *S, *Pt;

static bool matches(int i, int j) { // s[i-1] vs p[j-1]
  return Pt[j - 1] == '.' || S[i - 1] == Pt[j - 1];
}

bool isMatch(char *s, char *p) {
  int n = strlen(s), m = strlen(p);
  S = s, Pt = p;
  int w = m + 1;
  bool *dp = calloc((n + 1) * w, sizeof(bool)); // dp[i * w + j]
  dp[0] = true;

  for (int i = 0; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (p[j - 1] == '*') {
        dp[i * w + j] = dp[i * w + (j - 2)]; // zero copies
        if (i > 0 && matches(i, j - 1))
          dp[i * w + j] = dp[i * w + j] || dp[(i - 1) * w + j]; // one more copy
      } else {
        dp[i * w + j] = i > 0 && matches(i, j) && dp[(i - 1) * w + (j - 1)];
      }
    }
  }
  bool res = dp[n * w + m];
  free(dp);
  return res;
}
