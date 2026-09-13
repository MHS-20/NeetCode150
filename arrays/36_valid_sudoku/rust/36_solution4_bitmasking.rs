impl Solution {
    pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
        let mut seen_rows = [0i32; 9];
        let mut seen_cols = [0i32; 9];
        let mut seen_boxes = [0i32; 9];

        fn check_and_mark(masks: &mut [i32; 9], idx: usize, bit: u8) -> bool {
            if masks[idx] & (1 << bit) != 0 {
                return false;
            }
            masks[idx] |= 1 << bit;
            true
        }

        for i in 0..9 {
            for j in 0..9 {
                if board[i][j] == '.' {
                    continue;
                }

                let current = board[i][j] as u8 - b'0' - 1;
                let bx = (i / 3) * 3 + (j / 3);

                if !check_and_mark(&mut seen_rows, i, current) {
                    return false;
                }
                if !check_and_mark(&mut seen_cols, j, current) {
                    return false;
                }
                if !check_and_mark(&mut seen_boxes, bx, current) {
                    return false;
                }
            }
        }

        true
    }
}
