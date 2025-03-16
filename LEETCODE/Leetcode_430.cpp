#include <iostream>
using namespace std;

// Definition for a Node.
struct ListNode {
     int val;
     ListNode* next;
     ListNode* prev;
     ListNode* child;
    
     ListNode(int _val) {
        val = _val;
        next = nullptr;
        prev = nullptr;
        child = nullptr;
     }
};





class Solution {
public:

     ListNode* solve(ListNode* head) {
          if (head == nullptr) return nullptr;

          ListNode* current = head;
          ListNode* tail = current;

          while (current) {
               // If the node has a child, we need to flatten it
               if (current->child){
                    ListNode *childTail = solve(current->child);
                    
                    ListNode *temp = current->next;  // Save the next pointer
                    current->next = current->child;
                    current->next->prev = current;
                    childTail->next = temp;
                    
                    
                    if (temp) temp->prev = childTail;
                    // Set the child pointer to null
                    current->child = nullptr;
               }

               tail = current;
               current = current->next;
          }

          return tail;
     }
     
     ListNode* flatten(ListNode* head) {
          solve(head);
          return head;
     }
};



void printList(ListNode* head) {
     ListNode* curr = head;
     while (curr) {
        cout << curr->val << " ";
        curr = curr->next;
     }
     cout << endl;
}




int main() {
    // Create the nodes
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(5);
    ListNode* n6 = new ListNode(6);
    ListNode* n7 = new ListNode(7);
    ListNode* n8 = new ListNode(8);
    ListNode* n9 = new ListNode(9);
    ListNode* n10 = new ListNode(10);
    ListNode* n11 = new ListNode(11);
    ListNode* n12 = new ListNode(12);
    
    // Link the main list
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = n4;
    n4->prev = n3;
    n4->next = n5;
    n5->prev = n4;
    n5->next = n6;
    n6->prev = n5;
    
    // Link the child lists
    n3->child = n7;
    n7->next = n8;
    n8->prev = n7;
    n8->next = n9;
    n9->prev = n8;
    n9->next = n10;
    n10->prev = n9;
    
    n8->child = n11;
    n11->next = n12;
    n12->prev = n11;
    
    // Flatten the list
    Solution solution;
    ListNode* flattenedHead = solution.flatten(n1);
    
    // Print the flattened list
    printList(flattenedHead);
    
    return 0;
}