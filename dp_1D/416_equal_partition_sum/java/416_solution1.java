import java.util.Arrays;

class Solution {
    public boolean canPartition(int[] nums) {
        int total = Arrays.stream(nums).sum();
        if (total % 2 != 0)
            return false;
        int target = total / 2;

        boolean[] dp = new boolean[target + 1];
        dp[0] = true;

        for (int x : nums) {
            // Go backward so each number is used at most once
            for (int s = target; s >= x; s--) {
                if (dp[s - x])
                    dp[s] = true;
            }
        }
        return dp[target];
    }
}
