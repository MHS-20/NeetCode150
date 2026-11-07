package dp

func change(amount int, coins []int) int {
	dp := make([][]int, len(coins))
	for i := range dp {
		dp[i] = make([]int, amount+1)
		for x := range dp[i] {
			dp[i][x] = -1
		}
	}

	var f func(i, x int) int
	f = func(i, x int) int {
		if x == 0 {
			return 1 // made the amount
		}
		if i == len(coins) {
			return 0 // out of coins
		}
		if dp[i][x] != -1 {
			return dp[i][x]
		}

		skip := f(i+1, x) // never use coin i again
		take := 0
		if coins[i] <= x {
			take = f(i, x-coins[i]) // use coin i, stay at i (reuse allowed)
		}

		dp[i][x] = skip + take
		return dp[i][x]
	}

	return f(0, amount)
}
