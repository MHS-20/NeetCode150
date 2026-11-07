const DIRS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn pacific_atlantic(heights: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let (rows, cols) = (heights.len(), heights[0].len());
        let mut pacific = vec![vec![false; cols]; rows];
        let mut atlantic = vec![vec![false; cols]; rows];

        for i in 0..rows {
            Self::dfs(&heights, &mut pacific, i, 0, i32::MIN);
            Self::dfs(&heights, &mut atlantic, i, cols - 1, i32::MIN);
        }
        for j in 0..cols {
            Self::dfs(&heights, &mut pacific, 0, j, i32::MIN);
            Self::dfs(&heights, &mut atlantic, rows - 1, j, i32::MIN);
        }

        let mut result = Vec::new();
        for i in 0..rows {
            for j in 0..cols {
                if pacific[i][j] && atlantic[i][j] {
                    result.push(vec![i as i32, j as i32]);
                }
            }
        }
        result
    }

    fn dfs(heights: &[Vec<i32>], ocean: &mut Vec<Vec<bool>>, r: usize, c: usize, prev_height: i32) {
        if ocean[r][c] || heights[r][c] < prev_height {
            return;
        }

        ocean[r][c] = true;
        let (rows, cols) = (heights.len(), heights[0].len());
        for (dr, dc) in DIRS {
            // wrapping_add_signed turns -1 at 0 into usize::MAX, caught by the bounds check
            let (nr, nc) = (r.wrapping_add_signed(dr), c.wrapping_add_signed(dc));
            if nr < rows && nc < cols {
                Self::dfs(heights, ocean, nr, nc, heights[r][c]);
            }
        }
    }
}
