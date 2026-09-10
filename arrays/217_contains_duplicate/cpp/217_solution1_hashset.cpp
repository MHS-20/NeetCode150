#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> tracker;

    for (int x : nums) {
      if (tracker.contains(x)) {
        return true;
      } else {
        tracker.insert(x);
      }
    }

    return false;
  }
};
