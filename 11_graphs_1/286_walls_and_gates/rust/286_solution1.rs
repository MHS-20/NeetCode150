use std::collections::VecDeque;

const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn islands_and_treasure(grid: &mut Vec<Vec<i32>>) {
        let (rows, cols) = (grid.len(), grid[0].len());
        let mut q = VecDeque::new();

        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == 0 {
                    q.push_back((i, j));
                }
            }
        }

        while let Some((r, c)) = q.pop_front() {
            for (dr, dc) in DIRS {
                // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
                let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
                if nr >= rows || nc >= cols {
                    continue;
                }
                if grid[nr][nc] != i32::MAX {
                    continue;
                }

                grid[nr][nc] = grid[r][c] + 1;
                q.push_back((nr, nc));
            }
        }
    }
}
