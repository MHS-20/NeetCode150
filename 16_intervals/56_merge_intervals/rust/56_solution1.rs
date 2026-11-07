impl Solution {
    pub fn merge(mut intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        intervals.sort();
        let mut result: Vec<Vec<i32>> = Vec::new();

        for cur in intervals {
            match result.last_mut() {
                Some(last) if last[1] >= cur[0] => last[1] = last[1].max(cur[1]),
                _ => result.push(cur),
            }
        }

        result
    }
}
