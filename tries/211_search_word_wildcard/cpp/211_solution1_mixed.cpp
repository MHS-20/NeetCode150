#include <string>

using namespace std;

class WordDictionary {
  struct Node {
    Node *children[26] = {};
    bool is_end = false;
  };

  Node *root;

  bool searchFrom(const Node *cur, const string &word, int pos) const {
    for (int i = pos; i < (int)word.size(); i++) {
      char ch = word[i];
      if (ch != '.') {
        cur = cur->children[ch - 'a'];
        if (!cur)
          return false;
      } else {
        for (const Node *n : cur->children) {
          if (n && searchFrom(n, word, i + 1))
            return true;
        }
        return false;
      }
    }
    return cur->is_end;
  }

  void destroy(Node *n) {
    if (!n)
      return;
    for (Node *c : n->children)
      destroy(c);
    delete n;
  }

public:
  WordDictionary() { root = new Node(); }
  ~WordDictionary() { destroy(root); }

  void addWord(const string &word) {
    Node *cur = root;
    for (char ch : word) {
      int i = ch - 'a';
      if (!cur->children[i])
        cur->children[i] = new Node();
      cur = cur->children[i];
    }
    cur->is_end = true;
  }

  bool search(const string &word) const { return searchFrom(root, word, 0); }
};
