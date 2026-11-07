#include "node.h"
#include <unordered_map>

using namespace std;

class Solution {
public:
  Node *copyRandomList(Node *head) {
    if (!head)
      return nullptr;

    // pass 1: interleave copies
    for (Node *cur = head; cur; cur = cur->next->next) {
      Node *copy = new Node(cur->val);
      copy->next = cur->next;
      cur->next = copy;
    }

    // pass 2: set random pointers
    for (Node *cur = head; cur; cur = cur->next->next) {
      if (cur->random)
        cur->next->random = cur->random->next;
    }

    // pass 3: separate the lists
    Node *copyHead = head->next;
    for (Node *cur = head; cur; cur = cur->next) {
      Node *copy = cur->next;
      cur->next = copy->next;
      if (copy->next)
        copy->next = copy->next->next;
    }

    return copyHead;
  }
};
