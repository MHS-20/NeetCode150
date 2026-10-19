use std::collections::{BinaryHeap, VecDeque};

impl Solution {
    pub fn least_interval(tasks: Vec<char>, n: i32) -> i32 {
        let mut arr = [0; 26];
        for ch in tasks {
            arr[(ch as u8 - b'A') as usize] += 1;
        }

        // remaining counts
        let mut pq: BinaryHeap<i32> = arr.into_iter().filter(|&c| c > 0).collect();
        let mut timer = VecDeque::new(); // (count, next_time)
        let mut time = 0;

        while !pq.is_empty() || !timer.is_empty() {
            if let Some(&(count, next_time)) = timer.front() {
                if next_time <= time {
                    pq.push(count);
                    timer.pop_front();
                }
            }

            if let Some(count) = pq.pop() {
                if count > 1 {
                    timer.push_back((count - 1, time + n + 1));
                }
            }

            time += 1;
        }

        time
    }
}
