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

// LEETCODE: 206 (RECURSIVE WAY)
     ListNode* reverseList(ListNode* &prev, ListNode* &curr){
          if (curr == NULL) {
          // return newHead
          return prev;
          }
     
          ListNode* forward = curr->next;
          curr->next = prev;
          prev = curr;
          curr = forward;

          return reverseList(prev,curr);
     }

     ListNode* reverseList(ListNode* head) {
          ListNode* prev = NULL;
          ListNode* curr = head;
          ListNode* newHead = reverseList(prev,curr);

          return newHead;
     }

// ITERATIVE WAY
     ListNode* reverseList_1(ListNode* head) {
          ListNode* prev = NULL;
          ListNode* curr = head;

          while(curr != NULL){
               ListNode* forward = curr->next;
               curr->next = prev;
               prev = curr;
               curr = forward;
          }

          return prev;  // New head of the reversed list
     }





// LEETCODE: 876 ("Fast and Slow Pointers" Technique)
     ListNode* middleNode(ListNode* head) {
          ListNode* slow = head;
          ListNode* fast = head;

          while (fast != NULL) {
               fast = fast->next;

               if (fast != NULL){
                    fast = fast->next;
                    slow = slow->next;
               }
          }

          return slow;
     }





// LEETCODE: 234 (Palindrome Linked List)
     bool isPalindrome(ListNode* head) {
          // Edge Case
          if (head == NULL || head->next == NULL) return true;

          // Step 1: Find the middle of the linked list.
          ListNode* slow = head;
          ListNode* fast = head;

          while (fast != NULL && fast->next != NULL){
               slow = slow->next;
               fast = fast->next->next;
          }
          
          // step 2: Reverse the second half of the list.
          ListNode* secondHalf = reverseList_1(slow);
          
          // Step 3: Compare the first half and the reversed second half.
          ListNode* firstHalfHead = head;
          ListNode* secondHalfCopy = secondHalf;
          
          while(secondHalfCopy != NULL){
               if (firstHalfHead->val != secondHalfCopy->val){
                    return false;
               }
               firstHalfHead = firstHalfHead->next;
               secondHalfCopy = secondHalfCopy->next;
          }
          
          return true;
     }





// LEETCODE: 141
     void CreateCycle(ListNode*head, int pos) {
     if (pos == -1) return;

     ListNode* tail = head;
     ListNode* cycleNode = nullptr;
     int index = 0;

     while (tail->next != NULL){

          if (index == pos){
               cycleNode = tail;
          }
          
          tail = tail->next;
          index++;
     }
     // Connect the tail to the cycleNode to create a cycle.
     tail->next = cycleNode;

}

     bool hasCycle_1(ListNode *head) {                   // S.C : O(n)
          if (head == NULL || head->next == NULL) return false;

          unordered_map<ListNode*,bool> map;
          ListNode* temp = head;
          
          while(temp != NULL) {
               if (map[temp] == true) {
                    return true;
               }
               else {
                    map[temp] = true;
               }

               temp = temp->next;
          }
     
          return false;
     }

     bool hasCycle_2(ListNode *head) {                   // S.C : O(1)
          if (head == NULL || head->next == NULL) return false;

          ListNode* slow = head;
          ListNode* fast = head;

          while(fast != NULL){
               fast = fast->next;
               if (fast != NULL){
                    fast = fast->next;
                    slow = slow->next;
                    
                    if (fast == slow){
                         return true;
                    }
               }
          }

          return false;
     }
     
     




// Function to segregate 0s, 1s, and 2s in the linked list
     void segregateList_1(ListNode* &head) {             // M-1 (IMPORTANT)
     // Edge Case
     if (head == NULL || head->next == NULL) return;
     
     // Dummy nodes to represent the heads of segregated lists
     ListNode* zeroDummy = new ListNode(0);
     ListNode* oneDummy = new ListNode(0);
     ListNode* twoDummy = new ListNode(0);
     
     // Pointers to the current end of the respective lists
     ListNode* zero = zeroDummy;
     ListNode* one = oneDummy;
     ListNode* two = twoDummy;

     ListNode* curr = head;
     while(curr != nullptr) {

          if (curr->val == 0){
               zero->next = curr;
               zero = zero->next;
          }

          else if (curr->val == 1){
               one->next = curr;
               one = one->next;
          }

          else {
               two->next = curr;
               two = two->next;
          }  

          curr = curr->next; 
     }
     
     // Connect the three lists: zero -> one -> two
     zero->next = (oneDummy->next) ? oneDummy->next : twoDummy->next;
     one->next = twoDummy->next;
     two->next = nullptr;
     
     // Update head to point to the new rearranged list
     head = zeroDummy->next;
     
     // Cleanup dummy nodes
     // So that their data values i.e '0' are ignored)
     delete(zeroDummy);
     delete(oneDummy);
     delete(twoDummy);

}
     
     void segregateList_2(ListNode* &head) {
          // Edge Case
          if (head == NULL || head->next == NULL) return;

          int count0 = 0;
          int count1 = 0;
          int count2 = 0;

          ListNode *temp = head;

          while(temp != NULL){
               if (temp->val == 0){
                    count0++;
               }
               else if (temp->val == 1){
                    count1++;
               }
               else {
                    count2++;
               }

               temp = temp->next;
          }
          
          // Second pass to update the values in the linked list
          temp = head;

          while(count0--){
               temp->val = 0;
               temp = temp->next;
          }

          while(count1--){
               temp->val = 1;
               temp = temp->next;
          }

          while(count2--){
               temp->val = 2;
               temp = temp->next;
          }
     }






