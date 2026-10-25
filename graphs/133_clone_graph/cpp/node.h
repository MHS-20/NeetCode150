#pragma once

#include <vector>

using namespace std;

// Definition for a Node.
class Node {
public:
  int val;
  vector<Node *> neighbors;
  Node() : val(0) {}
  Node(int _val) : val(_val) {}
  Node(int _val, vector<Node *> _neighbors)
      : val(_val), neighbors(_neighbors) {}
};
