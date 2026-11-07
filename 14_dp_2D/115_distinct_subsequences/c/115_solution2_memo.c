#include <stdlib.h>
#include <string.h>

static const char *S, *T;
static int w;
static long long *dp; // dp[i * w + j], -1 = not computed

static long long f(int i, int j) {
  if (j == 0)
    return 1; // t fully matched
  if (i == 0)
    return 0; // s ran out first
  if (dp[i * w + j] != -1)
    return dp[i * w + j];

  long long ways = f(i - 1, j); // skip s[i-1]
  if (S[i - 1] == T[j - 1])
    ways += f(i - 1, j - 1); // pick it

  // keep within u32 range so nothing overflows and -1 stays a free sentinel
  return dp[i * w + j] = ways & 0xFFFFFFFFLL;
}

int numDistinct(char *s, char *t) {
  int n = strlen(s), m = strlen(t);
  S = s, T = t, w = m + 1;
  dp = malloc((n + 1) * w * sizeof(long long));
  for (int k = 0; k < (n + 1) * w; k++)
    dp[k] = -1;
  int res = (int)f(n, m);
  free(dp);
  return res;
}
