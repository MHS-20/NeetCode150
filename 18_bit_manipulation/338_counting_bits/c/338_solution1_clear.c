#include <stdlib.h>

int *countBits(int n, int *returnSize) {
  int *ans = calloc(n + 1, sizeof(int));
  for (int i = 1; i <= n; i++) {
    ans[i] = ans[i & (i - 1)] + 1;
  }
  *returnSize = n + 1;
  return ans;
}
