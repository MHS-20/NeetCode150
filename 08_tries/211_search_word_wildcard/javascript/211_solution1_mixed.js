class Node {
  constructor() {
    this.children = new Map();
    this.isEnd = false;
  }
}

class WordDictionary {
  constructor() {
    this.root = new Node();
  }

  addWord(word) {
    let cur = this.root;
    for (const ch of word) {
      if (!cur.children.has(ch)) cur.children.set(ch, new Node());
      cur = cur.children.get(ch);
    }
    cur.isEnd = true;
  }

  search(word) {
    return this.searchFrom(this.root, word, 0);
  }

  searchFrom(cur, word, pos) {
    for (let i = pos; i < word.length; i++) {
      const ch = word[i];
      if (ch !== ".") {
        cur = cur.children.get(ch);
        if (!cur) return false;
      } else {
        for (const n of cur.children.values()) {
          if (this.searchFrom(n, word, i + 1)) return true;
        }
        return false;
      }
    }
    return cur.isEnd;
  }
}
