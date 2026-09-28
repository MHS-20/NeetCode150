#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int minEatingSpeed(vector<int> &piles, int h) {
    int left = 1, right = *max_element(piles.begin(), piles.end());
    int k = right;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      long long sum = 0;

      for (int n : piles)
        sum += ((long long)n + mid - 1) / mid;

      if (sum > h)
        left = mid + 1;
      if (sum <= h) {
        k = min(k, mid);
        right = mid - 1;
      }
    }

    return k;
  }
};
