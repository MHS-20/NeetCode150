impl Solution {
    pub fn rotate(matrix: &mut Vec<Vec<i32>>) {
        let n = matrix.len();
        for i in 0..n {
            for j in i + 1..n {
                let tmp = matrix[j][i];
                matrix[j][i] = matrix[i][j];
                matrix[i][j] = tmp;
            }
        }

        for row in matrix.iter_mut() {
            for j in 0..n / 2 {
                row.swap(j, n - j - 1);
            }
        }
    }
}
