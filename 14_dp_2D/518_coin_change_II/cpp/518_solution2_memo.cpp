#include <vector>

using namespace std;

class Solution {
public:
  int f(int i, int x, vector<int> &coins, vector<vector<int>> &dp) {
    if (x == 0)
      return 1; // made the amount
    if (i == coins.size())
      return 0; // out of coins
    if (dp[i][x] != -1)
      return dp[i][x];

    int skip = f(i + 1, x, coins, dp); // never use coin i again
    int take = 0;
    if (coins[i] <= x)
      take = f(i, x - coins[i], coins,
               dp); // use coin i, stay at i (reuse allowed)

    return dp[i][x] = skip + take;
  }

  int change(int amount, vector<int> &coins) {
    vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, -1));
    return f(0, amount, coins, dp);
  }
};
