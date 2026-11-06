package dp

func maxProduct(nums []int) int {
	curMax, curMin, best := nums[0], nums[0], nums[0]

	for _, x := range nums[1:] {
		a, b := curMax*x, curMin*x

		curMax = max(x, a, b)
		curMin = min(x, a, b)
		best = max(best, curMax)
	}
	return best
}
