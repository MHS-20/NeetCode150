use std::collections::VecDeque;

impl Solution {
    pub fn swim_in_water(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len() as i32;
        let (mut lo, mut hi) = (0, n * n - 1);
        while lo < hi {
            let mid = lo + (hi - lo) / 2;
            if Self::can_reach(&grid, mid) {
                hi = mid; // works: try lower
            } else {
                lo = mid + 1; // fails: need more water
            }
        }
        lo
    }

    fn can_reach(grid: &[Vec<i32>], t: i32) -> bool {
        let n = grid.len();
        if grid[0][0] > t {
            return false;
        }
        let mut visited = vec![vec![false; n]; n];
        let mut q = VecDeque::from([(0usize, 0usize)]);
        visited[0][0] = true;
        let dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)];

        while let Some((r, c)) = q.pop_front() {
            if r == n - 1 && c == n - 1 {
                return true;
            }
            for (dr, dc) in dirs {
                let (nr, nc) = (r as i32 + dr, c as i32 + dc);
                if nr < 0 || nc < 0 || nr >= n as i32 || nc >= n as i32 {
                    continue;
                }
                let (nr, nc) = (nr as usize, nc as usize);
                if visited[nr][nc] || grid[nr][nc] > t {
                    continue;
                }
                visited[nr][nc] = true;
                q.push_back((nr, nc));
            }
        }
        false
    }
}