// Function to add 1 to the Linked List number and return the new head.
     ListNode* addOne_1(ListNode* &head) {           // M-1
          // Reverse the Linked List
          head = reverseList_1(head);
          
          ListNode* temp = head;
          int carry = 1;       // Initialize the value of carry with '1'

          while (temp != NULL) {
               int sum = temp->val + carry;
               carry = sum / 10;
               int digit = sum % 10;
               temp->val = digit;
               
               // move to next node
               // IMPORTANT STEP
               if (temp->next == NULL && carry != 0) {
                    ListNode *newNode = new ListNode(carry);
                    temp->next = newNode;
                    temp = newNode;
               }

               temp = temp->next;
          }
          
          // Again Reverse the list
          head = reverseList_1(head);

          return head;

     }
     
     ListNode* addOne_2(ListNode* &head) {           // M-2
          // Step 1: Convert the linked list into a number
          ListNode* current = head;
          int num = 0;

          while (current != NULL) {
               num = num * 10 + current->val;
               current = current->next;
          }
          
          // Step 2: Add 1 to the number.
          num = num + 1;

          // Step 3: Convert the number back into a linked list.
          ListNode *newHead = NULL;
          ListNode *newTail = NULL;
          
          // If num is 0, it means the list was 0 -> we return a single node with 1
          if (num == 0) {
          return new ListNode(1);
          }
          
          // Traverse the digits of num and create new nodes for the linked list.
          while (num > 0) {
               int digit = num % 10;
               ListNode *newNode = new ListNode(digit);

               if (newHead == NULL) {
                    // If this is the first node being added to the new list
                    newHead = newNode;
                    newTail = newNode;
               }
               
               // IMPORTANT STEP
               else {
                    // Inserting in such a way 
                    // we don't have to reverse the list
                    newNode->next = newHead;
                    newHead = newNode;
               }

               num = num / 10;
          }

          return newHead;

     }






// LEETCODE : 2 (Add Two LInked Lists)
     ListNode* addTwoNumbers_I(ListNode* l1, ListNode* l2) {
          ListNode *ans = new ListNode(0);
          ListNode *current = ans;
          int carry = 0;

          while (l1 || l2 || carry) {
               int a = l1 ? l1->val : 0;
               int b = l2 ? l2->val : 0;
               int sum = a + b + carry;
               carry = sum / 10;
               int digit = sum % 10;
               
               current->next = new ListNode(digit);
               current = current->next;

               l1 = l1 ? l1->next : nullptr;
               l2 = l2 ? l2->next : nullptr;

          }

          ListNode *finalAns = ans->next;
          delete ans;

          return finalAns;
        
    }
     
     ListNode* addTwoNumbers_R(ListNode* l1, ListNode* l2, int carry = 0) {
          if (l1 == nullptr && l2 == nullptr && carry == 0) return 0;

          int a = l1 ? l1->val : 0;
          int b = l2 ? l2->val : 0;
          int sum = a + b + carry;
          carry = sum / 10;
          int digit = sum % 10;

          ListNode *ans = new ListNode(digit);
          ans->next = addTwoNumbers_R(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr, carry);

          return ans;
     }






// LEETCODE : 25 (Reverse Nodes in K-grps)                     [IMPORTANT]
     int getLength(ListNode* head) {
          int length = 0;
          while (head != NULL){
               length++;
               head = head->next;
          }

          return length;

     }

     ListNode* reverseKGroup(ListNode* &head, int k) {
          // Node should be >= 2
          if (head == NULL || head->next == NULL) return head;
          
          int len = getLength(head);
          if (len < k){
               return head;
          }
          
          ListNode *prev = NULL;
          ListNode *current = head;
          int position = 0;

          while (position < k) {
               ListNode *front = current->next;
               current->next = prev;
               prev = current;
               current = front;
               position++;
          }

          if (current != NULL) {
               ListNode *nextGroup = reverseKGroup(current,k);
               head->next = nextGroup;
          }

          return prev;

     }






