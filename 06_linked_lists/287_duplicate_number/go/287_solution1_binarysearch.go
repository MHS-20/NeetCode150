package linkedlists

func findDuplicateBinarySearch(nums []int) int {
	left, right := 1, len(nums)-1 // right = n

	for left < right {
		mid := left + (right-left)/2

		// count how many numbers are <= mid
		count := 0
		for _, x := range nums {
			if x <= mid {
				count++
			}
		}

		if count > mid {
			right = mid // duplicate is in [left, mid]
		} else {
			left = mid + 1 // duplicate is in [mid + 1, right]
		}
	}

	return left
}
