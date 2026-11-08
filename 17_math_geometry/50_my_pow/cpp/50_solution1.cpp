class Solution {
public:
  double myPow(double x, int n) {
    long long N = n;
    bool neg = N < 0;
    if (neg)
      N = -N;

    double res = 1;
    while (N > 0) {
      if (N & 1)
        res *= x;
      x *= x;
      N >>= 1;
    }
    return neg ? 1 / res : res;
  }
};
