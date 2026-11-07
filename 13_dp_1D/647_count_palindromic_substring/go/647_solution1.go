package dp

func countSubstrings(s string) int {
	n := len(s)
	count := 0
	dp := make([][]bool, n)
	for i := range dp {
		dp[i] = make([]bool, n)
	}

	for i := 0; i < n; i++ {
		dp[i][i] = true
		count++
	}

	for length := 2; length <= n; length++ {
		for i := 0; i+length-1 < n; i++ {
			j := i + length - 1

			if s[i] == s[j] && (length == 2 || dp[i+1][j-1]) {
				dp[i][j] = true
				count++
			}
		}
	}

	return count
}
