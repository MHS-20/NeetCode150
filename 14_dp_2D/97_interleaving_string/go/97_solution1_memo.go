package dp

func isInterleave(s1 string, s2 string, s3 string) bool {
	n, m := len(s1), len(s2)
	if n+m != len(s3) {
		return false
	}

	dp := make([][]int, n+1) // -1 = not computed, 0 = false, 1 = true
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var f func(i, j int) bool
	f = func(i, j int) bool {
		if i == n && j == m {
			return true // used everything
		}
		if dp[i][j] != -1 {
			return dp[i][j] == 1
		}

		k := i + j // position in s3
		res := false
		if i < n && s1[i] == s3[k] {
			res = f(i+1, j) // take from s1
		}
		if !res && j < m && s2[j] == s3[k] {
			res = f(i, j+1) // take from s2
		}

		dp[i][j] = 0
		if res {
			dp[i][j] = 1
		}
		return res
	}

	return f(0, 0)
}
