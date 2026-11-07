impl Solution {
    pub fn foreign_dictionary(words: Vec<String>) -> String {
        let mut seen = [false; 26];
        let mut edge = [[false; 26]; 26];
        let mut state = [0u8; 26]; // 0 = unvisited, 1 = visiting, 2 = done
        let mut result = Vec::new();

        // 1. Register every letter
        for w in &words {
            for &c in w.as_bytes() {
                seen[(c - b'a') as usize] = true;
            }
        }

        // 2. Build edges (no in-degree needed)
        for pair in words.windows(2) {
            let (a, b) = (pair[0].as_bytes(), pair[1].as_bytes());
            match a.iter().zip(b).position(|(x, y)| x != y) {
                None => {
                    if a.len() > b.len() {
                        return String::new();
                    }
                }
                // duplicates are harmless here
                Some(j) => edge[(a[j] - b'a') as usize][(b[j] - b'a') as usize] = true,
            }
        }

        // 3. DFS from every unvisited letter
        for c in 0..26 {
            if seen[c] && state[c] == 0 && !Self::dfs(c, &edge, &mut state, &mut result) {
                return String::new();
            }
        }

        // 4. Post-order is reversed topological order
        result.reverse();
        String::from_utf8(result).unwrap()
    }

    // Returns false if a cycle is found
    fn dfs(u: usize, edge: &[[bool; 26]; 26], state: &mut [u8; 26], result: &mut Vec<u8>) -> bool {
        state[u] = 1;
        for v in 0..26 {
            if !edge[u][v] {
                continue;
            }
            if state[v] == 1 {
                return false; // back edge: cycle
            }
            if state[v] == 0 && !Self::dfs(v, edge, state, result) {
                return false; // propagate failure
            }
        }
        state[u] = 2;
        result.push(b'a' + u as u8); // post-order
        true
    }
}
