#include <iostream>
using namespace std;

// Node structure for the linked list
struct ListNode {
     int data;
     ListNode* next;
     ListNode* bottom;

     ListNode(int x) {
        data = x;
        next = nullptr;
        bottom = nullptr;
     }
};


// Function to merge two sorted linked lists

ListNode* merge (ListNode *a, ListNode *b) {
     if (!a) return b; // If one list is empty, return the other list
     if (!b) return a;
     
     
     if (a->data < b->data) {
         a->bottom = merge(a->bottom, b);
          return a;
     }

     else {
          b->bottom = merge(a, b->bottom);
          return b;
     }
     
}

ListNode *flatten (ListNode *root) {
     // Base case: if root is null or there is no next list
     if (!root || !root->next) return root;
     
     // By flattening the last sublist first, 
     // the complexity of merging becomes easier 
     // as we already have a sorted list to merge with the current sublist.


     // Recursively flatten the next list
     root->next = flatten(root->next);

     // Merge the current list (root) with the flattened next list
     root = merge(root,root->next);

     return root;

}




void printList(ListNode* head) {
     while (head) {
        cout << head->data << " ";
        head = head->bottom;
     }
     cout << endl;
}




int main() {
    // Example: Creating linked list with sub-linked-lists

    ListNode* root = new ListNode(5);
    root->bottom = new ListNode(7);
    root->bottom->bottom = new ListNode(8);
    root->bottom->bottom->bottom = new ListNode(30);

    root->next = new ListNode(10);
    root->next->bottom = new ListNode(20);

    root->next->next = new ListNode(19);
    root->next->next->bottom = new ListNode(22);
    root->next->next->bottom->bottom = new ListNode(50);

    root->next->next->next = new ListNode(28);
    root->next->next->next->bottom = new ListNode(35);
    root->next->next->next->bottom->bottom = new ListNode(40);
    root->next->next->next->bottom->bottom->bottom = new ListNode(45);

    // Flatten the linked list
    root = flatten(root);

    // Print the flattened list
    printList(root);

    return 0;
}