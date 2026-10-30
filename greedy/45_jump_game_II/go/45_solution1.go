package greedy

func jump(nums []int) int {
	end, far, count := 0, 0, 0

	for i := 0; i < len(nums)-1; i++ {
		far = max(far, i+nums[i])
		if i == end {
			// I've used up everything reachable with k jumps,
			// so now I'm entering the area that needs k+1 jumps.
			count++
			end = far
		}
	}

	return count
}
