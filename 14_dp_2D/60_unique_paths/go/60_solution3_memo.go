package dp

func uniquePaths(m int, n int) int {
	dp := make([][]int, m)
	for i := range dp {
		dp[i] = make([]int, n)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var solve func(i, j int) int
	solve = func(i, j int) int {
		if i == 0 && j == 0 {
			return 1 // reached the start
		}
		if i < 0 || j < 0 {
			return 0 // fell off the grid
		}
		if dp[i][j] != -1 {
			return dp[i][j] // already computed
		}

		up := solve(i-1, j)
		left := solve(i, j-1)
		dp[i][j] = up + left
		return dp[i][j]
	}

	return solve(m-1, n-1)
}
