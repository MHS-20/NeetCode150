use std::collections::VecDeque;

impl Solution {
    pub fn foreign_dictionary(words: Vec<String>) -> String {
        let mut seen = [false; 26];
        let mut edge = [[false; 26]; 26];
        let mut indeg = [0; 26];
        let mut total = 0;

        for w in &words {
            for &c in w.as_bytes() {
                let i = (c - b'a') as usize;
                if !seen[i] {
                    seen[i] = true;
                    total += 1;
                }
            }
        }

        for pair in words.windows(2) {
            let (a, b) = (pair[0].as_bytes(), pair[1].as_bytes());
            match a.iter().zip(b).position(|(x, y)| x != y) {
                None => {
                    if a.len() > b.len() {
                        return String::new(); // b is a proper prefix of a: invalid
                    }
                }
                Some(j) => {
                    let (u, v) = ((a[j] - b'a') as usize, (b[j] - b'a') as usize);
                    if !edge[u][v] {
                        // avoid double-counting
                        edge[u][v] = true;
                        indeg[v] += 1;
                    }
                }
            }
        }

        // Kahn's algorithm
        let mut q: VecDeque<usize> = (0..26).filter(|&c| seen[c] && indeg[c] == 0).collect();
        let mut result = String::new();
        while let Some(u) = q.pop_front() {
            result.push((b'a' + u as u8) as char);
            for v in 0..26 {
                if edge[u][v] {
                    indeg[v] -= 1;
                    if indeg[v] == 0 {
                        q.push_back(v);
                    }
                }
            }
        }

        if result.len() == total { result } else { String::new() }
    }
}
