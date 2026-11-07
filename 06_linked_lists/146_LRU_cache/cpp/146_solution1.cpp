#include <unordered_map>
using namespace std;

class LRUCache {
  struct Node {
    int key, value;
    Node *prev = nullptr, *next = nullptr;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
  };

  int cap;
  Node *head, *tail; // dummy nodes
  unordered_map<int, Node *> map;

  void remove(Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }

  void insertFront(Node *n) {
    n->prev = head;
    n->next = head->next;
    head->next->prev = n;
    head->next = n;
  }

public:
  LRUCache(int capacity) : cap(capacity) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
  }

  ~LRUCache() {
    Node *cur = head;
    while (cur) {
      Node *nxt = cur->next;
      delete cur;
      cur = nxt;
    }
  }

  int get(int key) {
    auto it = map.find(key);
    if (it == map.end())
      return -1;

    Node *n = it->second;
    remove(n);
    insertFront(n);
    return n->value;
  }

  void put(int key, int value) {
    auto it = map.find(key);
    if (it != map.end()) {
      Node *n = it->second;
      n->value = value;
      remove(n);
      insertFront(n);
      return;
    }

    if ((int)map.size() == cap) {
      Node *lru = tail->prev;
      remove(lru);
      map.erase(lru->key); // erase before delete
      delete lru;
    }

    Node *n = new Node(key, value);
    map[key] = n;
    insertFront(n);
  }
};
