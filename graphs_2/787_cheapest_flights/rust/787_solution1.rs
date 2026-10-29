use std::collections::VecDeque;

impl Solution {
    pub fn find_cheapest_price(n: i32, flights: Vec<Vec<i32>>, src: i32, dst: i32, k: i32) -> i32 {
        let n = n as usize;
        let mut adj = vec![vec![]; n]; // from -> (to, price)
        for f in &flights {
            adj[f[0] as usize].push((f[1] as usize, f[2]));
        }

        let mut prices = vec![i32::MAX; n];
        let mut q = VecDeque::from([(src as usize, 0)]); // (city, cost so far)
        prices[src as usize] = 0;

        let mut flights_used = 0;
        while flights_used <= k && !q.is_empty() {
            for _ in 0..q.len() {
                let (c, p) = q.pop_front().unwrap();
                for &(next, price) in &adj[c] {
                    if p + price < prices[next] {
                        prices[next] = p + price;
                        q.push_back((next, p + price));
                    }
                }
            }
            flights_used += 1;
        }

        if prices[dst as usize] == i32::MAX { -1 } else { prices[dst as usize] }
    }
}
