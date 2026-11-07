#[derive(Default)]
struct Trie {
    children: [Option<Box<Trie>>; 26],
    is_end: bool,
}

impl Trie {
    fn new() -> Self {
        Self::default()
    }

    fn insert(&mut self, word: String) {
        let mut cur = self;
        for b in word.bytes() {
            cur = cur.children[(b - b'a') as usize].get_or_insert_with(Default::default);
        }
        cur.is_end = true;
    }

    fn search(&self, word: String) -> bool {
        self.walk(&word).is_some_and(|n| n.is_end)
    }

    fn starts_with(&self, prefix: String) -> bool {
        self.walk(&prefix).is_some()
    }

    // returns the node reached by following s, or None if the path breaks
    fn walk(&self, s: &str) -> Option<&Trie> {
        let mut cur = self;
        for b in s.bytes() {
            cur = cur.children[(b - b'a') as usize].as_deref()?;
        }
        Some(cur)
    }
}
