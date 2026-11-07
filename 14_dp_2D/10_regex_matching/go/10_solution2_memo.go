package dp

func isMatch(s string, p string) bool {
	n, m := len(s), len(p)
	dp := make([][]int, n+1) // -1 = not computed, 0 = false, 1 = true
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	matches := func(i, j int) bool { // s[i-1] vs p[j-1]
		return p[j-1] == '.' || s[i-1] == p[j-1]
	}

	var f func(i, j int) bool
	f = func(i, j int) bool {
		if j == 0 {
			return i == 0 // empty pattern matches only empty s
		}
		if dp[i][j] != -1 {
			return dp[i][j] == 1
		}

		var res bool
		if p[j-1] == '*' {
			res = f(i, j-2) // zero copies
			if !res && i > 0 && matches(i, j-1) {
				res = f(i-1, j) // one more copy
			}
		} else {
			res = i > 0 && matches(i, j) && f(i-1, j-1)
		}

		dp[i][j] = 0
		if res {
			dp[i][j] = 1
		}
		return res
	}

	return f(n, m)
}
