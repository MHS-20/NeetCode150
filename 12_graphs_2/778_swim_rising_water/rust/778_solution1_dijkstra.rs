use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn swim_in_water(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        let mut visited = vec![vec![false; n]; n];
        let mut pq = BinaryHeap::new(); // Reverse((elev, r, c))
        let dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)];

        pq.push(Reverse((grid[0][0], 0usize, 0usize)));
        visited[0][0] = true;
        let mut t = 0;

        while let Some(Reverse((elev, r, c))) = pq.pop() {
            t = t.max(elev);
            if r == n - 1 && c == n - 1 {
                return t;
            }

            for (dr, dc) in dirs {
                let (nr, nc) = (r as i32 + dr, c as i32 + dc);
                if nr < 0 || nc < 0 || nr >= n as i32 || nc >= n as i32 {
                    continue;
                }
                let (nr, nc) = (nr as usize, nc as usize);
                if visited[nr][nc] {
                    continue;
                }
                visited[nr][nc] = true;
                pq.push(Reverse((grid[nr][nc], nr, nc)));
            }
        }
        -1
    }
}
