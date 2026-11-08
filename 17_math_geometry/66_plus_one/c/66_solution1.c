#include <stdlib.h>
#include <string.h>

int *plusOne(int *digits, int digitsSize, int *returnSize) {
  int *res = malloc(sizeof(int) * (digitsSize + 1));
  memcpy(res + 1, digits, sizeof(int) * digitsSize);

  for (int i = digitsSize; i >= 1; i--) {
    if (res[i] < 9) {
      res[i]++;
      *returnSize = digitsSize;
      memmove(res, res + 1, sizeof(int) * digitsSize);
      return res;
    }
    res[i] = 0;
  }
  res[0] = 1;
  *returnSize = digitsSize + 1;
  return res;
}
