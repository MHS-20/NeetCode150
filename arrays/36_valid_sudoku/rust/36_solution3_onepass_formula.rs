impl Solution {
    pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
        let mut seen_rows = [[false; 9]; 9];
        let mut seen_cols = [[false; 9]; 9];
        let mut seen_boxes = [[false; 9]; 9];

        fn check_and_mark(arr: &mut [bool; 9], idx: usize) -> bool {
            if arr[idx] {
                return false;
            }
            arr[idx] = true;
            true
        }

        for i in 0..9 {
            for j in 0..9 {
                if board[i][j] == '.' {
                    continue;
                }

                let current = (board[i][j] as u8 - b'0' - 1) as usize;
                let bx = (i / 3) * 3 + (j / 3);

                if !check_and_mark(&mut seen_rows[i], current) {
                    return false;
                }
                if !check_and_mark(&mut seen_cols[j], current) {
                    return false;
                }
                if !check_and_mark(&mut seen_boxes[bx], current) {
                    return false;
                }
            }
        }

        true
    }
}
