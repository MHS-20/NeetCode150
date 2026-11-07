package dp

func numDistinct(s string, t string) int {
	n, m := len(s), len(t)
	dp := make([][]int, n+1) // -1 = not computed
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var f func(i, j int) int
	f = func(i, j int) int {
		if j == 0 {
			return 1 // t fully matched
		}
		if i == 0 {
			return 0 // s ran out first
		}
		if dp[i][j] != -1 {
			return dp[i][j]
		}

		ways := f(i-1, j) // skip s[i-1]
		if s[i-1] == t[j-1] {
			ways += f(i-1, j-1) // pick it
		}

		dp[i][j] = ways & 0xFFFFFFFF // keep within u32 range so nothing overflows
		return dp[i][j]
	}

	return int(int32(f(n, m)))
}
