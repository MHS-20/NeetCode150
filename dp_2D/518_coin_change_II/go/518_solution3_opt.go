package dp

func change(amount int, coins []int) int {
	dp := make([]uint64, amount+1)
	dp[0] = 1
	for _, c := range coins {
		for x := c; x <= amount; x++ {
			dp[x] += dp[x-c]
		}
	}
	return int(int32(dp[amount]))
}
