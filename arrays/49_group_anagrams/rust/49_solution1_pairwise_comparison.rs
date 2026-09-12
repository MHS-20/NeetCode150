use std::collections::HashMap;

impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        let mut result: Vec<Vec<String>> = Vec::new();

        for s in strs {
            let mut placed = false;
            for group in result.iter_mut() {
                if Solution::is_anagram(&s, &group[0]) {
                    group.push(s.clone());
                    placed = true;
                    break;
                }
            }

            if !placed {
                result.push(vec![s]);
            }
        }

        result
    }

    fn is_anagram(s: &str, t: &str) -> bool {
        if s.len() != t.len() {
            return false;
        }

        let mut freq: HashMap<char, i32> = HashMap::new();
        for c in s.chars() {
            *freq.entry(c).or_insert(0) += 1;
        }
        for c in t.chars() {
            let count = freq.entry(c).or_insert(0);
            *count -= 1;
            if *count < 0 {
                return false;
            }
        }
        true
    }
}
