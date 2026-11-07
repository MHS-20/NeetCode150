#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int f(int l, int r, vector<int> &a, vector<vector<int>> &dp) {
    if (r - l < 2)
      return 0; // nothing strictly between l and r
    if (dp[l][r] != -1)
      return dp[l][r];

    int best = 0;
    for (int k = l + 1; k < r; k++) { // k = last balloon burst in (l, r)
      int coins = a[l] * a[k] * a[r] + f(l, k, a, dp) + f(k, r, a, dp);
      best = max(best, coins);
    }
    return dp[l][r] = best;
  }

  int maxCoins(vector<int> &nums) {
    vector<int> a = {1};
    a.insert(a.end(), nums.begin(), nums.end());
    a.push_back(1); // pad: [1, nums..., 1]

    int N = a.size();
    vector<vector<int>> dp(N, vector<int>(N, -1));
    return f(0, N - 1, a, dp);
  }
};
