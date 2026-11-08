#include <limits.h>

int reverse(int x) {
  int res = 0;

  while (x != 0) {
    int d = x % 10;
    x = x / 10;

    if (res > INT_MAX / 10 || res < INT_MIN / 10)
      return 0;
    res = res * 10 + d;
  }

  return res;
}
