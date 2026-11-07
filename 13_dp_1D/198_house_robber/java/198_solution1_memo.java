import java.util.Arrays;

class Solution {
    private int[] memo;

    private int maxLoot(int idx, int[] nums) {
        if (idx == 0)
            return nums[0];
        if (idx == 1)
            return Math.max(nums[0], nums[1]);

        if (memo[idx] != -1)
            return memo[idx];

        return memo[idx] = Math.max(maxLoot(idx - 1, nums), // skip this house
                maxLoot(idx - 2, nums) + nums[idx]); // rob this house
    }

    public int rob(int[] nums) {
        memo = new int[nums.length];
        Arrays.fill(memo, -1);
        return maxLoot(nums.length - 1, nums);
    }
}
