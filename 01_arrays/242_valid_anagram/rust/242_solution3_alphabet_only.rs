// works if chars are a-z only
impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        if s.len() != t.len() {
            return false;
        }

        let mut count = [0i32; 26];
        for (cs, ct) in s.bytes().zip(t.bytes()) {
            count[(cs - b'a') as usize] += 1;
            count[(ct - b'a') as usize] -= 1;
        }

        count.iter().all(|&c| c == 0)
    }
}

struct Solution;
