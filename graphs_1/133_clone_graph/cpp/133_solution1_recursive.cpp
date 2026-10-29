#include <unordered_map>

#include "node.h"

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
private:
  unordered_map<Node *, Node *> clones;

public:
  Node *cloneGraph(Node *node) {
    if (!node)
      return nullptr;

    if (!clones.count(node)) {
      clones[node] = new Node(node->val);
      for (auto cur : node->neighbors) {
        clones[node]->neighbors.push_back(cloneGraph(cur));
      }
    }

    return clones[node];
  }
};
