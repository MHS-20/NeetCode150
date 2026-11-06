impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        let n = n as usize;
        let mut memo = vec![-1; n + 1];
        Self::ways(n, &mut memo)
    }

    fn ways(i: usize, memo: &mut Vec<i32>) -> i32 {
        if i <= 2 {
            return i as i32; // ways(1) = 1, ways(2) = 2
        }
        if memo[i] != -1 {
            return memo[i];
        }
        memo[i] = Self::ways(i - 1, memo) + Self::ways(i - 2, memo);
        memo[i]
    }
}
