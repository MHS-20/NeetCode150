package dp

func isMatch(s string, p string) bool {
	n, m := len(s), len(p)
	dp := make([][]bool, n+1)
	for i := range dp {
		dp[i] = make([]bool, m+1)
	}
	dp[0][0] = true

	matches := func(i, j int) bool { // s[i-1] vs p[j-1]
		return p[j-1] == '.' || s[i-1] == p[j-1]
	}

	for i := 0; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if p[j-1] == '*' {
				dp[i][j] = dp[i][j-2] // zero copies
				if i > 0 && matches(i, j-1) {
					dp[i][j] = dp[i][j] || dp[i-1][j] // one more copy
				}
			} else {
				dp[i][j] = i > 0 && matches(i, j) && dp[i-1][j-1]
			}
		}
	}
	return dp[n][m]
}
