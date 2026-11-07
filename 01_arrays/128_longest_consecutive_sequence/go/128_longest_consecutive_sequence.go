package main

func longestConsecutive(nums []int) int {
	set := make(map[int]bool, len(nums))
	for _, n := range nums {
		set[n] = true
	}

	longest := 0

	for n := range set {
		if !set[n-1] {
			count := 1

			for set[n+count] {
				count++
			}

			if count > longest {
				longest = count
			}
		}
	}

	return longest
}
