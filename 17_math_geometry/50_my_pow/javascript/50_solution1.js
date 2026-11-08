/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function (x, n) {
  const neg = n < 0;
  let N = Math.abs(n); // bitwise ops would truncate 2^31 to int32

  let res = 1;
  while (N > 0) {
    if (N % 2 === 1) res *= x;
    x *= x;
    N = Math.floor(N / 2);
  }
  return neg ? 1 / res : res;
};
