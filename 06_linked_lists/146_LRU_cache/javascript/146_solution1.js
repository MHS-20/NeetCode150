class Node {
  constructor(key = 0, value = 0) {
    this.key = key;
    this.value = value;
    this.prev = null;
    this.next = null;
  }
}

class LRUCache {
  constructor(capacity) {
    this.cap = capacity;
    this.map = new Map();
    this.head = new Node(); // dummy nodes
    this.tail = new Node();
    this.head.next = this.tail;
    this.tail.prev = this.head;
  }

  remove(n) {
    n.prev.next = n.next;
    n.next.prev = n.prev;
  }

  insertFront(n) {
    n.prev = this.head;
    n.next = this.head.next;
    this.head.next.prev = n;
    this.head.next = n;
  }

  get(key) {
    const n = this.map.get(key);
    if (!n) return -1;

    this.remove(n);
    this.insertFront(n);
    return n.value;
  }

  put(key, value) {
    let n = this.map.get(key);
    if (n) {
      n.value = value;
      this.remove(n);
      this.insertFront(n);
      return;
    }

    if (this.map.size === this.cap) {
      const lru = this.tail.prev;
      this.remove(lru);
      this.map.delete(lru.key);
    }

    n = new Node(key, value);
    this.map.set(key, n);
    this.insertFront(n);
  }
}

module.exports = LRUCache;
