use std::collections::HashMap;

struct TimeMap {
    kv: HashMap<String, Vec<(i32, String)>>,
}

impl TimeMap {
    fn new() -> Self {
        TimeMap { kv: HashMap::new() }
    }

    fn set(&mut self, key: String, value: String, timestamp: i32) {
        self.kv.entry(key).or_insert_with(Vec::new).push((timestamp, value));
    }

    fn get(&self, key: String, timestamp: i32) -> String {
        let arr = match self.kv.get(&key) {
            Some(arr) => arr,
            None => return String::new(),
        };

        let (mut left, mut right) = (0i32, arr.len() as i32 - 1);
        let mut res_idx: i32 = -1;

        while left <= right {
            let mid = left + (right - left) / 2;
            let (t, _) = &arr[mid as usize];

            if *t == timestamp {
                return arr[mid as usize].1.clone();
            }
            if *t > timestamp {
                right = mid - 1;
            } else {
                res_idx = mid;
                left = mid + 1;
            }
        }

        if res_idx == -1 {
            String::new()
        } else {
            arr[res_idx as usize].1.clone()
        }
    }
}
