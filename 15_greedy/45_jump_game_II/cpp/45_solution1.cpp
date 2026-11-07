#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int jump(vector<int> &nums) {
    int end = 0, far = 0, count = 0;

    for (int i = 0; i < nums.size() - 1; i++) {
      far = max(far, i + nums[i]);
      if (i == end) {
        // I’ve used up everything reachable with k jumps,
        // so now I’m entering the area that needs k+1 jumps.
        count++;
        end = far;
      }
    }

    return count;
  }
};
