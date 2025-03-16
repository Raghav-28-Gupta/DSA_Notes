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

// Swapping Nodes In a Linked List
     int getLength(ListNode *head) {
          int length = 0;
          while (head) {
               length++;
               head = head->next;
          }
          return length;
     }


     ListNode* swapNodes(ListNode* head, int k) {
          // Case : 1
          if (head == NULL || head->next == NULL) return head;
          int length = getLength(head);
          int lPos = k;
          int rPos = length - k + 1;
          
          if (rPos < lPos) swap(rPos,lPos);

          // Case : 2
          if (lPos == rPos) return head;

          // Case : 3
          if (length == 2) {
               ListNode *newHead = head->next;
               newHead->next = head;
               head->next = nullptr;
               head = newHead;
               return head;
          }
          
          
          // Case : 4
          if (lPos == 1) {
               ListNode *ln = head;
               ListNode *rp = head;
               for (int i = 0; i < rPos - 2; i++){
                    rp = rp->next;
               }
               ListNode *rn = rp->next;
               ListNode *rSave = rn->next;

               // Swapping
               rn->next = ln->next;
               rp->next = ln;
               ln->next = rSave;
               head = rn;
               return head;
          }
          
          int noOfNodesBetweenSwappingNodes = rPos - lPos - 1;
          // Case : 5
          if (noOfNodesBetweenSwappingNodes == 0) {
               // ln & rn are adjacents
               ListNode *lp = head;
               for (int i = 0; i < lPos - 2; i++){
                    lp = lp->next;
               }
               ListNode *ln = lp->next;
               
               ListNode *rp = head;
               for (int i = 0; i < rPos - 2; i++){
                    rp = rp->next;
               }
               ListNode *rn = rp->next;
               ListNode *rSave = rn->next;

               // Swapping
               lp->next = rp->next;
               rn->next = rp;     // Because they are adjacent
               rp->next = rSave;
               return head;
          }

          else {
               // noOfNodesBetweenSwappingNodes >= 1
               ListNode *lp = head;
               for (int i = 0; i < lPos - 2; i++){
                    lp = lp->next;
               }
               ListNode *ln = lp->next;
               
               ListNode *rp = head;
               for (int i = 0; i < rPos - 2; i++){
                    rp = rp->next;
               }
               ListNode *rn = rp->next;
               ListNode *rSave = rn->next;

               // Swapping
               lp->next = rn;
               rn->next = ln->next;
               rp->next = ln;
               ln->next = rSave;

               return head;
          }
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

     ListNode* newHead = sol.swapNodes(head1,2);


     cout << "Modified Linked List: ";
     printList(newHead);


     // vector<int> result = sol.nodesBetweenCriticalPoints(head1);
     // cout << "[" << result[0] << ", " << result[1] << "]" << endl;
     

     return 0;
}