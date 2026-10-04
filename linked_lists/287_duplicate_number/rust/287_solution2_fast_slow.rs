struct Solution;

impl Solution {
    pub fn find_duplicate(nums: Vec<i32>) -> i32 {
        let (mut slow, mut fast) = (0usize, 0usize);

        // Phase 1: find a meeting point inside the cycle
        loop {
            slow = nums[slow] as usize;
            fast = nums[nums[fast] as usize] as usize;
            if slow == fast {
                break;
            }
        }

        // Phase 2: find the cycle entrance (the duplicate)
        slow = 0;
        while slow != fast {
            slow = nums[slow] as usize;
            fast = nums[fast] as usize;
        }

        slow as i32
    }
}
