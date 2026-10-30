impl Solution {
    pub fn can_jump(nums: Vec<i32>) -> bool {
        let mut mx = 0;

        for (i, &n) in nums.iter().enumerate() {
            if i > mx {
                return false;
            }

            mx = mx.max(i + n as usize);
            if mx >= nums.len() - 1 {
                return true;
            }
        }

        false
    }
}
