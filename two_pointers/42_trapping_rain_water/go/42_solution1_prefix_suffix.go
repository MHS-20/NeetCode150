package solution

func trap(height []int) int {
	n := len(height)
	if n == 0 {
		return 0
	}

	leftMax := make([]int, n)
	rightMax := make([]int, n)

	leftMax[0] = height[0]
	for i := 1; i < n; i++ {
		leftMax[i] = leftMax[i-1]
		if height[i] > leftMax[i] {
			leftMax[i] = height[i]
		}
	}

	rightMax[n-1] = height[n-1]
	for i := n - 2; i >= 0; i-- {
		rightMax[i] = rightMax[i+1]
		if height[i] > rightMax[i] {
			rightMax[i] = height[i]
		}
	}

	total := 0
	for i := 0; i < n; i++ {
		level := leftMax[i]
		if rightMax[i] < level {
			level = rightMax[i]
		}
		total += level - height[i]
	}

	return total
}
