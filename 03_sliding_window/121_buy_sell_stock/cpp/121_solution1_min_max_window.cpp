#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int mn = INT_MAX;
    int profit = 0;
    for (int p : prices) {
      mn = min(mn, p);
      profit = max(profit, p - mn);
    }
    return profit;
  }
};
