import java.util.Arrays;

class Solution {
    private int[] memo;

    private int maxLoot(int idx, int start, int[] nums) {
        if (idx < start)
            return 0;
        if (memo[idx] != -1)
            return memo[idx];
        return memo[idx] = Math.max(maxLoot(idx - 1, start, nums),
                maxLoot(idx - 2, start, nums) + nums[idx]);
    }

    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 1)
            return nums[0];

        memo = new int[n];
        Arrays.fill(memo, -1);
        int skipLast = maxLoot(n - 2, 0, nums);

        Arrays.fill(memo, -1); // reset: different subproblem
        int skipFirst = maxLoot(n - 1, 1, nums);

        return Math.max(skipLast, skipFirst);
    }
}
