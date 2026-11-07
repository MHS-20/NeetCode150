class Solution {
  maxArea(height) {
    let left = 0;
    let right = height.length - 1;
    let mx = 0;

    while (left < right) {
      const width = right - left;
      const h = Math.min(height[left], height[right]);
      mx = Math.max(mx, h * width);

      if (height[left] > height[right]) right--;
      else left++;
    }

    return mx;
  }
}
