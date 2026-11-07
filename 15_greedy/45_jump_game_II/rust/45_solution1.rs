impl Solution {
    pub fn jump(nums: Vec<i32>) -> i32 {
        let (mut end, mut far, mut count) = (0, 0, 0);

        for i in 0..nums.len().saturating_sub(1) {
            far = far.max(i + nums[i] as usize);
            if i == end {
                // I've used up everything reachable with k jumps,
                // so now I'm entering the area that needs k+1 jumps.
                count += 1;
                end = far;
            }
        }

        count
    }
}
