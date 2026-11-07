use std::collections::HashSet;

impl Solution {
    pub fn contains_duplicate(nums: Vec<i32>) -> bool {
        let mut tracker = HashSet::with_capacity(nums.len());

        for x in nums {
            if !tracker.insert(x) {
                return true;
            }
        }

        false
    }
}

struct Solution;
