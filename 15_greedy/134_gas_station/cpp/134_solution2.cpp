#include <vector>

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int total = 0, cur = 0, start = 0;
    for (int i = 0; i < gas.size(); i++) {
      int diff = gas[i] - cost[i];
      total += diff;
      cur += diff;
      if (cur < 0) {
        start = i + 1;
        cur = 0;
      }
    }
    return total < 0 ? -1 : start;
  }
};
