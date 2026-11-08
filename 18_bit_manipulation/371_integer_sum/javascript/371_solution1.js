/**
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
var getSum = function (a, b) {
  // bitwise ops work on int32, so the carry dies after bit 31
  let sum = a ^ b, carry = (a & b) << 1;

  while (carry !== 0) {
    const tmp = (sum & carry) << 1;
    sum ^= carry;
    carry = tmp;
  }

  return sum;
};
