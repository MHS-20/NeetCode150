use std::collections::VecDeque;

const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn num_islands(mut grid: Vec<Vec<char>>) -> i32 {
        if grid.is_empty() {
            return 0;
        }
        let (rows, cols) = (grid.len(), grid[0].len());
        let mut count = 0;
        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == '1' {
                    Self::sink(&mut grid, i, j, rows, cols);
                    count += 1;
                }
            }
        }
        count
    }

    fn sink(grid: &mut Vec<Vec<char>>, r: usize, c: usize, rows: usize, cols: usize) {
        let mut q = VecDeque::from([(r, c)]);
        grid[r][c] = '0';
        while let Some((cr, cc)) = q.pop_front() {
            for (dr, dc) in DIRS {
                // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
                let (nr, nc) = (cr.wrapping_add_signed(dr), cc.wrapping_add_signed(dc));
                if nr < rows && nc < cols && grid[nr][nc] == '1' {
                    grid[nr][nc] = '0';
                    q.push_back((nr, nc));
                }
            }
        }
    }
}
