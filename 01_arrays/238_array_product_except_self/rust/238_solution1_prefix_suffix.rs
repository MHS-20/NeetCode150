impl Solution {
    pub fn product_except_self(nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len();
        let mut prefixes = vec![1; n];
        let mut suffixes = vec![1; n];
        let mut ans = vec![1; n];

        for i in 1..n {
            prefixes[i] = prefixes[i - 1] * nums[i - 1];
        }

        for i in (0..n - 1).rev() {
            suffixes[i] = suffixes[i + 1] * nums[i + 1];
        }

        for i in 0..n {
            ans[i] = prefixes[i] * suffixes[i];
        }

        ans
    }
}
