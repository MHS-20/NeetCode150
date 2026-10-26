const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn solve(board: &mut Vec<Vec<char>>) {
        let (rows, cols) = (board.len(), board[0].len());

        // 1. mark border-connected 'O's as safe
        for i in 0..rows {
            Self::dfs(board, i, 0, rows, cols);
            Self::dfs(board, i, cols - 1, rows, cols);
        }
        for j in 0..cols {
            Self::dfs(board, 0, j, rows, cols);
            Self::dfs(board, rows - 1, j, rows, cols);
        }

        // 2. capture leftover 'O's, restore safe ones
        for cell in board.iter_mut().flatten() {
            if *cell == 'O' {
                *cell = 'X';
            } else if *cell == '.' {
                *cell = 'O';
            }
        }
    }

    fn dfs(board: &mut Vec<Vec<char>>, r: usize, c: usize, rows: usize, cols: usize) {
        if board[r][c] != 'O' {
            return;
        }
        board[r][c] = '.';
        for (dr, dc) in DIRS {
            // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
            let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
            if nr < rows && nc < cols {
                Self::dfs(board, nr, nc, rows, cols);
            }
        }
    }
}
