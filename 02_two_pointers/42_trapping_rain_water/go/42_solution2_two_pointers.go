package solution

func trap(height []int) int {
	if len(height) == 0 {
		return 0
	}

	left, right := 0, len(height)-1
	leftMax, rightMax := height[left], height[right]
	total := 0

	for left < right {
		if leftMax < rightMax {
			left++
			if height[left] > leftMax {
				leftMax = height[left]
			}
			total += leftMax - height[left]
		} else {
			right--
			if height[right] > rightMax {
				rightMax = height[right]
			}
			total += rightMax - height[right]
		}
	}

	return total
}
