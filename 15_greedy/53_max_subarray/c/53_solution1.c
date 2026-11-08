#include <limits.h>

int maxSubArray(int *nums, int numsSize) {
  int sum = 0;
  int mx = INT_MIN;

  for (int i = 0; i < numsSize; i++) {
    sum += nums[i];
    if (sum > mx)
      mx = sum;
    if (sum < 0)
      sum = 0; // a negative prefix only lowers what follows
  }

  return mx;
}
