package dp

func longestPalindrome(s string) string {
	n := len(s)
	memo := make([][]int8, n) // 0 unknown, 1 no, 2 yes
	for i := range memo {
		memo[i] = make([]int8, n)
	}

	var isPal func(i, j int) bool
	isPal = func(i, j int) bool {
		if i >= j {
			return true // length 0 or 1
		}
		if memo[i][j] == 0 {
			memo[i][j] = 1
			if s[i] == s[j] && isPal(i+1, j-1) {
				memo[i][j] = 2
			}
		}
		return memo[i][j] == 2
	}

	bestStart, bestLen := 0, 0
	for i := 0; i < n; i++ {
		for j := i; j < n; j++ {
			if j-i+1 > bestLen && isPal(i, j) {
				bestStart, bestLen = i, j-i+1
			}
		}
	}
	return s[bestStart : bestStart+bestLen]
}
