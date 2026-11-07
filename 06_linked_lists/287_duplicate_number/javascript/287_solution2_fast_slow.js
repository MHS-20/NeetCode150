var findDuplicate = function (nums) {
  let slow = 0, fast = 0;

  // Phase 1: find a meeting point inside the cycle
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (slow !== fast);

  // Phase 2: find the cycle entrance (the duplicate)
  slow = 0;
  while (slow !== fast) {
    slow = nums[slow];
    fast = nums[fast];
  }

  return slow;
};
