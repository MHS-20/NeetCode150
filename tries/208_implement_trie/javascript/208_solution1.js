class Node {
  constructor() {
    this.children = new Map();
    this.isEnd = false;
  }
}

class Trie {
  constructor() {
    this.root = new Node();
  }

  insert(word) {
    let cur = this.root;
    for (const ch of word) {
      if (!cur.children.has(ch)) cur.children.set(ch, new Node());
      cur = cur.children.get(ch);
    }
    cur.isEnd = true;
  }

  search(word) {
    const node = this.walk(word);
    return node !== null && node.isEnd;
  }

  startsWith(prefix) {
    return this.walk(prefix) !== null;
  }

  // returns the node reached by following s, or null if the path breaks
  walk(s) {
    let cur = this.root;
    for (const ch of s) {
      cur = cur.children.get(ch);
      if (!cur) return null;
    }
    return cur;
  }
}
