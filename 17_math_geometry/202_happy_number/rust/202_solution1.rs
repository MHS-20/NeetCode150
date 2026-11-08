impl Solution {
    fn next(mut n: i32) -> i32 {
        let mut sum = 0;
        while n > 0 {
            let d = n % 10;
            sum += d * d;
            n /= 10;
        }
        sum
    }

    pub fn is_happy(n: i32) -> bool {
        let (mut slow, mut fast) = (n, Self::next(n));
        while fast != 1 && slow != fast {
            slow = Self::next(slow);
            fast = Self::next(Self::next(fast));
        }
        fast == 1
    }
}
