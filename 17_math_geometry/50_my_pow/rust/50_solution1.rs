impl Solution {
    pub fn my_pow(mut x: f64, n: i32) -> f64 {
        let neg = n < 0;
        let mut big_n = (n as i64).abs(); // i32::MIN.abs() overflows

        let mut res = 1.0;
        while big_n > 0 {
            if big_n & 1 == 1 {
                res *= x;
            }
            x *= x;
            big_n >>= 1;
        }
        if neg { 1.0 / res } else { res }
    }
}
