#[derive(Default)]
struct Node {
    children: [Option<Box<Node>>; 26],
    word: Option<String>, // Some means a word ends here
}

const DIRS: [(isize, isize); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

impl Solution {
    pub fn find_words(mut board: Vec<Vec<char>>, words: Vec<String>) -> Vec<String> {
        let mut root = Node::default();
        for w in words {
            let mut cur = &mut root;
            for b in w.bytes() {
                cur = cur.children[(b - b'a') as usize].get_or_insert_with(Default::default);
            }
            cur.word = Some(w);
        }

        let mut res = Vec::new();
        for r in 0..board.len() {
            for c in 0..board[0].len() {
                Self::dfs(&mut board, &mut root, r, c, &mut res);
            }
        }
        res
    }

    fn dfs(board: &mut Vec<Vec<char>>, node: &mut Node, r: usize, c: usize, res: &mut Vec<String>) {
        let ch = board[r][c];
        if ch == '#' {
            return;
        }
        let Some(next) = node.children[(ch as u8 - b'a') as usize].as_deref_mut() else {
            return;
        };

        if let Some(w) = next.word.take() {
            res.push(w); // take() avoids duplicates
        }

        board[r][c] = '#'; // mark visited
        for (dr, dc) in DIRS {
            let (Some(nr), Some(nc)) = (r.checked_add_signed(dr), c.checked_add_signed(dc)) else {
                continue;
            };
            if nr < board.len() && nc < board[0].len() {
                Self::dfs(board, next, nr, nc, res);
            }
        }
        board[r][c] = ch; // unmark
    }
}
