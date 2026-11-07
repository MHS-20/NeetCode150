#include "node.h"
#include <unordered_map>

using namespace std;

class Solution {
public:
  Node *copyRandomList(Node *head) {
    unordered_map<Node *, Node *> copyOf;
    copyOf[nullptr] = nullptr; // null original -> null copy

    // pass 1: create all copies (no links yet)
    for (Node *cur = head; cur; cur = cur->next)
      copyOf[cur] = new Node(cur->val);

    // pass 2: wire up next and random
    for (Node *cur = head; cur; cur = cur->next) {
      copyOf[cur]->next = copyOf[cur->next];
      copyOf[cur]->random = copyOf[cur->random];
    }

    return copyOf[head];
  }
};
