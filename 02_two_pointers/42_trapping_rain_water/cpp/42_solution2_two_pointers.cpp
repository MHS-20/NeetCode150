#include <vector>
using namespace std;
class Solution {
public:
  int trap(vector<int> &height) {
    if (height.empty()) {
      return 0;
    }

    int left = 0, right = height.size() - 1;
    int leftMax = height[left], rightMax = height[right];
    int total = 0;

    while (left < right) {
      if (leftMax < rightMax) {
        left++;
        leftMax = max(leftMax, height[left]);
        total += leftMax - height[left];
      } else {
        right--;
        rightMax = max(rightMax, height[right]);
        total += rightMax - height[right];
      }
    }

    return total;
  }
};
