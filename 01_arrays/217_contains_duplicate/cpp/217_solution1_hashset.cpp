#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> tracker;
    tracker.reserve(nums.size());

    for (int x : nums) {
      if (!tracker.insert(x).second)
        return true;
    }

    return false;
  }
};
