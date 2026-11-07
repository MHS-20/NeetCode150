#include <deque>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> maxs;
    deque<int> dq;

    // i is the right pointer
    // i - k + 1 is the left pointer
    for (int i = 0; i < nums.size(); i++) {
      if (!dq.empty() && dq.front() < i - k + 1) {
        dq.pop_front();
      }

      while (!dq.empty() && nums[i] > nums[dq.back()])
        dq.pop_back();
      dq.push_back(i);

      if (i >= k - 1)
        maxs.push_back(nums[dq.front()]);
    }

    return maxs;
  }
};
