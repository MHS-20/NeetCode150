use std::collections::{BinaryHeap, HashMap};

impl Solution {
    pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut freq: HashMap<i32, i32> = HashMap::new();
        for n in nums {
            *freq.entry(n).or_insert(0) += 1;
        }

        let mut max_heap: BinaryHeap<(i32, i32)> = BinaryHeap::new();
        for (val, cnt) in freq {
            max_heap.push((cnt, val));
        }

        let mut res = Vec::new();
        for _ in 0..k {
            if let Some((_, val)) = max_heap.pop() {
                res.push(val);
            }
        }
        res
    }
}
