use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct KthLargest {
    cap: usize,
    pq: BinaryHeap<Reverse<i32>>,
}

impl KthLargest {
    fn new(k: i32, nums: Vec<i32>) -> Self {
        let mut pq: BinaryHeap<_> = nums.into_iter().map(Reverse).collect();
        let cap = k as usize;
        while pq.len() > cap {
            pq.pop();
        }
        Self { cap, pq }
    }

    fn add(&mut self, val: i32) -> i32 {
        self.pq.push(Reverse(val));
        if self.pq.len() > self.cap {
            self.pq.pop();
        }
        self.pq.peek().unwrap().0
    }
}
