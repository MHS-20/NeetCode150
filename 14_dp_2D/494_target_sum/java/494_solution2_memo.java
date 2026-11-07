import java.util.Arrays;

class Solution {
    private int tot, target;
    private int[][] dp; // dp[i][sum + tot], -1 = not computed

    // Ways to reach target using nums[i..], given the running sum so far
    private int f(int i, int sum, int[] nums) {
        if (i == nums.length)
            return sum == target ? 1 : 0;
        if (dp[i][sum + tot] != -1)
            return dp[i][sum + tot];

        int add = f(i + 1, sum + nums[i], nums); // +nums[i]
        int sub = f(i + 1, sum - nums[i], nums); // -nums[i]
        return dp[i][sum + tot] = add + sub;
    }

    public int findTargetSumWays(int[] nums, int target) {
        int n = nums.length;
        tot = Arrays.stream(nums).sum();
        if (Math.abs(target) > tot)
            return 0;

        this.target = target;
        dp = new int[n][2 * tot + 1];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return f(0, 0, nums);
    }
}
