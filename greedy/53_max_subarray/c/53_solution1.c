#include <limits.h>

int maxSubArray(int *nums, int numsSize) {
  int sum = 0;
  int mx = INT_MIN;

  for (int i = 0; i < numsSize; i++) {
    sum += nums[i];
    if (sum > mx)
      mx = sum;
    if (sum < 0)
      sum = nums[i] < 0 ? 0 : nums[i];
  }

  return mx;
}
