#[derive(Default)]
struct TrieNode {
    children: [Option<Box<TrieNode>>; 26],
    is_word: bool,
}

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        // Build the trie from the dictionary
        let mut root = TrieNode::default();
        for w in &word_dict {
            let mut node = &mut root;
            for c in w.bytes() {
                node = node.children[(c - b'a') as usize].get_or_insert_with(Default::default);
            }
            node.is_word = true;
        }

        let b = s.as_bytes();
        let n = b.len();
        let mut dp = vec![false; n + 1];
        dp[0] = true;

        for j in 0..n {
            if !dp[j] {
                continue; // only start a word where the prefix is segmentable
            }

            // Walk s and the trie together, starting at j
            let mut node = &root;
            for k in j..n {
                match &node.children[(b[k] - b'a') as usize] {
                    Some(next) => node = next,
                    None => break, // no dictionary word continues this way
                }
                if node.is_word {
                    dp[k + 1] = true; // s[j..k] is a word, so the first k+1 chars are segmentable
                }
            }
        }
        dp[n]
    }
}
