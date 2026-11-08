impl Solution {
    pub fn get_sum(a: i32, b: i32) -> i32 {
        // u32: shifts on unsigned values drop high bits without panicking
        let (a, b) = (a as u32, b as u32);
        let (mut sum, mut carry) = (a ^ b, (a & b) << 1);

        while carry != 0 {
            let tmp = (sum & carry) << 1;
            sum ^= carry;
            carry = tmp;
        }

        sum as i32
    }
}
