use std::collections::HashMap;

impl Solution {
    pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut freq: HashMap<i32, i32> = HashMap::new();
        for n in nums {
            *freq.entry(n).or_insert(0) += 1;
        }

        let mut items: Vec<(i32, i32)> = freq.into_iter().collect();
        items.sort_unstable_by(|a, b| b.1.cmp(&a.1));

        items
            .into_iter()
            .take(k as usize)
            .map(|(val, _)| val)
            .collect()
    }
}
