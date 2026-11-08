int getSum(int a, int b) {
  // unsigned: left-shifting a negative int is undefined behaviour
  unsigned sum = a ^ b, carry = (unsigned)(a & b) << 1;

  while (carry != 0) {
    unsigned tmp = (sum & carry) << 1;
    sum ^= carry;
    carry = tmp;
  }

  return sum;
}
