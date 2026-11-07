package dp

func coinChange(coins []int, amount int) int {
	INF := amount + 1
	dp := make([]int, amount+1)
	for x := 1; x <= amount; x++ {
		dp[x] = INF
	}

	for x := 1; x <= amount; x++ {
		for _, c := range coins {
			if c <= x && dp[x-c] != INF {
				dp[x] = min(dp[x], dp[x-c]+1)
			}
		}
	}
	if dp[amount] == INF {
		return -1
	}
	return dp[amount]
}
