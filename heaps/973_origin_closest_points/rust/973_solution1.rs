use std::collections::BinaryHeap;

impl Solution {
    pub fn k_closest(points: Vec<Vec<i32>>, k: i32) -> Vec<Vec<i32>> {
        // keyed by squared distance, same order as the real one
        let mut pq = BinaryHeap::new();

        for p in points {
            pq.push((p[0] * p[0] + p[1] * p[1], p));
            if pq.len() > k as usize {
                pq.pop();
            }
        }

        pq.into_iter().map(|(_, p)| p).collect()
    }
}
