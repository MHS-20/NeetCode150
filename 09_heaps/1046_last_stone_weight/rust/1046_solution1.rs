use std::collections::BinaryHeap;

impl Solution {
    pub fn last_stone_weight(stones: Vec<i32>) -> i32 {
        let mut pq = BinaryHeap::from(stones);

        while pq.len() > 1 {
            let y = pq.pop().unwrap();
            let x = pq.pop().unwrap();
            if y != x {
                pq.push(y - x);
            }
        }

        pq.pop().unwrap_or(0)
    }
}
