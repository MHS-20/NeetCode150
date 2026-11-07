use std::collections::{HashSet, VecDeque};

impl Solution {
    pub fn ladder_length(begin_word: String, end_word: String, word_list: Vec<String>) -> i32 {
        let mut words: HashSet<Vec<u8>> = word_list.into_iter().map(String::into_bytes).collect();
        let end = end_word.into_bytes();
        if !words.contains(&end) {
            return 0;
        }

        let begin = begin_word.into_bytes();
        words.remove(&begin);
        let mut q = VecDeque::from([begin]);
        let mut length = 1;

        while !q.is_empty() {
            for _ in 0..q.len() {
                let mut w = q.pop_front().unwrap();

                for pos in 0..w.len() {
                    let original = w[pos];
                    for c in b'a'..=b'z' {
                        if c == original {
                            continue;
                        }
                        w[pos] = c;
                        if w == end {
                            return length + 1;
                        }
                        if words.remove(&w) {
                            q.push_back(w.clone());
                        }
                    }
                    w[pos] = original;
                }
            }
            length += 1;
        }
        0
    }
}
