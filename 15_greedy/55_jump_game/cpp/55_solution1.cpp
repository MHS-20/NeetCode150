#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  bool canJump(vector<int> &nums) {
    int mx = 0;

    for (int i = 0; i < nums.size(); i++) {
      if (i > mx)
        return false;

      int j = i + nums[i];
      mx = max(mx, j);
      if (mx >= (int)nums.size() - 1)
        return true;
    }

    return false;
  }
};
