package solution

func trap(height []int) int {
	stack := []int{}
	total := 0

	for i, h := range height {
		for len(stack) > 0 && h > height[stack[len(stack)-1]] {
			bottom := stack[len(stack)-1]
			stack = stack[:len(stack)-1]

			if len(stack) == 0 {
				break
			}

			left := stack[len(stack)-1]
			width := i - left - 1
			limit := height[left]
			if h < limit {
				limit = h
			}
			total += width * (limit - height[bottom])
		}

		stack = append(stack, i)
	}

	return total
}
