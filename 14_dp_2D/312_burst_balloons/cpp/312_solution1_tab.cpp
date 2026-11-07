#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxCoins(vector<int> &nums) {
    vector<int> a = {1};
    a.insert(a.end(), nums.begin(), nums.end());
    a.push_back(1);

    int N = a.size();
    vector<vector<int>> dp(N, vector<int>(N, 0)); // len < 2 → 0 already

    for (int len = 2; len < N; len++) { // distance between walls
      for (int l = 0; l + len < N; l++) {
        int r = l + len;
        for (int k = l + 1; k < r; k++) {
          dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[k] * a[r]);
        }
      }
    }
    return dp[0][N - 1];
  }
};
