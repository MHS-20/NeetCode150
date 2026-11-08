impl Solution {
    pub fn reverse(mut x: i32) -> i32 {
        let mut res: i32 = 0;

        while x != 0 {
            let d = x % 10;
            x /= 10;

            if res > i32::MAX / 10 || res < i32::MIN / 10 {
                return 0;
            }
            res = res * 10 + d;
        }

        res
    }
}
