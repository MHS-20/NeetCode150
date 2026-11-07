impl Solution {
    pub fn erase_overlap_intervals(mut intervals: Vec<Vec<i32>>) -> i32 {
        intervals.sort();
        let mut kept = 0;
        let mut last_end = 0; // end of the last kept interval

        for cur in &intervals {
            if kept == 0 || last_end <= cur[0] {
                kept += 1;
                last_end = cur[1];
            } else if last_end > cur[1] {
                last_end = cur[1]; // overlap: keep the one that ends earlier
            }
        }

        intervals.len() as i32 - kept
    }
}
