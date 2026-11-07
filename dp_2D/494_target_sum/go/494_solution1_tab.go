package dp

func findTargetSumWays(nums []int, target int) int {
	n := len(nums)
	tot := 0
	for _, x := range nums {
		tot += x
	}
	if target > tot || target < -tot {
		return 0
	}

	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, 2*tot+1)
	}
	dp[0][0+tot] = 1 // 0 numbers used, sum 0

	for i := 1; i <= n; i++ {
		x := nums[i-1]
		for s := -tot; s <= tot; s++ {
			ways := 0
			if s-x >= -tot {
				ways += dp[i-1][s-x+tot] // added x
			}
			if s+x <= tot {
				ways += dp[i-1][s+x+tot] // subtracted x
			}
			dp[i][s+tot] = ways
		}
	}
	return dp[n][target+tot]
}
