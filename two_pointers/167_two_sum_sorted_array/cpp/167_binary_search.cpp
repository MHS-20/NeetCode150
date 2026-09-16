#include <vector>
using namespace std;
class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    int i, j;

    for (int idx = 0; idx < numbers.size(); idx++) {
      int diff = target - numbers[idx];
      i = idx + 1;
      j = numbers.size() - 1;

      while (i <= j) {
        int mid = (i + j) / 2;

        if (numbers[mid] == diff)
          return {idx + 1, mid + 1};

        if (numbers[mid] > diff)
          j = mid - 1;
        else
          i = mid + 1;
      }
    }

    return {};
  }
};
