#include <iostream>
using namespace std;

// PROBLEM: Max XOR
// You are given an integer n that is divisible by 4.
// Find an integer x such that:
//   - x >= n
//   - x has the same number of bits in binary as n
//   - v = n ^ (n+1) ^ (n+2) ^ ... ^ x is as large as possible
// (^ is bitwise XOR.)
// If several values of x give the same maximum v, return the smallest x.
//
// Example: n = 4, possible x are 4, 5, 6, 7
//   x = 4 -> v = 4
//   x = 5 -> v = 4^5 = 1
//   x = 6 -> v = 4^5^6 = 7
//   x = 7 -> v = 4^5^6^7 = 0
//   The maximum is v = 7 at x = 6, so return 6.

// SOLUTION IDEA:
// XOR of 0..k repeats every 4: k%4==0 -> k, 1 -> 1, 2 -> k+1, 3 -> 0.
// Since n % 4 == 0, XOR of 0..(n-1) is 0, so v = XOR of 0..x.
// The maximum with b bits is all ones (2^b - 1), reached first at x = 2^b - 2.

long long maxXor(long long n) {
  long long p = 1;
  while (p <= n) {
    p = p * 2; // p = 2^b, the first power of 2 bigger than n
  }
  return p - 2;
}

int main() {
  long long n;
  cin >> n;
  cout << maxXor(n) << endl;
  return 0;
}
