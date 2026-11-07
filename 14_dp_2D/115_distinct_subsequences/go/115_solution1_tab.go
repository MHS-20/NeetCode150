package dp

func numDistinct(s string, t string) int {
	n, m := len(s), len(t)
	dp := make([][]uint64, n+1) // uint64 so intermediate overflow wraps
	for i := range dp {
		dp[i] = make([]uint64, m+1)
		dp[i][0] = 1 // empty t: one way
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			dp[i][j] = dp[i-1][j] // skip cur s[i-1]
			if s[i-1] == t[j-1] {
				dp[i][j] += dp[i-1][j-1] // pick it
			}
		}
	}
	return int(int32(dp[n][m]))
}