// LEETCODE : 725
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





// Checkout  Leetcode : 430 in 'LEETCODE' folder
     


// Delete N nodes after M nodes
     void LinkDelete(ListNode *head, int M, int N) {
          // Edge Case
          if (head == NULL) return;
          
          ListNode *current = head;

          for (int i = 0; i < M - 1; i++) {
               if (current == NULL) return;
               current = current->next;
          }

          // Now 'current' is at Mth node
          if (current == NULL) return;
          
          ListNode *MthNode = current;
          ListNode *it = current->next;

          for (int j = 0; j < N; j++) {
               if (it == NULL) break;

               ListNode *temp = it->next;
               delete it;
               it = temp;
          }

          MthNode->next = it;

          LinkDelete(it, M, N);

     }





// delete Nth node from the end of the linked list
     ListNode* removeKthNode_1(ListNode *head, int N) {
          if (head == NULL) return head;

          int length = 0;
          ListNode *current = head;

          while (current != NULL) {
               length++;
               current = current->next;
          }

          int count = length - N;

          if (N == length) {
               ListNode *newhead = head->next;
               delete head;
               return newhead;
          }
          
          current = head;
          while (current != NULL) {
               count--;
               if (count == 0) break;
               current = current->next;
          }

          ListNode *delNode = current->next;
          current->next = current->next->next;
          
          delete(delNode);
          
          return head;
     }

     void removeKthNode_2(ListNode *head, int N) {       // Using Fast & Slow Method
          ListNode *fast = head;
          ListNode *slow = head;
          ListNode *prev = NULL;
          
          // Move the `fast` pointer N steps ahead
          for (int i = 0; i < N; i++) {
               if (!fast) return;
               fast = fast->next;
          }
          
          // if `fast` is NULL after the first move, we need to delete the head
          if (!fast) {
               ListNode *delHead = head;
               head = head->next;
               delete(delHead);
               return;
          }
          
          // Move both `fast` and `slow` pointers until `fast` reaches the end of the list
          while (fast) {
               prev = slow;
               slow = slow->next;
               fast = fast->next;
          }

          if (prev != NULL) {
               prev->next = slow->next;
          }
          
          delete slow;
     }





// Odd-Even Linked List
     ListNode* OddEvenLL_1(ListNode* &head, vector<int> &arr) {             // S.C : O(N)
          // Edge Case 
          if (head == NULL || head->next == NULL ) return head;
          
          // For ODD
          ListNode* temp = head;
          int i = 0;

          while (temp != NULL && temp->next != NULL) {
               arr.push_back(temp->val);
               temp = temp->next->next;
               i++;
          }

          if (temp) {
               arr.push_back(temp->val);
          }
          
          // For EVEN
          temp = head->next;
          while (temp != NULL && temp->next != NULL) {
               arr.push_back(temp->val);
               temp = temp->next->next;
               i++;
          }

          if (temp) {
               arr.push_back(temp->val);
          }

          temp = head;
          int j = 0;
          while (temp != NULL) {
               temp->val = arr[j++];
               temp = temp->next;
          }

          return head;
     }
     
     ListNode* OddEvenLL_2(ListNode* &head) {                               // S.C : O(1) &  T.C : O(N/2)*2 
          if (head == NULL || head->next == NULL) return head;
          
          ListNode *odd = head;
          ListNode *even = head->next;
          ListNode *evenHead = head->next;

          // since 'Even' advances 'Odd'
          while (even != NULL && even->next != NULL) {
               odd->next = odd->next->next;
               odd = odd->next;

               even->next = even->next->next;
               even = even->next;
          } 
          
          odd->next = evenHead;

          return head;

     }





// LEETCODE : 21 (Merge Two Sorted LL) 
     ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
          ListNode *t1 = list1;
          ListNode *t2 = list2;

          // Edge Case
          if (t1 == NULL) return t2;
          if (t2 == NULL) return t1;

          ListNode *ans = new ListNode(-1);
          ListNode *temp = ans;

          while (t1 && t2) {
               if (t1->val <= t2->val) {
                    temp->next = t1;
                    temp = t1;
                    t1 = t1->next;
               }

               else {
                    temp->next = t2;
                    temp = t2;
                    t2 = t2->next;
               }

               temp = temp->next;
          }

          if (t1) temp->next = t1;
          if (t2) temp->next = t2;


          return ans->next;
     }

//  Checkout : Flatten Linked List  -->   [IMPORTANT]




