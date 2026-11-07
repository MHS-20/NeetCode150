use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn min_interval(mut intervals: Vec<Vec<i32>>, queries: Vec<i32>) -> Vec<i32> {
        let mut result = vec![0; queries.len()];
        let mut idx: Vec<usize> = (0..queries.len()).collect();
        let mut min_heap = BinaryHeap::new(); // Reverse((size, end))

        intervals.sort();
        idx.sort_by_key(|&k| queries[k]);

        let mut i = 0;
        for j in idx {
            let q = queries[j];

            while i < intervals.len() && intervals[i][0] <= q {
                let (left, right) = (intervals[i][0], intervals[i][1]);
                min_heap.push(Reverse((right - left + 1, right)));
                i += 1;
            }

            while let Some(&Reverse((_, end))) = min_heap.peek() {
                if end >= q {
                    break;
                }
                min_heap.pop();
            }

            result[j] = min_heap.peek().map_or(-1, |&Reverse((size, _))| size);
        }

        result
    }
}
