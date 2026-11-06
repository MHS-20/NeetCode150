package dp

func rob(nums []int) int {
	memo := make([]int, len(nums))
	for i := range memo {
		memo[i] = -1
	}

	var maxLoot func(idx int) int
	maxLoot = func(idx int) int {
		if idx == 0 {
			return nums[0]
		}
		if idx == 1 {
			return max(nums[0], nums[1])
		}

		if memo[idx] != -1 {
			return memo[idx]
		}

		memo[idx] = max(maxLoot(idx-1), // skip this house
			maxLoot(idx-2)+nums[idx]) // rob this house
		return memo[idx]
	}

	return maxLoot(len(nums) - 1)
}
