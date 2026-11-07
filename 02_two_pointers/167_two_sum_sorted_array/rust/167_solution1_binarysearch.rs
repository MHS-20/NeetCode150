struct Solution;

impl Solution {
    fn two_sum(numbers: Vec<i32>, target: i32) -> Vec<i32> {
        for idx in 0..numbers.len() {
            let diff = target - numbers[idx];
            let mut i = idx as i32 + 1;
            let mut j = numbers.len() as i32 - 1;

            while i <= j {
                let mid = i + (j - i) / 2;

                if numbers[mid as usize] == diff {
                    return vec![idx as i32 + 1, mid + 1];
                }

                if numbers[mid as usize] > diff {
                    j = mid - 1;
                } else {
                    i = mid + 1;
                }
            }
        }

        vec![]
    }
}
