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
    return this.dfs(this.root, word, 0);
  }

  dfs(cur, word, i) {
    if (!cur) return false;
    if (i === word.length) return cur.isEnd;

    if (word[i] !== ".") return this.dfs(cur.children.get(word[i]), word, i + 1);

    for (const child of cur.children.values())
      if (this.dfs(child, word, i + 1)) return true;
    return false;
  }
}
