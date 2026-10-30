#include <stdbool.h>

bool canJump(int *nums, int numsSize) {
  int mx = 0;

  for (int i = 0; i < numsSize; i++) {
    if (i > mx)
      return false;

    if (i + nums[i] > mx)
      mx = i + nums[i];
    if (mx >= numsSize - 1)
      return true;
  }

  return false;
}
