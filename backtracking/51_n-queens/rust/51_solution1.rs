struct State {
    n: usize,
    board: Vec<Vec<u8>>,
    cols: Vec<bool>,
    diag1: Vec<bool>,
    diag2: Vec<bool>,
    result: Vec<Vec<String>>,
}

impl State {
    fn backtrack(&mut self, row: usize) {
        let n = self.n;
        if row == n {
            let snapshot = self
                .board
                .iter()
                .map(|r| String::from_utf8(r.clone()).unwrap())
                .collect();
            self.result.push(snapshot);
            return;
        }

        for col in 0..n {
            let d1 = row + col; // "/" diagonal
            let d2 = row + n - 1 - col; // "\" diagonal, shifted
            if self.cols[col] || self.diag1[d1] || self.diag2[d2] {
                continue;
            }

            self.board[row][col] = b'Q';
            self.cols[col] = true;
            self.diag1[d1] = true;
            self.diag2[d2] = true;

            self.backtrack(row + 1);

            self.board[row][col] = b'.';
            self.cols[col] = false;
            self.diag1[d1] = false;
            self.diag2[d2] = false;
        }
    }
}

impl Solution {
    pub fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
        let n = n as usize;
        let mut st = State {
            n,
            board: vec![vec![b'.'; n]; n],
            cols: vec![false; n],
            diag1: vec![false; 2 * n - 1],
            diag2: vec![false; 2 * n - 1],
            result: Vec::new(),
        };
        st.backtrack(0);
        st.result
    }
}
