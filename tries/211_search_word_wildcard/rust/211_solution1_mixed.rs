#[derive(Default)]
struct WordDictionary {
    children: [Option<Box<WordDictionary>>; 26],
    is_end: bool,
}

impl WordDictionary {
    fn new() -> Self {
        Self::default()
    }

    fn add_word(&mut self, word: String) {
        let mut cur = self;
        for b in word.bytes() {
            cur = cur.children[(b - b'a') as usize].get_or_insert_with(Default::default);
        }
        cur.is_end = true;
    }

    fn search(&self, word: String) -> bool {
        self.search_from(word.as_bytes())
    }

    fn search_from(&self, word: &[u8]) -> bool {
        let mut cur = self;
        for (i, &b) in word.iter().enumerate() {
            if b != b'.' {
                match &cur.children[(b - b'a') as usize] {
                    Some(next) => cur = next,
                    None => return false,
                }
            } else {
                return cur
                    .children
                    .iter()
                    .flatten()
                    .any(|n| n.search_from(&word[i + 1..]));
            }
        }
        cur.is_end
    }
}
