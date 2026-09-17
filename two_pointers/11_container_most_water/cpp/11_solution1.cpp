#include <vector>
using namespace std;
class Solution {
public:
  int maxArea(vector<int> &height) {
    int mx = 0, left = 0, right = height.size() - 1;

    while (left < right) {
      int width = right - left;
      int h = min(height[left], height[right]);
      mx = max(mx, h * width);
      if (height[left] > height[right]) {
        right--;
      } else {
        left++;
      }
    }

    return mx;
  }
};
