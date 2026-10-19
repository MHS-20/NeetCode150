use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct MedianFinder {
    lo: BinaryHeap<i32>,          // max-heap, lower half
    hi: BinaryHeap<Reverse<i32>>, // min-heap, upper half
}

impl MedianFinder {
    fn new() -> Self {
        Self { lo: BinaryHeap::new(), hi: BinaryHeap::new() }
    }

    fn add_num(&mut self, num: i32) {
        self.lo.push(num);
        self.hi.push(Reverse(self.lo.pop().unwrap()));
        if self.hi.len() > self.lo.len() {
            self.lo.push(self.hi.pop().unwrap().0);
        }
    }

    fn find_median(&self) -> f64 {
        let lo = *self.lo.peek().unwrap() as f64;
        if self.lo.len() > self.hi.len() {
            return lo;
        }
        (lo + self.hi.peek().unwrap().0 as f64) / 2.0
    }
}
