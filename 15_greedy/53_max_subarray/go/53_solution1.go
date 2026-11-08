package greedy

import "math"

func maxSubArray(nums []int) int {
	sum := 0
	mx := math.MinInt

	for _, n := range nums {
		sum += n
		mx = max(sum, mx)
		if sum < 0 {
			sum = 0 // a negative prefix only lowers what follows
		}
	}

	return mx
}
