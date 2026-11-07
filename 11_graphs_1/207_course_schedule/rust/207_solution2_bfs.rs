use std::collections::VecDeque;

impl Solution {
    pub fn can_finish(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> bool {
        let n = num_courses as usize;
        let mut unlocks = vec![Vec::new(); n]; // b -> courses that need b
        let mut remaining = vec![0; n]; // prerequisites still missing

        for p in &prerequisites {
            let (a, b) = (p[0] as usize, p[1] as usize);
            unlocks[b].push(a);
            remaining[a] += 1;
        }

        let mut q: VecDeque<usize> = (0..n).filter(|&c| remaining[c] == 0).collect();

        let mut taken = 0;
        while let Some(c) = q.pop_front() {
            taken += 1;

            for &next in &unlocks[c] {
                remaining[next] -= 1;
                if remaining[next] == 0 {
                    q.push_back(next);
                }
            }
        }

        taken == n
    }
}
