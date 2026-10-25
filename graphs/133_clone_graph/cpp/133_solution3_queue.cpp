#include <queue>
#include <unordered_map>

#include "node.h"

using namespace std;

class Solution {
public:
  Node *cloneGraph(Node *node) {
    if (!node)
      return nullptr;

    unordered_map<Node *, Node *> clones;
    queue<Node *> q;
    clones[node] = new Node(node->val);
    q.push(node);

    while (!q.empty()) {
      Node *cur = q.front();
      q.pop();
      for (Node *neighbor : cur->neighbors) {
        if (!clones.count(neighbor)) {
          clones[neighbor] = new Node(neighbor->val);
          q.push(neighbor);
        }
        clones[cur]->neighbors.push_back(clones[neighbor]);
      }
    }
    return clones[node];
  }
};
