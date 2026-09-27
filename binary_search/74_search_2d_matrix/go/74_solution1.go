package main

func searchMatrix(matrix [][]int, target int) bool {
	rows, cols := len(matrix), len(matrix[0])
	left, right := 0, rows*cols-1

	for left <= right {
		mid := left + (right-left)/2
		i, j := mid/cols, mid%cols

		if matrix[i][j] == target {
			return true
		}
		if matrix[i][j] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}
	return false
}
