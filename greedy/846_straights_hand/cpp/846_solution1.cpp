#include <map>
#include <vector>

using namespace std;

class Solution {
public:
  bool isNStraightHand(vector<int> &hand, int groupSize) {
    if (hand.size() % groupSize != 0)
      return false;

    map<int, int> count;
    for (int c : hand)
      count[c]++;

    while (!count.empty()) {
      int start = count.begin()->first; // smallest remaining card

      for (int v = start; v < start + groupSize; v++) {
        auto it = count.find(v);
        if (it == count.end())
          return false; // missing value, group can't be built
        if (--it->second == 0)
          count.erase(it); // drop values that are used up
      }
    }

    return true;
  }
};
