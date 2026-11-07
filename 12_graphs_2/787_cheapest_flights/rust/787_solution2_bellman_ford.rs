impl Solution {
    pub fn find_cheapest_price(n: i32, flights: Vec<Vec<i32>>, src: i32, dst: i32, k: i32) -> i32 {
        let mut prices = vec![i32::MAX; n as usize];
        prices[src as usize] = 0;

        // Bellman-Ford limited to k + 1 rounds: round i allows i flights
        for _ in 0..=k {
            let mut next = prices.clone(); // reads come from the previous round only
            for f in &flights {
                let (from, to, price) = (f[0] as usize, f[1] as usize, f[2]);
                if prices[from] != i32::MAX && prices[from] + price < next[to] {
                    next[to] = prices[from] + price;
                }
            }
            prices = next;
        }

        if prices[dst as usize] == i32::MAX { -1 } else { prices[dst as usize] }
    }
}
