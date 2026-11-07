#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const char *a, *b, *c;
static int n, m;
static int *dp; // dp[i * (m + 1) + j], -1 = not computed

static bool f(int i, int j) {
  if (i == n && j == m)
    return true; // used everything
  int *memo = &dp[i * (m + 1) + j];
  if (*memo != -1)
    return *memo;

  int k = i + j; // position in s3
  bool res = false;
  if (i < n && a[i] == c[k])
    res = f(i + 1, j); // take from s1
  if (!res && j < m && b[j] == c[k])
    res = f(i, j + 1); // take from s2

  *memo = res;
  return res;
}

bool isInterleave(char *s1, char *s2, char *s3) {
  n = strlen(s1), m = strlen(s2);
  if (n + m != (int)strlen(s3))
    return false;

  a = s1, b = s2, c = s3;
  dp = malloc((n + 1) * (m + 1) * sizeof(int));
  for (int k = 0; k < (n + 1) * (m + 1); k++)
    dp[k] = -1;
  bool res = f(0, 0);
  free(dp);
  return res;
}
