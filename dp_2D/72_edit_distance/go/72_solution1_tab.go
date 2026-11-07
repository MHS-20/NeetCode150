package dp

func minDistance(word1 string, word2 string) int {
	n, m := len(word1), len(word2)
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
	}

	for i := 0; i <= n; i++ {
		dp[i][0] = i // delete all
	}
	for j := 0; j <= m; j++ {
		dp[0][j] = j // insert all
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if word1[i-1] == word2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				dp[i][j] = 1 + min(dp[i-1][j], // delete
					dp[i][j-1],   // insert
					dp[i-1][j-1]) // replace
			}
		}
	}
	return dp[n][m]
}
