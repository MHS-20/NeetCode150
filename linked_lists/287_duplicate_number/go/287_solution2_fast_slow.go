package linkedlists

func findDuplicate(nums []int) int {
	slow, fast := 0, 0

	// Phase 1: find a meeting point inside the cycle
	for {
		slow = nums[slow]
		fast = nums[nums[fast]]
		if slow == fast {
			break
		}
	}

	// Phase 2: find the cycle entrance (the duplicate)
	slow = 0
	for slow != fast {
		slow = nums[slow]
		fast = nums[fast]
	}

	return slow
}
