const DIRS: [(i32, i32); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn exist(mut board: Vec<Vec<char>>, word: String) -> bool {
        let word: Vec<char> = word.chars().collect();
        for r in 0..board.len() {
            for c in 0..board[0].len() {
                if Self::dfs(&mut board, &word, 0, r, c) {
                    return true;
                }
            }
        }
        false
    }

    fn dfs(board: &mut Vec<Vec<char>>, word: &[char], idx: usize, row: usize, col: usize) -> bool {
        let ch = word[idx];
        if ch != board[row][col] {
            return false;
        }

        if idx == word.len() - 1 {
            return true;
        }

        board[row][col] = '#';
        for (dr, dc) in DIRS {
            let (nr, nc) = (row as i32 + dr, col as i32 + dc);

            if nr < 0 || nr >= board.len() as i32 || nc < 0 || nc >= board[0].len() as i32 {
                continue;
            }

            if Self::dfs(board, word, idx + 1, nr as usize, nc as usize) {
                return true;
            }
        }

        board[row][col] = ch;
        false
    }
}
