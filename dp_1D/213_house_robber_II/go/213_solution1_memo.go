package dp

func rob(nums []int) int {
	n := len(nums)
	if n == 1 {
		return nums[0]
	}

	memo := make([]int, n)
	reset := func() {
		for i := range memo {
			memo[i] = -1
		}
	}

	var maxLoot func(idx, start int) int
	maxLoot = func(idx, start int) int {
		if idx < start {
			return 0
		}
		if memo[idx] != -1 {
			return memo[idx]
		}
		memo[idx] = max(maxLoot(idx-1, start), maxLoot(idx-2, start)+nums[idx])
		return memo[idx]
	}

	reset()
	skipLast := maxLoot(n-2, 0)

	reset() // reset: different subproblem
	skipFirst := maxLoot(n-1, 1)

	return max(skipLast, skipFirst)
}
