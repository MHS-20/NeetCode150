impl Solution {
    pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
        let mut seen = [false; 9];

        for i in 0..9 {
            for j in 0..9 {
                if board[i][j] == '.' {
                    continue;
                }
                let current = (board[i][j] as u8 - b'0' - 1) as usize;
                if seen[current] {
                    return false;
                }
                seen[current] = true;
            }
            seen = [false; 9];
        }

        for j in 0..9 {
            for i in 0..9 {
                if board[i][j] == '.' {
                    continue;
                }
                let current = (board[i][j] as u8 - b'0' - 1) as usize;
                if seen[current] {
                    return false;
                }
                seen[current] = true;
            }
            seen = [false; 9];
        }

        for row_offset in (0..9).step_by(3) {
            for col_offset in (0..9).step_by(3) {
                for i in 0..3 {
                    for j in 0..3 {
                        let val = board[i + row_offset][j + col_offset];
                        if val == '.' {
                            continue;
                        }
                        let current = (val as u8 - b'0' - 1) as usize;
                        if seen[current] {
                            return false;
                        }
                        seen[current] = true;
                    }
                }
                seen = [false; 9];
            }
        }

        true
    }
}
