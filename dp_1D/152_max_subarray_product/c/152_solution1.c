static int max(int a, int b) { return a > b ? a : b; }
static int min(int a, int b) { return a < b ? a : b; }

int maxProduct(int *nums, int numsSize) {
  int curMax = nums[0], curMin = nums[0], best = nums[0];

  for (int i = 1; i < numsSize; i++) {
    int x = nums[i];
    int a = curMax * x, b = curMin * x;

    curMax = max(x, max(a, b));
    curMin = min(x, min(a, b));
    best = max(best, curMax);
  }
  return best;
}
