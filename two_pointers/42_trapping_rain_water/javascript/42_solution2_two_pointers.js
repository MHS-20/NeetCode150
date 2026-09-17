class Solution {
  trap(height) {
    if (height.length === 0) return 0;

    let left = 0;
    let right = height.length - 1;
    let leftMax = height[left];
    let rightMax = height[right];
    let total = 0;

    while (left < right) {
      if (leftMax < rightMax) {
        left++;
        leftMax = Math.max(leftMax, height[left]);
        total += leftMax - height[left];
      } else {
        right--;
        rightMax = Math.max(rightMax, height[right]);
        total += rightMax - height[right];
      }
    }

    return total;
  }
}
