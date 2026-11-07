impl Solution {
    pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
        let (mut total, mut cur, mut start) = (0, 0, 0);
        for i in 0..gas.len() {
            let diff = gas[i] - cost[i];
            total += diff;
            cur += diff;
            if cur < 0 {
                start = i + 1;
                cur = 0;
            }
        }
        if total < 0 { -1 } else { start as i32 }
    }
}
