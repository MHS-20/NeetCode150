package greedy

func canJump(nums []int) bool {
	mx := 0

	for i, n := range nums {
		if i > mx {
			return false
		}

		mx = max(mx, i+n)
		if mx >= len(nums)-1 {
			return true
		}
	}

	return false
}
