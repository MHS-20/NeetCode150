impl Solution {
    pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
        let sum_gas: i32 = gas.iter().sum();
        let sum_cost: i32 = cost.iter().sum();
        if sum_cost > sum_gas {
            return -1;
        }

        let (mut start, mut cur_gas, mut cur_pos) = (0, 0, 0);
        loop {
            cur_gas += gas[cur_pos] - cost[cur_pos];

            cur_pos = (cur_pos + 1) % gas.len();

            if cur_pos == start {
                return start as i32;
            }

            if cur_gas < 0 {
                start = cur_pos;
                cur_gas = 0;
            }
        }
    }
}
