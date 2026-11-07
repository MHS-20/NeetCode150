#include <vector>

using namespace std;

class Solution {
  vector<int> memo;

  int ways(int i) {
    if (i <= 2)
      return i; // ways(1) = 1, ways(2) = 2
    if (memo[i] != -1)
      return memo[i];
    return memo[i] = ways(i - 1) + ways(i - 2);
  }

public:
  int climbStairs(int n) {
    memo.assign(n + 1, -1);
    return ways(n);
  }
};
