package dp

func longestCommonSubsequence(text1 string, text2 string) int {
	n, m := len(text1), len(text2)
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var solve func(i, j int) int
	solve = func(i, j int) int {
		if i == 0 || j == 0 {
			return 0 // one string is empty
		}
		if dp[i][j] != -1 {
			return dp[i][j]
		}

		if text1[i-1] == text2[j-1] {
			dp[i][j] = 1 + solve(i-1, j-1)
		} else {
			dp[i][j] = max(solve(i-1, j), solve(i, j-1))
		}
		return dp[i][j]
	}

	return solve(n, m)
}
