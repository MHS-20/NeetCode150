import java.util.Arrays;

class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        int n = nums.length;
        int tot = Arrays.stream(nums).sum();
        if (Math.abs(target) > tot)
            return 0;

        int[][] dp = new int[n + 1][2 * tot + 1];
        dp[0][0 + tot] = 1; // 0 numbers used, sum 0

        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            for (int s = -tot; s <= tot; s++) {
                int ways = 0;
                if (s - x >= -tot)
                    ways += dp[i - 1][s - x + tot]; // added x
                if (s + x <= tot)
                    ways += dp[i - 1][s + x + tot]; // subtracted x
                dp[i][s + tot] = ways;
            }
        }
        return dp[n][target + tot];
    }
}
