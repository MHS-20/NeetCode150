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

	dp := make([][]int, n) // dp[i][sum+tot], -1 = not computed
	for i := range dp {
		dp[i] = make([]int, 2*tot+1)
		for s := range dp[i] {
			dp[i][s] = -1
		}
	}

	// f returns the ways to reach target using nums[i..], given the running sum so far
	var f func(i, sum int) int
	f = func(i, sum int) int {
		if i == n {
			if sum == target {
				return 1
			}
			return 0
		}
		if dp[i][sum+tot] != -1 {
			return dp[i][sum+tot]
		}

		add := f(i+1, sum+nums[i]) // +nums[i]
		sub := f(i+1, sum-nums[i]) // -nums[i]
		dp[i][sum+tot] = add + sub
		return dp[i][sum+tot]
	}

	return f(0, 0)
}
