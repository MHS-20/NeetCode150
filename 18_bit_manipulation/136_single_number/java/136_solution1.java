class Solution {
    public int singleNumber(int[] nums) {
        int xr = 0;
        for (int n : nums)
            xr = xr ^ n;
        return xr;
    }
}
