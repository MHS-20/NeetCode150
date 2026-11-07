package main

func checkAndMarkBit(masks *[9]int, idx int, bit byte) bool {
	if masks[idx]&(1<<bit) != 0 {
		return false
	}
	masks[idx] |= 1 << bit
	return true
}

func isValidSudoku(board [][]byte) bool {
	var seenRows [9]int
	var seenCols [9]int
	var seenBoxes [9]int

	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			if board[i][j] == '.' {
				continue
			}

			current := board[i][j] - '0' - 1
			box := (i/3)*3 + (j / 3)

			if !checkAndMarkBit(&seenRows, i, current) {
				return false
			}
			if !checkAndMarkBit(&seenCols, j, current) {
				return false
			}
			if !checkAndMarkBit(&seenBoxes, box, current) {
				return false
			}
		}
	}

	return true
}
