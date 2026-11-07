package dp

func maxProfit(prices []int) int {
	n := len(prices)
	dp := make([][2]int, n+2) // dp[day][canBuy]

	for day := n - 1; day >= 0; day-- {
		// canBuy = 1
		dp[day][1] = max(-prices[day]+dp[day+1][0], // buy
			dp[day+1][1]) // skip
		// canBuy = 0 (holding)
		dp[day][0] = max(prices[day]+dp[day+2][1], // sell + cooldown
			dp[day+1][0]) // hold
	}
	return dp[0][1]
}
