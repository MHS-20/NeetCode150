use std::cmp::Reverse;
use std::collections::BinaryHeap;

// Definition of Interval:
// pub struct Interval {
//     pub start: i32,
//     pub end: i32,
// }

impl Solution {
    pub fn min_meeting_rooms(mut intervals: Vec<Interval>) -> i32 {
        let mut mx = 0;
        let mut min_heap = BinaryHeap::new(); // Reverse makes it a min-heap

        intervals.sort_by_key(|i| i.start);

        for i in &intervals {
            while min_heap.peek().is_some_and(|&Reverse(end)| end <= i.start) {
                min_heap.pop();
            }
            min_heap.push(Reverse(i.end));
            mx = mx.max(min_heap.len());
        }

        mx as i32
    }
}
