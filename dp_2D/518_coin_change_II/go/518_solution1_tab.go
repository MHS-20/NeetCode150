package dp

func change(amount int, coins []int) int {
	n := len(coins)
	dp := make([][]uint64, n+1)
	for i := range dp {
		dp[i] = make([]uint64, amount+1)
		dp[i][0] = 1 // one way to make 0: use nothing
	}

	for i := 1; i <= n; i++ {
		for x := 1; x <= amount; x++ {
			dp[i][x] = dp[i-1][x] // skip coin i
			if coins[i-1] <= x {
				dp[i][x] += dp[i][x-coins[i-1]] // take coin i (same row)
			}
		}
	}
	return int(int32(dp[n][amount]))
}
