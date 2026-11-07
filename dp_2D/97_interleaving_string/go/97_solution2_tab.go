package dp

func isInterleave(s1 string, s2 string, s3 string) bool {
	n, m := len(s1), len(s2)
	if n+m != len(s3) {
		return false
	}

	dp := make([][]bool, n+1)
	for i := range dp {
		dp[i] = make([]bool, m+1)
	}
	dp[0][0] = true // empty + empty = empty

	for i := 0; i <= n; i++ {
		for j := 0; j <= m; j++ {
			if i == 0 && j == 0 {
				continue
			}
			k := i + j - 1 // last char of s3 prefix
			fromS1 := i > 0 && dp[i-1][j] && s1[i-1] == s3[k]
			fromS2 := j > 0 && dp[i][j-1] && s2[j-1] == s3[k]
			dp[i][j] = fromS1 || fromS2
		}
	}
	return dp[n][m]
}
