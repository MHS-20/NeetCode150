class Solution {
    public int maxSubArray(int[] nums) {
        int sum = 0;
        int mx = Integer.MIN_VALUE;

        for (int n : nums) {
            sum += n;
            mx = Math.max(sum, mx);
            if (sum < 0)
                sum = 0; // a negative prefix only lowers what follows
        }

        return mx;
    }
}
