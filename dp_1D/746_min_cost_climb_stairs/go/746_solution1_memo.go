package dp

func minCostClimbingStairs(cost []int) int {
	memo := make([]int, len(cost)+1)
	for i := range memo {
		memo[i] = -1
	}

	var costs func(i int) int
	costs = func(i int) int {
		if i <= 1 {
			return 0 // start on step 0 or 1 for free
		}
		if memo[i] != -1 {
			return memo[i]
		}
		memo[i] = min(costs(i-1)+cost[i-1], costs(i-2)+cost[i-2])
		return memo[i]
	}

	return costs(len(cost))
}