// Checkout ->   LEETCODE : 138 (Copy List With Random Pointer)
     


 
// LEETCODE : 61 (Rotate the List)     [Basic But IMPORTANT]
     ListNode* rotateRight(ListNode *head, int k) {
          if (head == NULL) return head;

          int length = 0;
          ListNode *current = head;

          while (current) {
               length++;
               current = current->next;
          }

          int actualRotation = k % length;
          
          if (actualRotation == 0) return head;

          int newLastNodePos = length - actualRotation - 1;
          current = head;

          ListNode *newLastNode = head;

          for (int i = 0; i < newLastNodePos; i++) {
               newLastNode = newLastNode->next;
          }

          ListNode *newHead = newLastNode->next;
          newLastNode->next = NULL;

          ListNode *it = newHead;
          while (it->next) {
               it = it->next;
          }

          it->next = head;

          return newHead;

     }




// LEETCODE : 2058 
     vector<int> nodesBetweenCriticalPoints(ListNode* head) {
          // Fewer than 3 nodes, so no critical points.
          if (head == NULL || head->next == NULL || head->next->next == NULL){
               return {-1,-1};
          }

          vector<int> criticalPoints;
          ListNode *prev = head;
          ListNode *curr = head->next;
          int index = 1;     // Start from second node.

          while (curr->next) {

               if   ((curr->val > prev->val && curr->val > curr->next->val) || 
                    (curr->val < prev->val && curr->val < curr->next->val)) {
                         criticalPoints.push_back(index);
                    }
               
               prev = curr;
               curr = curr->next;
               index++;
          }

          if (criticalPoints.size() < 2) {
               return {-1,-1};   // If fewer than two critical points.
          }

          int minDistance = INT_MAX;
          int maxDistance = criticalPoints.back() - criticalPoints.front();

          for (int i = 1; i < criticalPoints.size(); i++) {
               minDistance = min (minDistance, criticalPoints[i] - criticalPoints[i-1]);
          }
          
          return {minDistance, maxDistance};
     }
     




// LEETCODE : 2181   (Merge Nodes in Between Zeros)  
     ListNode* mergeNodes(ListNode* head) {
          if (head == NULL) return head;

          ListNode *fast = head;
          ListNode *slow = head;
          ListNode *newLastNode = nullptr;
          
          int sum = 0;
          while (fast) {
               if (fast->val != 0) {
                    sum = sum + fast->val;
               }
               else {
                    // fast->val = 0
                    slow->val = sum;
                    newLastNode = slow;
                    slow = slow->next;
                    sum = 0;

               }
               fast = fast->next;
          }

          ListNode *temp = slow;
          newLastNode->next = NULL;
           
          // Deleting rest of the list
          while (temp) {
               ListNode *nextNode = temp->next;
               delete temp;
               temp = nextNode;
          }

          return head;

     }


  


// LEETCODE : 148 (Sort List)       (Using -> Merge Sort)
     ListNode* sortList(ListNode* &head) {
          if (head == NULL || head->next == NULL) return head;

          ListNode *midNode = middleNode(head);
          ListNode *left = midNode;
          ListNode *right = midNode->next;
          midNode->next = nullptr;  // To separate the two lists
 
          // Sort Recursively
          left = sortList(left);
          right = sortList(right);
 
          // Merge both left & right Lists
          ListNode *mergedLL = mergeTwoLists(left,right);
          return mergedLL;
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

    ListNode* head1 = new ListNode(7);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(9);
    head1->next->next->next->next = new ListNode(5);
    head1->next->next->next->next->next = new ListNode(6);
    head1->next->next->next->next->next->next = new ListNode(8);

     // ListNode* head2 = new ListNode(1);
     // head2->next = new ListNode(2);
     // head2->next->next = new ListNode(3);
     // head2->next->next->next = new ListNode(4);
     // head2->next->next->next->next = new ListNode(5);
     // head2->next->next->next->next->next = new ListNode(6);
     // head2->next->next->next->next->next->next = new ListNode(7);
    

     cout << "Original list: ";
     printList(head1);

     // sol.removeKthNode_2(head2, 5);

     ListNode* newHead = sol.sortList(head1);


     cout << "Modified Linked List: ";
     printList(newHead);


     // vector<int> result = sol.nodesBetweenCriticalPoints(head1);
     // cout << "[" << result[0] << ", " << result[1] << "]" << endl;
     

     return 0;
}




// int main() {
//      Solution sol;
//     // Example 1
//     vector<int> values1 = {1, 2, 3};
//     ListNode* head1 = sol.createLinkedList(values1);
//     int k1 = 5;
//     vector<ListNode*> result1 = sol.splitListToParts(head1, k1);
//     sol.printListParts(result1);  // Expected output: [[1], [2], [3], [], []]
    
//     // Example 2
//     vector<int> values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     ListNode* head2 = sol.createLinkedList(values2);
//     int k2 = 3;
//     vector<ListNode*> result2 = sol.splitListToParts(head2, k2);
//     sol.printListParts(result2);  // Expected output: [[1,2,3,4], [5,6,7], [8,9,10]]

//     return 0;
// }