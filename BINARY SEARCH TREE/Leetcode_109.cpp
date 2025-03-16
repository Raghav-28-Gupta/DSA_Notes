#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <unordered_set>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <math.h>
#include <limits.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};




// Convert Sorted List To BST




// APPROACH - 1

// Helper function to find the middle element of the linked list
ListNode* findMiddle(ListNode* &head) {
     ListNode* slow = head;
     ListNode* fast = head;
     ListNode* prev = nullptr;

     while(fast != NULL && fast->next != NULL) {
          prev = slow;
          slow = slow->next;
          fast = fast->next->next;
     }
     
     // Disconnect the left half from the mid node
     if(prev != NULL) {
          prev->next = NULL;
     }
     
     return slow;
}

// Recursive function to convert sorted linked list to a height-balanced BST
TreeNode* sortedListToBST(ListNode* &head) {
     // Base Case
     if(head == nullptr) {
          return nullptr;
     }

     ListNode *mid = findMiddle(head);              // Get the middle of the linked list
     TreeNode *root = new TreeNode(mid->val);       // Create a tree node with the middle value
     
     // If mid is the same as head, return the single node (base case for single node list)
     if (head == mid) {
          return root;
     }

     // Recursively construct the left subtree and right subtree
     root->left = sortedListToBST(head);
     root->right = sortedListToBST(mid->next);

     return root;
}

// Function to print inorder traversal of the BST 
void printInorder(TreeNode* root) {
     if(!root) return;
     printInorder(root->left);
     cout << root->val << " ";
     printInorder(root->right);
}







// APPROACH - 2

int getLength(ListNode* &head) {
     ListNode* temp = head;
     int cnt = 0;
     while(temp) {
          cnt++;
          temp = temp->next;
     }

     return cnt;
}


TreeNode* sortedListToBSTHelper(ListNode* &head, int left, int right) {
     if(left > right) {
          return nullptr;
     }
     
     int mid = left + (right - left) / 2;


     TreeNode* leftSubTree = sortedListToBSTHelper(head, 0, mid - 1);
     // Allocate the current node as the root
     TreeNode* root = new TreeNode(head->val);
     // Connect left children to the root
     root->left = leftSubTree;
     

     // Move the list pointer to the next node
     head = head->next;


     TreeNode* rightSubTree = sortedListToBSTHelper(head, mid + 1, right);
     root->right = rightSubTree;

     return root;
}


TreeNode* sortedListToBST_2(ListNode* &head) {
     int size = getLength(head);
     return sortedListToBSTHelper(head, 0, size - 1);
     
}









int main() {
    // Example usage
    ListNode* head = new ListNode(-10);
    head->next = new ListNode(-3);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(9);

    TreeNode* root = sortedListToBST_2(head);

    // Inorder traversal of the resulting BST
    printInorder(root);
    return 0;
}

