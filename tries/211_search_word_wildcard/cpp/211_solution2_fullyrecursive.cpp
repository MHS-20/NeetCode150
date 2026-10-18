#include <string>

using namespace std;

class WordDictionary {
  struct Node {
    Node *children[26] = {};
    bool is_end = false;
  };

  Node *root = new Node();

  bool dfs(const Node *cur, const string &word, int i) const {
    if (!cur)
      return false;
    if (i == (int)word.size())
      return cur->is_end;

    if (word[i] != '.')
      return dfs(cur->children[word[i] - 'a'], word, i + 1);

    for (const Node *child : cur->children)
      if (dfs(child, word, i + 1))
        return true;
    return false;
  }

  void destroy(Node *n) {
    if (!n)
      return;
    for (Node *c : n->children)
      destroy(c);
    delete n;
  }

public:
  ~WordDictionary() { destroy(root); }

  void addWord(const string &word) {
    Node *cur = root;
    for (char ch : word) {
      Node *&next = cur->children[ch - 'a'];
      if (!next)
        next = new Node();
      cur = next;
    }
    cur->is_end = true;
  }

  bool search(const string &word) const { return dfs(root, word, 0); }
};
