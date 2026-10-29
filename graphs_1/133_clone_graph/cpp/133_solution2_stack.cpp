#include <stack>
#include <unordered_map>

#include "node.h"

using namespace std;

class Solution {
public:
  Node *cloneGraph(Node *node) {
    if (!node)
      return nullptr;

    unordered_map<Node *, Node *> clones;
    stack<Node *> st;
    clones[node] = new Node(node->val);
    st.push(node);

    while (!st.empty()) {
      Node *cur = st.top();
      st.pop();
      for (Node *neighbor : cur->neighbors) {
        if (!clones.count(neighbor)) {
          clones[neighbor] = new Node(neighbor->val);
          st.push(neighbor);
        }
        clones[cur]->neighbors.push_back(clones[neighbor]);
      }
    }
    return clones[node];
  }
};
