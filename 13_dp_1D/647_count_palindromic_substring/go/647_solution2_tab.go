package dp

func countSubstrings(s string) int {
	n, count := len(s), 0
	memo := make([][]bool, n)
	for i := range memo {
		memo[i] = make([]bool, n)
	}

	for i := n - 1; i >= 0; i-- {
		for j := i; j < n; j++ {
			if s[i] == s[j] && (j-i < 2 || memo[i+1][j-1]) {
				memo[i][j] = true
				count++
			}
		}
	}

	return count
}
