struct Solution;

impl Solution {
    fn min_eating_speed(piles: Vec<i32>, h: i32) -> i32 {
        let mut left = 1;
        let mut right = *piles.iter().max().unwrap();

        while left < right {
            let k = left + (right - left) / 2;
            let hours: i32 = piles.iter().map(|&p| (p + k - 1) / k).sum();

            if hours > h {
                left = k + 1;
            } else {
                right = k;
            }
        }
        left
    }
}
