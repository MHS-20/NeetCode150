package dp

func wordBreak(s string, wordDict []string) bool {
	n := len(s)
	words := make(map[string]bool, len(wordDict))
	maxLen := 0
	for _, w := range wordDict {
		words[w] = true
		maxLen = max(maxLen, len(w))
	}

	dp := make([]bool, n+1)
	dp[0] = true

	for i := 1; i <= n; i++ {
		// A piece longer than maxLen can't be a word, so start j no earlier than
		// i - maxLen
		for j := max(0, i-maxLen); j < i; j++ {
			if dp[j] && words[s[j:i]] {
				dp[i] = true
				break
			}
		}
	}
	return dp[n]
}
