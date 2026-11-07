import java.util.Arrays;

class Solution {
    private int[] memo;

    private int costs(int i, int[] cost) {
        if (i <= 1)
            return 0; // start on step 0 or 1 for free
        if (memo[i] != -1)
            return memo[i];
        return memo[i] = Math.min(costs(i - 1, cost) + cost[i - 1],
                costs(i - 2, cost) + cost[i - 2]);
    }

    public int minCostClimbingStairs(int[] cost) {
        memo = new int[cost.length + 1];
        Arrays.fill(memo, -1);
        return costs(cost.length, cost);
    }
}
