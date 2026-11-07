#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const char *S, *Pt;
static int w;
static int *dp; // dp[i * w + j], -1 = not computed

static bool matches(int i, int j) { // s[i-1] vs p[j-1]
  return Pt[j - 1] == '.' || S[i - 1] == Pt[j - 1];
}

static bool f(int i, int j) {
  if (j == 0)
    return i == 0; // empty pattern matches only empty s
  if (dp[i * w + j] != -1)
    return dp[i * w + j];

  bool res;
  if (Pt[j - 1] == '*') {
    res = f(i, j - 2); // zero copies
    if (!res && i > 0 && matches(i, j - 1))
      res = f(i - 1, j); // one more copy
  } else {
    res = i > 0 && matches(i, j) && f(i - 1, j - 1);
  }
  dp[i * w + j] = res;
  return res;
}

bool isMatch(char *s, char *p) {
  int n = strlen(s), m = strlen(p);
  S = s, Pt = p, w = m + 1;
  dp = malloc((n + 1) * w * sizeof(int));
  for (int k = 0; k < (n + 1) * w; k++)
    dp[k] = -1;
  bool res = f(n, m);
  free(dp);
  return res;
}
