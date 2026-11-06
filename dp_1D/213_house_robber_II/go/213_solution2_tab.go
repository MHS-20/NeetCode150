package dp

// robRange returns the max loot from houses start..end (inclusive), in a straight line
func robRange(nums []int, start, end int) int {
	length := end - start + 1
	if length == 1 {
		return nums[start]
	}

	dp := make([]int, length)
	dp[0] = nums[start]
	dp[1] = max(nums[start], nums[start+1])

	for i := 2; i < length; i++ {
		dp[i] = max(dp[i-1], // skip this house
			dp[i-2]+nums[start+i]) // rob this house
	}
	return dp[length-1]
}

func rob(nums []int) int {
	n := len(nums)
	if n == 1 {
		return nums[0]
	}

	return max(robRange(nums, 0, n-2), // exclude the last house
		robRange(nums, 1, n-1)) // exclude the first house
}
