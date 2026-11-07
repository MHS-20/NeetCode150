struct Solution;

impl Solution {
    fn encode(strs: Vec<String>) -> String {
        let mut encoded = String::new();
        for s in &strs {
            encoded.push_str(&s.len().to_string());
            encoded.push('-');
            encoded.push_str(s);
        }
        encoded
    }

    fn decode(s: String) -> Vec<String> {
        let bytes = s.as_bytes();
        let mut res = Vec::new();
        let mut i = 0;

        while i < bytes.len() {
            let delim_pos = s[i..].find('-').unwrap() + i;
            let len: usize = s[i..delim_pos].parse().unwrap();

            res.push(s[delim_pos + 1..delim_pos + 1 + len].to_string());
            i = delim_pos + 1 + len;
        }

        res
    }
}
