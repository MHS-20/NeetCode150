use std::collections::HashMap;

impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        let mut groups: HashMap<String, Vec<String>> = HashMap::new();

        for s in strs {
            let key = Solution::serialize_frequency(&s);
            groups.entry(key).or_insert_with(Vec::new).push(s);
        }

        groups.into_values().collect()
    }

    fn serialize_frequency(s: &str) -> String {
        let mut alphabet = [0; 26];
        for c in s.bytes() {
            alphabet[(c - b'a') as usize] += 1;
        }

        alphabet
            .iter()
            .map(|count| count.to_string())
            .collect::<Vec<String>>()
            .join("#")
    }
}
