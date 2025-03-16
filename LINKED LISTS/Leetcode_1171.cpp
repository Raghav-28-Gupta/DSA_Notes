#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;


// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};



class Solution {
public:

// LEETCODE : 1171 (remove zero sum consecutive nodes from linked list)

     void SanitizeMap(ListNode *curr, unordered_map<int,ListNode*> &mp, int sum) {
          int temp = sum;
          while(true) {
               temp = temp + curr->val;
               if (temp == sum) break;
               mp.erase(temp);
               curr = curr->next;
          }
     }


     ListNode* removeZeroSumSublists(ListNode* head) {
          if (head == NULL || head->next == NULL && head->val == 0) return 0;

          unordered_map<int,ListNode*> mp;
          ListNode *it = head;
          int sum = 0;
          while (it) {
               sum += it->val;

               if (sum == 0) {
                    head = it->next;
                    mp.clear();
               }

               else if (mp.find(sum) != mp.end()) {
                    SanitizeMap(mp[sum]->next, mp, sum);
                    mp[sum]->next = it->next;

               }

               else {
                    mp[sum] = it;
               }

               it = it->next;
          }
          
          return head;
     }

};


void printList(ListNode* &head) {
     ListNode* current = head;
     while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
     }
     cout << endl;
}


int main() {

     Solution sol;

     ListNode* head1 = new ListNode(1);
     head1->next = new ListNode(2);
     head1->next->next = new ListNode(-3);
     head1->next->next->next = new ListNode(3);
     head1->next->next->next->next = new ListNode(1);
     // head1->next->next->next->next->next = new ListNode(6);
     // head1->next->next->next->next->next->next = new ListNode(0);

     cout << "Original list: ";
     printList(head1);

     // sol.removeKthNode_2(head2, 5);

     ListNode* newHead = sol.removeZeroSumSublists(head1);


     cout << "Modified Linked List: ";
     printList(newHead);


     // vector<int> result = sol.nodesBetweenCriticalPoints(head1);
     // cout << "[" << result[0] << ", " << result[1] << "]" << endl;
     

     return 0;
}