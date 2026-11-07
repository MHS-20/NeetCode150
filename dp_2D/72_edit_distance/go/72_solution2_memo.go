package dp

func minDistance(word1 string, word2 string) int {
	n, m := len(word1), len(word2)
	dp := make([][]int, n+1) // -1 = not computed
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var f func(i, j int) int
	f = func(i, j int) int {
		if i == 0 {
			return j // insert the remaining j chars
		}
		if j == 0 {
			return i // delete the remaining i chars
		}
		if dp[i][j] != -1 {
			return dp[i][j]
		}

		if word1[i-1] == word2[j-1] {
			dp[i][j] = f(i-1, j-1) // free match
			return dp[i][j]
		}

		del := f(i-1, j)
		ins := f(i, j-1)
		rep := f(i-1, j-1)
		dp[i][j] = 1 + min(del, ins, rep)
		return dp[i][j]
	}

	return f(n, m)
}
