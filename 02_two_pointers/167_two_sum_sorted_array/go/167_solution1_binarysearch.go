package solution

func twoSum(numbers []int, target int) []int {
	for idx := 0; idx < len(numbers); idx++ {
		diff := target - numbers[idx]
		i, j := idx+1, len(numbers)-1

		for i <= j {
			mid := i + (j-i)/2

			if numbers[mid] == diff {
				return []int{idx + 1, mid + 1}
			}

			if numbers[mid] > diff {
				j = mid - 1
			} else {
				i = mid + 1
			}
		}
	}

	return []int{}
}
