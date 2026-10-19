use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn find_kth_largest(nums: Vec<i32>, k: i32) -> i32 {
        let k = k as usize;
        let mut pq = BinaryHeap::with_capacity(k);
        for x in nums {
            if pq.len() < k {
                pq.push(Reverse(x));
            } else if let Some(mut top) = pq.peek_mut() {
                if x > top.0 {
                    *top = Reverse(x);
                }
            }
        }
        pq.peek().unwrap().0
    }
}
