use std::collections::VecDeque;

struct Solution;

impl Solution {
    fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let k = k as usize;
        let mut maxs = Vec::new();
        let mut dq: VecDeque<usize> = VecDeque::new(); // indices, values decreasing

        // i is the right pointer
        // i + 1 - k is the left pointer
        for i in 0..nums.len() {
            if dq.front().is_some_and(|&f| f + k <= i) {
                dq.pop_front();
            }

            while dq.back().is_some_and(|&b| nums[i] > nums[b]) {
                dq.pop_back();
            }
            dq.push_back(i);

            if i + 1 >= k {
                maxs.push(nums[dq[0]]);
            }
        }

        maxs
    }
}
