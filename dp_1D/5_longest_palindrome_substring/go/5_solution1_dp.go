package dp

func longestPalindrome(s string) string {
	n := len(s)
	dp := make([][]bool, n)
	for i := range dp {
		dp[i] = make([]bool, n)
	}
	bestStart, bestLen := 0, 1

	// Every single character is a palindrome
	for i := 0; i < n; i++ {
		dp[i][i] = true
	}

	// Fill by increasing substring length
	for length := 2; length <= n; length++ {
		for i := 0; i+length-1 < n; i++ {
			j := i + length - 1

			if s[i] == s[j] && (length == 2 || dp[i+1][j-1]) {
				dp[i][j] = true
				if length > bestLen {
					bestStart, bestLen = i, length
				}
			}
		}
	}
	return s[bestStart : bestStart+bestLen]
}
