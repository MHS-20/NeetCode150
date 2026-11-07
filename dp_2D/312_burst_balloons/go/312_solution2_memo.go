package dp

func maxCoins(nums []int) int {
	a := append(append([]int{1}, nums...), 1) // pad: [1, nums..., 1]

	N := len(a)
	dp := make([][]int, N) // -1 = not computed
	for i := range dp {
		dp[i] = make([]int, N)
		for j := range dp[i] {
			dp[i][j] = -1
		}
	}

	var f func(l, r int) int
	f = func(l, r int) int {
		if r-l < 2 {
			return 0 // nothing strictly between l and r
		}
		if dp[l][r] != -1 {
			return dp[l][r]
		}

		best := 0
		for k := l + 1; k < r; k++ { // k = last balloon burst in (l, r)
			coins := a[l]*a[k]*a[r] + f(l, k) + f(k, r)
			best = max(best, coins)
		}
		dp[l][r] = best
		return best
	}

	return f(0, N-1)
}
