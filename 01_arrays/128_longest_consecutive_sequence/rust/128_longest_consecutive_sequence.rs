use std::collections::HashSet;

struct Solution;

impl Solution {
    fn longest_consecutive(nums: Vec<i32>) -> i32 {
        let set: HashSet<i32> = nums.into_iter().collect();
        let mut longest = 0;

        for &n in &set {
            if !set.contains(&(n - 1)) {
                let mut count = 1;

                while set.contains(&(n + count)) {
                    count += 1;
                }

                longest = longest.max(count);
            }
        }

        longest
    }
}
