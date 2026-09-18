struct Solution;

impl Solution {
    fn two_sum(numbers: Vec<i32>, target: i32) -> Vec<i32> {
        let mut left = 0i32;
        let mut right = numbers.len() as i32 - 1;

        while left < right {
            let total = numbers[left as usize] + numbers[right as usize];

            if total == target {
                return vec![left + 1, right + 1];
            } else if total < target {
                left += 1;
            } else {
                right -= 1;
            }
        }

        vec![]
    }
}
