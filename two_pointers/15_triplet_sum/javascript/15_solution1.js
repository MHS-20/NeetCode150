class Solution {
  threeSum(nums) {
    nums.sort((a, b) => a - b);
    const result = [];

    for (let idx = 0; idx < nums.length; idx++) {
      if (idx > 0 && nums[idx] === nums[idx - 1]) continue;

      let left = idx + 1;
      let right = nums.length - 1;

      while (left < right) {
        const total = nums[idx] + nums[left] + nums[right];

        if (total === 0) {
          result.push([nums[idx], nums[left], nums[right]]);
          left++;
          right--;
          while (left < right && nums[left] === nums[left - 1]) left++;
          while (left < right && nums[right] === nums[right + 1]) right--;
        } else if (total > 0) {
          right--;
        } else {
          left++;
        }
      }
    }

    return result;
  }
}
