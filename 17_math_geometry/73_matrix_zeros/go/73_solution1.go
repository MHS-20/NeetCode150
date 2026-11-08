package mathgeometry

func setZeroes(matrix [][]int) {
	m, n := len(matrix), len(matrix[0])
	zeroRow, zeroCol := make([]bool, m), make([]bool, n)

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if matrix[i][j] == 0 {
				zeroRow[i], zeroCol[j] = true, true
			}
		}
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if zeroRow[i] || zeroCol[j] {
				matrix[i][j] = 0
			}
		}
	}
}
