#include <vector>

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int sumgas = 0, sumcost = 0;
    for (int i = 0; i < gas.size(); i++) {
      sumgas += gas[i];
      sumcost += cost[i];
    }

    if (sumcost > sumgas)
      return -1;

    int start = 0, curGas = 0, curPos = 0;
    for (;;) {
      curGas += gas[curPos];
      curGas -= cost[curPos];

      curPos++;
      curPos = curPos % gas.size();

      if (curPos == start)
        return start;

      if (curGas < 0) {
        start = curPos;
        curGas = 0;
      }
    }
  }
};
