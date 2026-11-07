impl Solution {
    pub fn swim_in_water(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        let mut parent: Vec<usize> = (0..n * n).collect();
        let mut rnk = vec![0u32; n * n];

        // pos[v] = cell index holding elevation v
        let mut pos = vec![0; n * n];
        for r in 0..n {
            for c in 0..n {
                pos[grid[r][c] as usize] = r * n + c;
            }
        }

        let dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)];

        for t in 0..n * n {
            let (r, c) = (pos[t] / n, pos[t] % n); // this cell becomes submerged
            for (dr, dc) in dirs {
                let (nr, nc) = (r as i32 + dr, c as i32 + dc);
                if nr < 0 || nc < 0 || nr >= n as i32 || nc >= n as i32 {
                    continue;
                }
                let (nr, nc) = (nr as usize, nc as usize);
                if grid[nr][nc] as usize <= t {
                    // neighbor already submerged
                    Self::unite(&mut parent, &mut rnk, r * n + c, nr * n + nc);
                }
            }
            if Self::find(&mut parent, 0) == Self::find(&mut parent, n * n - 1) {
                return t as i32;
            }
        }
        -1
    }

    fn find(parent: &mut [usize], mut x: usize) -> usize {
        while parent[x] != x {
            parent[x] = parent[parent[x]]; // path halving
            x = parent[x];
        }
        x
    }

    fn unite(parent: &mut [usize], rnk: &mut [u32], a: usize, b: usize) {
        let (mut a, mut b) = (Self::find(parent, a), Self::find(parent, b));
        if a == b {
            return;
        }
        if rnk[a] < rnk[b] {
            std::mem::swap(&mut a, &mut b);
        }
        parent[b] = a;
        if rnk[a] == rnk[b] {
            rnk[a] += 1;
        }
    }
}
