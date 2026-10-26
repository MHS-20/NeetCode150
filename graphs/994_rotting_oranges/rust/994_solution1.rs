use std::collections::VecDeque;

const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn oranges_rotting(mut grid: Vec<Vec<i32>>) -> i32 {
        let (rows, cols) = (grid.len(), grid[0].len());
        let mut q = VecDeque::new();
        let mut fresh = 0;

        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == 2 {
                    q.push_back((i, j));
                } else if grid[i][j] == 1 {
                    fresh += 1;
                }
            }
        }

        let mut minutes = 0;
        while !q.is_empty() && fresh > 0 {
            minutes += 1;
            for _ in 0..q.len() {
                let (r, c) = q.pop_front().unwrap();
                for (dr, dc) in DIRS {
                    // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
                    let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
                    if nr >= rows || nc >= cols {
                        continue;
                    }
                    if grid[nr][nc] != 1 {
                        continue;
                    }

                    grid[nr][nc] = 2;
                    fresh -= 1;
                    q.push_back((nr, nc));
                }
            }
        }
        if fresh == 0 { minutes } else { -1 }
    }
}
