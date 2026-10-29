const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn max_area_of_island(mut grid: Vec<Vec<i32>>) -> i32 {
        if grid.is_empty() {
            return 0;
        }

        let mut mx = 0;
        let (rows, cols) = (grid.len(), grid[0].len());

        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == 1 {
                    let mut count = 0;
                    Self::sink(&mut grid, i, j, rows, cols, &mut count);
                    mx = mx.max(count);
                }
            }
        }
        mx
    }

    fn sink(grid: &mut Vec<Vec<i32>>, r: usize, c: usize, rows: usize, cols: usize, count: &mut i32) {
        if grid[r][c] != 1 {
            return;
        }
        grid[r][c] = 0;
        *count += 1;
        for (dr, dc) in DIRS {
            // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
            let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
            if nr < rows && nc < cols {
                Self::sink(grid, nr, nc, rows, cols, count);
            }
        }
    }
}
