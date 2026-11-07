// A pointer-based doubly linked list fights Rust's ownership rules (every node
// has two owners), so the nodes live in a Vec and link to each other by index.
// Slots 0 and 1 are the dummy head and tail; an evicted node's slot is reused.
use std::collections::HashMap;

const HEAD: usize = 0;
const TAIL: usize = 1;

struct Node {
    key: i32,
    value: i32,
    prev: usize,
    next: usize,
}

struct LRUCache {
    cap: usize,
    nodes: Vec<Node>,
    map: HashMap<i32, usize>,
}

impl LRUCache {
    fn new(capacity: i32) -> Self {
        let nodes = vec![
            Node { key: 0, value: 0, prev: HEAD, next: TAIL },
            Node { key: 0, value: 0, prev: HEAD, next: TAIL },
        ];
        LRUCache { cap: capacity as usize, nodes, map: HashMap::new() }
    }

    fn remove(&mut self, i: usize) {
        let (prev, next) = (self.nodes[i].prev, self.nodes[i].next);
        self.nodes[prev].next = next;
        self.nodes[next].prev = prev;
    }

    fn insert_front(&mut self, i: usize) {
        let first = self.nodes[HEAD].next;
        self.nodes[i].prev = HEAD;
        self.nodes[i].next = first;
        self.nodes[first].prev = i;
        self.nodes[HEAD].next = i;
    }

    fn get(&mut self, key: i32) -> i32 {
        match self.map.get(&key) {
            None => -1,
            Some(&i) => {
                self.remove(i);
                self.insert_front(i);
                self.nodes[i].value
            }
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        if let Some(&i) = self.map.get(&key) {
            self.nodes[i].value = value;
            self.remove(i);
            self.insert_front(i);
            return;
        }

        let i = if self.map.len() == self.cap {
            let lru = self.nodes[TAIL].prev;
            self.remove(lru);
            self.map.remove(&self.nodes[lru].key);
            self.nodes[lru].key = key;
            self.nodes[lru].value = value;
            lru // reuse the evicted slot
        } else {
            self.nodes.push(Node { key, value, prev: HEAD, next: TAIL });
            self.nodes.len() - 1
        };

        self.map.insert(key, i);
        self.insert_front(i);
    }
}
