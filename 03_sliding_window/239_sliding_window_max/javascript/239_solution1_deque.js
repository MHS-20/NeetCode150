class Solution {
  maxSlidingWindow(nums, k) {
    const maxs = [];
    const dq = []; // indices, values decreasing
    let head = 0;

    // i is the right pointer
    // i - k + 1 is the left pointer
    for (let i = 0; i < nums.length; i++) {
      if (head < dq.length && dq[head] < i - k + 1) head++;

      while (head < dq.length && nums[i] > nums[dq[dq.length - 1]]) dq.pop();
      dq.push(i);

      if (i >= k - 1) maxs.push(nums[dq[head]]);
    }

    return maxs;
  }
}
