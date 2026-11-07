package dp

func maxCoins(nums []int) int {
	a := append(append([]int{1}, nums...), 1) // pad: [1, nums..., 1]

	N := len(a)
	dp := make([][]int, N) // len < 2 → 0 already
	for i := range dp {
		dp[i] = make([]int, N)
	}

	for length := 2; length < N; length++ { // distance between walls
		for l := 0; l+length < N; l++ {
			r := l + length
			for k := l + 1; k < r; k++ {
				dp[l][r] = max(dp[l][r], dp[l][k]+dp[k][r]+a[l]*a[k]*a[r])
			}
		}
	}
	return dp[0][N-1]
}
