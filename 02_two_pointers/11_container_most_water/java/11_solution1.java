class Solution {
    public int maxArea(int[] height) {
        int left = 0, right = height.length - 1, mx = 0;

        while (left < right) {
            int width = right - left;
            int h = Math.min(height[left], height[right]);
            mx = Math.max(mx, h * width);

            if (height[left] > height[right]) right--;
            else left++;
        }

        return mx;
    }
}
