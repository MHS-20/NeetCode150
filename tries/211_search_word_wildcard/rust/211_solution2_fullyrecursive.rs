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
        Self::dfs(Some(self), word.as_bytes())
    }

    fn dfs(cur: Option<&WordDictionary>, word: &[u8]) -> bool {
        let Some(cur) = cur else { return false };
        let Some((&b, rest)) = word.split_first() else {
            return cur.is_end;
        };

        if b != b'.' {
            return Self::dfs(cur.children[(b - b'a') as usize].as_deref(), rest);
        }

        cur.children.iter().any(|child| Self::dfs(child.as_deref(), rest))
    }
}
