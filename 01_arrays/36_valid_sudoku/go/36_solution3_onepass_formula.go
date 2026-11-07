package main

func checkAndMark(arr *[9]bool, idx byte) bool {
	if arr[idx] {
		return false
	}
	arr[idx] = true
	return true
}

func isValidSudoku(board [][]byte) bool {
	var seenRows [9][9]bool
	var seenCols [9][9]bool
	var seenBoxes [9][9]bool

	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			if board[i][j] == '.' {
				continue
			}

			current := board[i][j] - '0' - 1
			box := (i/3)*3 + (j / 3)

			if !checkAndMark(&seenRows[i], current) {
				return false
			}
			if !checkAndMark(&seenCols[j], current) {
				return false
			}
			if !checkAndMark(&seenBoxes[box], current) {
				return false
			}
		}
	}

	return true
}
