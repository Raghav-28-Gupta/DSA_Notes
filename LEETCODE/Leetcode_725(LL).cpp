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


     vector<ListNode*> splitListToParts(ListNode* head, int k) {
          int length = 0;
          auto temp = head;

          while (temp) {
               length++;
               temp = temp->next;
          }
          
          vector<ListNode*> ans(k, nullptr);

          temp = head;
          int partSize = length / k;
          int extraNodes = length % k;

          for (int i = 0; i < k && temp; i++) {
               ans[i] = temp;
               // At this point whole LL is now stored in 'ans' vector
               int currentPartSize = partSize + (extraNodes > 0 ? 1 : 0);
               extraNodes--;

               for (int j = 0; j < currentPartSize - 1; j++) {
                    temp = temp->next;
               }
               
               // Disconnect the end of the current part from the rest of the list
               auto nextPartStarting = temp->next;
               temp->next = nullptr;
               temp = nextPartStarting;
          }

          return ans;
     }

     ListNode* createLinkedList(const vector<int>& vals) {
          // Edge Case
          if (vals.empty()) return nullptr;

          ListNode* head = new ListNode(vals[0]);
          ListNode* current = head;

          for (int i = 1; i < vals.size(); ++i) {
               current->next = new ListNode(vals[i]);
               current = current->next;
          }

          return head;
     }

     void printListParts(const vector<ListNode*>& parts) {

          for (int i = 0; i < parts.size(); ++i) {
          ListNode* temp = parts[i];
          cout << "[";

          while (temp) {
               cout << temp->val;
               if (temp->next) cout << ",";
               temp = temp->next;
          }

          cout << "] ";
          }    
          cout << endl;

     }

};     



int main() {
     Solution sol;
    // Example 1
    vector<int> values1 = {1, 2, 3};
    ListNode* head1 = sol.createLinkedList(values1);
    int k1 = 5;
    vector<ListNode*> result1 = sol.splitListToParts(head1, k1);
    sol.printListParts(result1);  // Expected output: [[1], [2], [3], [], []]
    
    // Example 2
    vector<int> values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ListNode* head2 = sol.createLinkedList(values2);
    int k2 = 3;
    vector<ListNode*> result2 = sol.splitListToParts(head2, k2);
    sol.printListParts(result2);  // Expected output: [[1,2,3,4], [5,6,7], [8,9,10]]

    return 0;
}