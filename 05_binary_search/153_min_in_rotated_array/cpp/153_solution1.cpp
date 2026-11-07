#include <vector>
using namespace std;

class Solution {
public:
  int findMin(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] > nums[right])
        left = mid + 1; // min is strictly right of mid
      else
        right = mid; // mid could be the min, keep it
    }

    return nums[left];
  }
};
