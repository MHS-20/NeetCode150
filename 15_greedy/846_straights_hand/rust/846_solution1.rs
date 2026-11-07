use std::collections::BTreeMap;

impl Solution {
    pub fn is_n_straight_hand(hand: Vec<i32>, group_size: i32) -> bool {
        if hand.len() % group_size as usize != 0 {
            return false;
        }

        let mut count = BTreeMap::new();
        for c in hand {
            *count.entry(c).or_insert(0) += 1;
        }

        while let Some((&start, _)) = count.first_key_value() {
            // start is the smallest remaining card
            for v in start..start + group_size {
                match count.get_mut(&v) {
                    None => return false, // missing value, group can't be built
                    Some(1) => {
                        count.remove(&v); // drop values that are used up
                    }
                    Some(n) => *n -= 1,
                }
            }
        }

        true
    }
}
