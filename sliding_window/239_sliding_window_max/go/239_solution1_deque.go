package main

func maxSlidingWindow(nums []int, k int) []int {
	maxs := []int{}
	dq := []int{} // indices, values decreasing

	// i is the right pointer
	// i - k + 1 is the left pointer
	for i, n := range nums {
		if len(dq) > 0 && dq[0] < i-k+1 {
			dq = dq[1:]
		}

		for len(dq) > 0 && n > nums[dq[len(dq)-1]] {
			dq = dq[:len(dq)-1]
		}
		dq = append(dq, i)

		if i >= k-1 {
			maxs = append(maxs, nums[dq[0]])
		}
	}

	return maxs
}
