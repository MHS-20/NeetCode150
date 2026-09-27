struct Solution;

impl Solution {
    fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        let (rows, cols) = (matrix.len(), matrix[0].len());
        let (mut left, mut right) = (0i32, (rows * cols) as i32 - 1);

        while left <= right {
            let mid = left + (right - left) / 2;
            let (i, j) = ((mid as usize) / cols, (mid as usize) % cols);

            if matrix[i][j] == target {
                return true;
            }
            if matrix[i][j] > target {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        false
    }
}
