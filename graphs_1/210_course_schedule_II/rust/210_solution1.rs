impl Solution {
    pub fn find_order(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> Vec<i32> {
        let n = num_courses as usize;
        let mut adjacency = vec![Vec::new(); n];
        for p in &prerequisites {
            adjacency[p[0] as usize].push(p[1] as usize);
        }

        let mut state = vec![0u8; n]; // 0 = unvisited, 1 = on path, 2 = done
        let mut order = Vec::with_capacity(n);
        for i in 0..n {
            if !Self::dfs(&adjacency, &mut state, i, &mut order) {
                return Vec::new();
            }
        }
        order
    }

    fn dfs(adjacency: &[Vec<usize>], state: &mut [u8], node: usize, order: &mut Vec<i32>) -> bool {
        if state[node] == 1 {
            return false; // cycle
        }
        if state[node] == 2 {
            return true;
        }

        state[node] = 1;
        for &next in &adjacency[node] {
            if !Self::dfs(adjacency, state, next, order) {
                return false;
            }
        }
        state[node] = 2;
        order.push(node as i32);
        true
    }
}
