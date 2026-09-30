/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    ListNode *prev = nullptr;
    ListNode *cur = head;

    while (cur != nullptr) {
      ListNode *next = cur->next; // save next node
      cur->next = prev;           // reverse the link
      prev = cur;                 // move prev forward
      cur = next;                 // move cur forward
    }

    return prev; // prev is the new head
  }
};
