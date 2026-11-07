package dp

func climbStairs(n int) int {
	memo := make([]int, n+1)

	var ways func(i int) int
	ways = func(i int) int {
		if i <= 2 {
			return i // ways(1) = 1, ways(2) = 2
		}
		if memo[i] != 0 {
			return memo[i]
		}
		memo[i] = ways(i-1) + ways(i-2)
		return memo[i]
	}

	return ways(n)
}
