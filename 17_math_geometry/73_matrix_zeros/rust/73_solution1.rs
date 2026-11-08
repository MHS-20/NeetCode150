impl Solution {
    pub fn set_zeroes(matrix: &mut Vec<Vec<i32>>) {
        let (m, n) = (matrix.len(), matrix[0].len());
        let (mut zero_row, mut zero_col) = (vec![false; m], vec![false; n]);

        for i in 0..m {
            for j in 0..n {
                if matrix[i][j] == 0 {
                    zero_row[i] = true;
                    zero_col[j] = true;
                }
            }
        }

        for i in 0..m {
            for j in 0..n {
                if zero_row[i] || zero_col[j] {
                    matrix[i][j] = 0;
                }
            }
        }
    }
}
