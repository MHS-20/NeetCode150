package solution

func containsDuplicate(nums []int) bool {
	tracker := make(map[int]struct{})

	for _, x := range nums {
		if _, ok := tracker[x]; ok {
			return true
		}
		tracker[x] = struct{}{}
	}

	return false
}
