impl Solution {
    pub fn partition_labels(s: String) -> Vec<i32> {
        let s = s.as_bytes();
        let mut last = [0; 26];
        for (i, &c) in s.iter().enumerate() {
            last[(c - b'a') as usize] = i;
        }

        let mut result = Vec::new();
        let (mut start, mut end) = (0, 0);

        for (i, &c) in s.iter().enumerate() {
            end = end.max(last[(c - b'a') as usize]);
            if i == end {
                result.push((end - start + 1) as i32);
                start = i + 1;
            }
        }

        result
    }
}
