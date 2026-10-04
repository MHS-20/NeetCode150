int findDuplicate(int *nums, int numsSize) {
  int left = 1, right = numsSize - 1; // right = n

  while (left < right) {
    int mid = left + (right - left) / 2;

    // count how many numbers are <= mid
    int count = 0;
    for (int i = 0; i < numsSize; i++)
      if (nums[i] <= mid)
        count++;

    if (count > mid)
      right = mid; // duplicate is in [left, mid]
    else
      left = mid + 1; // duplicate is in [mid + 1, right]
  }

  return left;
}
