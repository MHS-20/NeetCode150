use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn network_delay_time(times: Vec<Vec<i32>>, n: i32, k: i32) -> i32 {
        let n = n as usize;
        let mut adj = vec![vec![]; n + 1]; // node -> (neighbor, weight)
        for t in &times {
            adj[t[0] as usize].push((t[1] as usize, t[2]));
        }

        let mut dist = vec![i32::MAX; n + 1];
        let mut pq = BinaryHeap::new(); // Reverse((dist, node)) makes it a min-heap
        dist[k as usize] = 0;
        pq.push(Reverse((0, k as usize)));

        while let Some(Reverse((d, u))) = pq.pop() {
            if d > dist[u] {
                continue; // stale entry
            }
            for &(v, w) in &adj[u] {
                if d + w < dist[v] {
                    dist[v] = d + w;
                    pq.push(Reverse((dist[v], v)));
                }
            }
        }

        let ans = *dist[1..].iter().max().unwrap();
        if ans == i32::MAX { -1 } else { ans }
    }
}
