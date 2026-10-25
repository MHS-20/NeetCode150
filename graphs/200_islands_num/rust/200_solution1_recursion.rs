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
        if grid[r][c] != '1' {
            return;
        }
        grid[r][c] = '0';
        for (dr, dc) in DIRS {
            // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
            let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
            if nr < rows && nc < cols {
                Self::sink(grid, nr, nc, rows, cols);
            }
        }
    }
}
