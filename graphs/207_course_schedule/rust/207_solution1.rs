impl Solution {
    pub fn can_finish(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> bool {
        let n = num_courses as usize;
        let mut adjacency = vec![Vec::new(); n];
        for p in &prerequisites {
            adjacency[p[0] as usize].push(p[1] as usize);
        }

        let mut state = vec![0u8; n]; // 0 = unvisited, 1 = on path, 2 = done
        (0..n).all(|i| Self::dfs(&adjacency, &mut state, i))
    }

    fn dfs(adjacency: &[Vec<usize>], state: &mut [u8], node: usize) -> bool {
        if state[node] == 1 {
            return false; // back on the current path: cycle
        }
        if state[node] == 2 {
            return true; // already fully explored
        }

        state[node] = 1;
        for &next in &adjacency[node] {
            if !Self::dfs(adjacency, state, next) {
                return false;
            }
        }
        state[node] = 2;
        true
    }
}
