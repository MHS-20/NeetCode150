impl Solution {
    pub fn max_chunks_to_sorted(arr: Vec<i32>) -> i32 {
        let n = arr.len();
        let mut suf_min = vec![i32::MAX; n + 1];
        for i in (0..n).rev() {
            suf_min[i] = suf_min[i + 1].min(arr[i]);
        }

        let mut chunks = 0;
        let mut pref_max = i32::MIN;
        for i in 0..n {
            pref_max = pref_max.max(arr[i]);
            if pref_max <= suf_min[i + 1] {
                chunks += 1; // valid cut after i (i = n-1 always counts)
            }
        }
        chunks
    }
}
