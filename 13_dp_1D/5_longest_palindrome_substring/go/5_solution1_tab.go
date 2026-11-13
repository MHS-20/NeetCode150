package dp

func longestPalindrome(s string) string {
	n := len(s)
	memo := make([][]bool, n)
	for i := range memo {
		memo[i] = make([]bool, n)
	}
	bestStart, bestLen := 0, 0

	for i := n - 1; i >= 0; i-- {
		for j := i; j < n; j++ {
			if s[i] == s[j] && (j-i < 2 || memo[i+1][j-1]) {
				memo[i][j] = true
				if j-i+1 > bestLen {
					bestStart, bestLen = i, j-i+1
				}
			}
		}
	}

	return s[bestStart : bestStart+bestLen]
}
