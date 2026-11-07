package dp

func longestIncreasingPath(matrix [][]int) int {
	m, n := len(matrix), len(matrix[0])
	dirs := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}
	dp := make([][]int, m) // 0 = not computed
	for i := range dp {
		dp[i] = make([]int, n)
	}

	var dfs func(i, j int) int
	dfs = func(i, j int) int {
		if dp[i][j] != 0 {
			return dp[i][j] // already computed
		}

		best := 1 // the cell alone
		for _, d := range dirs {
			ni, nj := i+d[0], j+d[1]
			if ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] > matrix[i][j] {
				best = max(best, 1+dfs(ni, nj))
			}
		}
		dp[i][j] = best
		return best
	}

	res := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			res = max(res, dfs(i, j))
		}
	}
	return res
}
