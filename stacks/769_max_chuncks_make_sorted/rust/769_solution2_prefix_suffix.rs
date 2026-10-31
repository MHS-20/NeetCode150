impl Solution {
    pub fn max_chunks_to_sorted(arr: Vec<i32>) -> i32 {
        let n = arr.len();
        let mut prefix_max = vec![0; n];
        let mut suffix_min = vec![0; n];

        prefix_max[0] = arr[0];
        for i in 1..n {
            prefix_max[i] = prefix_max[i - 1].max(arr[i]);
        }

        suffix_min[n - 1] = arr[n - 1];
        for i in (0..n - 1).rev() {
            suffix_min[i] = suffix_min[i + 1].min(arr[i]);
        }

        let mut chunks = 1; // the last chunk always exists
        for i in 0..n - 1 {
            if prefix_max[i] <= suffix_min[i + 1] {
                chunks += 1;
            }
        }

        chunks
    }
}
