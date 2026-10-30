impl Solution {
    pub fn max_sub_array(nums: Vec<i32>) -> i32 {
        let mut sum = 0;
        let mut mx = i32::MIN;

        for n in nums {
            sum += n;
            mx = mx.max(sum);
            if sum < 0 {
                sum = if n < 0 { 0 } else { n };
            }
        }

        mx
    }
}
