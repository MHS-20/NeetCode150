package dp

func minCostClimbingStairs(cost []int) int {
	n := len(cost)
	dp := make([]int, n+1) // dp[0] = dp[1] = 0: start on step 0 or 1 for free

	for i := 2; i <= n; i++ {
		dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2])
	}
	return dp[n] // n = the top, one past the last step
}
