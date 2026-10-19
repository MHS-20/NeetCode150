use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct MedianFinder {
    max_heap: BinaryHeap<i32>,          // left half
    min_heap: BinaryHeap<Reverse<i32>>, // right half
}

impl MedianFinder {
    fn new() -> Self {
        Self { max_heap: BinaryHeap::new(), min_heap: BinaryHeap::new() }
    }

    fn add_num(&mut self, num: i32) {
        match self.min_heap.peek() {
            Some(&Reverse(top)) if num >= top => self.min_heap.push(Reverse(num)),
            _ => self.max_heap.push(num),
        }

        if self.max_heap.len() > self.min_heap.len() + 1 {
            let top = self.max_heap.pop().unwrap();
            self.min_heap.push(Reverse(top));
        }

        if self.min_heap.len() > self.max_heap.len() {
            let Reverse(top) = self.min_heap.pop().unwrap();
            self.max_heap.push(top);
        }
    }

    fn find_median(&self) -> f64 {
        let lo = *self.max_heap.peek().unwrap() as f64;
        if (self.min_heap.len() + self.max_heap.len()) % 2 == 0 {
            (lo + self.min_heap.peek().unwrap().0 as f64) / 2.0
        } else {
            lo
        }
    }
}
