#pragma once

// Definition for a Node.
class Node {
public:
  int val;
  Node *next;
  Node *random;

  Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};
