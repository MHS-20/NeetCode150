package dp

func uniquePaths(m int, n int) int {
	dp := make([][]int, m)
	for i := range dp {
		dp[i] = make([]int, n)
	}
	dp[m-1][n-1] = 1

	for i := m - 1; i >= 0; i-- {
		for j := n - 1; j >= 0; j-- {
			if i == m-1 && j == n-1 {
				continue
			}
			down, right := 0, 0
			if i+1 < m {
				down = dp[i+1][j]
			}
			if j+1 < n {
				right = dp[i][j+1]
			}
			dp[i][j] = down + right
		}
	}
	return dp[0][0]
}
