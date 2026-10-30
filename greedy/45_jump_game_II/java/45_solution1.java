class Solution {
    public int jump(int[] nums) {
        int end = 0, far = 0, count = 0;

        for (int i = 0; i < nums.length - 1; i++) {
            far = Math.max(far, i + nums[i]);
            if (i == end) {
                // I've used up everything reachable with k jumps,
                // so now I'm entering the area that needs k+1 jumps.
                count++;
                end = far;
            }
        }

        return count;
    }
}
