use std::collections::HashMap;

impl Solution {
    pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut freq: HashMap<i32, i32> = HashMap::new();
        for n in &nums {
            *freq.entry(*n).or_insert(0) += 1;
        }

        let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); nums.len() + 1];
        for (val, cnt) in freq {
            buckets[cnt as usize].push(val);
        }

        let mut res = Vec::new();
        for bucket in buckets.iter().rev() {
            for &val in bucket {
                res.push(val);
                if res.len() == k as usize {
                    return res;
                }
            }
        }

        res
    }
}
