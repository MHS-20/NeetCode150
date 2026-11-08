const INT_MAX = 2 ** 31 - 1, INT_MIN = -(2 ** 31);

/**
 * @param {number} x
 * @return {number}
 */
var reverse = function (x) {
  let res = 0;

  while (x !== 0) {
    const d = x % 10;
    x = Math.trunc(x / 10);

    if (res > Math.trunc(INT_MAX / 10) || res < Math.trunc(INT_MIN / 10))
      return 0;
    res = res * 10 + d;
  }

  return res;
};
