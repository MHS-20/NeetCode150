#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    int count = 0;
    int max = 0;
    unordered_set<int> set(nums.begin(), nums.end());

    for (int n : set) {
      if (!set.contains(n - 1)) {
        count = 1;

        while (set.contains(n + count))
          count++;

        if (count > max)
          max = count;
      }
    }

    return max;
  }
};
