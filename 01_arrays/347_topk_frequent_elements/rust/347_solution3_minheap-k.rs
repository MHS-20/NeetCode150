use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashMap};

impl Solution {
    pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut freq: HashMap<i32, i32> = HashMap::new();
        for n in nums {
            *freq.entry(n).or_insert(0) += 1;
        }

        let mut min_heap: BinaryHeap<Reverse<(i32, i32)>> = BinaryHeap::new();
        for (val, cnt) in freq {
            min_heap.push(Reverse((cnt, val)));
            if min_heap.len() > k as usize {
                min_heap.pop();
            }
        }

        min_heap.into_iter().map(|Reverse((_, val))| val).collect()
    }
}
