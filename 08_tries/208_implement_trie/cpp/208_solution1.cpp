#include <string>

using namespace std;

class Trie {
private:
  struct Node {
    Node *children[26] = {};
    bool is_end = false;
  };

  Node *root;

  void destroy(Node *n) {
    if (!n)
      return;
    for (Node *c : n->children)
      destroy(c);
    delete n;
  }

public:
  Trie() { root = new Node(); }
  ~Trie() { destroy(root); }

  void insert(string word) {
    Node *cur = root;
    for (char ch : word) {
      int i = ch - 'a';
      if (!cur->children[i])
        cur->children[i] = new Node();
      cur = cur->children[i];
    }
    cur->is_end = true;
  }

  bool search(string word) {
    Node *cur = root;
    for (char ch : word) {
      cur = cur->children[ch - 'a'];
      if (!cur)
        return false;
    }
    return cur->is_end;
  }

  bool startsWith(string prefix) {
    Node *cur = root;
    for (char ch : prefix) {
      cur = cur->children[ch - 'a'];
      if (!cur)
        return false;
    }
    return true;
  }
};
