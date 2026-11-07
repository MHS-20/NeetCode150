package main

func maxArea(height []int) int {
	left, right, mx := 0, len(height)-1, 0

	for left < right {
		width := right - left
		h := height[left]
		if height[right] < h {
			h = height[right]
		}
		if area := h * width; area > mx {
			mx = area
		}

		if height[left] > height[right] {
			right--
		} else {
			left++
		}
	}

	return mx
}
