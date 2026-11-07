package main

import "sort"

func threeSum(nums []int) [][]int {
	sort.Ints(nums)
	result := [][]int{}

	for idx := 0; idx < len(nums); idx++ {
		if idx > 0 && nums[idx] == nums[idx-1] {
			continue
		}

		left, right := idx+1, len(nums)-1

		for left < right {
			total := nums[idx] + nums[left] + nums[right]

			if total == 0 {
				result = append(result, []int{nums[idx], nums[left], nums[right]})
				left++
				right--
				for left < right && nums[left] == nums[left-1] {
					left++
				}
				for left < right && nums[right] == nums[right+1] {
					right--
				}
			} else if total > 0 {
				right--
			} else {
				left++
			}
		}
	}

	return result
}
