impl Solution {
    pub fn hamming_weight(mut n: i32) -> i32 {
        let mut count = 0;

        while n != 0 {
            n = n & (n - 1); // clears the lowest set bit
            count += 1;
        }
        count
    }
}
