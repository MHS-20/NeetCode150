int singleNumber(int *nums, int numsSize) {
  int xr = 0;
  for (int i = 0; i < numsSize; i++)
    xr = xr ^ nums[i];
  return xr;
}
