use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct KthLargest {
    cap: usize,
    pq: BinaryHeap<Reverse<i32>>,
}

impl KthLargest {
    fn new(k: i32, nums: Vec<i32>) -> Self {
        let mut kl = Self { cap: k as usize, pq: BinaryHeap::new() };
        for n in nums {
            kl.add(n);
        }
        kl
    }

    fn add(&mut self, val: i32) -> i32 {
        if self.pq.len() < self.cap {
            self.pq.push(Reverse(val));
        } else if let Some(mut top) = self.pq.peek_mut() {
            if val > top.0 {
                *top = Reverse(val);
            }
        }
        self.pq.peek().unwrap().0
    }
}
