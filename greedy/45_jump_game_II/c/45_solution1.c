int jump(int *nums, int numsSize) {
  int end = 0, far = 0, count = 0;

  for (int i = 0; i < numsSize - 1; i++) {
    if (i + nums[i] > far)
      far = i + nums[i];
    if (i == end) {
      // I've used up everything reachable with k jumps,
      // so now I'm entering the area that needs k+1 jumps.
      count++;
      end = far;
    }
  }

  return count;
}
