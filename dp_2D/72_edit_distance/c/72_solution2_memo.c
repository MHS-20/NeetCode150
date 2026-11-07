#include <stdlib.h>
#include <string.h>

static const char *A, *B;
static int w;
static int *dp; // dp[i * w + j], -1 = not computed

static int min3(int a, int b, int c) {
  int m = a < b ? a : b;
  return m < c ? m : c;
}

static int f(int i, int j) {
  if (i == 0)
    return j; // insert the remaining j chars
  if (j == 0)
    return i; // delete the remaining i chars
  if (dp[i * w + j] != -1)
    return dp[i * w + j];

  if (A[i - 1] == B[j - 1])
    return dp[i * w + j] = f(i - 1, j - 1); // free match

  int del = f(i - 1, j);
  int ins = f(i, j - 1);
  int rep = f(i - 1, j - 1);
  return dp[i * w + j] = 1 + min3(del, ins, rep);
}

int minDistance(char *word1, char *word2) {
  int n = strlen(word1), m = strlen(word2);
  A = word1, B = word2, w = m + 1;
  dp = malloc((n + 1) * w * sizeof(int));
  for (int k = 0; k < (n + 1) * w; k++)
    dp[k] = -1;
  int res = f(n, m);
  free(dp);
  return res;
}
