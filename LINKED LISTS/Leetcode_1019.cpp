#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <stack>
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

vector<int> nextLargerNodes(ListNode* head) {
     vector<int> values;

     ListNode *temp = head;
     while(head) {
          values.push_back(head->val);
          head = head->next;
     }
     
     int n = values.size();
     vector<int> results(n,0); // Initialize the result array with 0s.
     stack<int> stk;

     for(int i = 0; i < n; i++) {
          // Important Step
          while(!stk.empty() && values[i] > values[stk.top()]) {
               results[stk.top()] = values[i]; // Update result for the index on top of the stack.
               stk.pop();
          }

          stk.push(i);  // Push the current index onto the stack.
     }

     // Any remaining indices in the stack will already have their result as 0, 
     // So, no need to update.
     
     return results;
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
     head1->next->next->next->next->next = new ListNode(6);
     head1->next->next->next->next->next->next = new ListNode(0);

     cout << "Original list: ";
     printList(head1);

     vector<int> ans = sol.nextLargerNodes(head1);
     
     cout << "Output: [";
     for (auto c : ans) {
          cout << c << " ";
     }
     cout << "]" << endl;

     return 0;
}