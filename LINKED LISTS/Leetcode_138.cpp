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

// Definition for a Node
class Node {
public:
     int val;
     Node* next;
     Node* random;

     Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
     }
};



class Solution {
public:

// LEETCODE :138 (Copy List With Random Pointer)

     Node* copyRandomList_1(Node* head) {                  // S.C : O(1)
          // Edge Case
          if (head == NULL) return head;

          // Step 1: Create new nodes and insert them next to original nodes
          Node *current = head;
          while (current) {
               Node *copy = new Node(current->val);
               copy->next = current->next;
               current->next = copy;
               current = copy->next;
          }


          // Step 2: Assign random pointers for the copied nodes
          current = head;
          while (current) {
               if (current->random) {
                    current->next->random = current->random->next;
                    // 'current->next' refers to the copied node
                    // 'current->random->next' :
                    // refers to the copied node of the node 
                    // that the random pointer of the original node points to
               }

               current = current->next->next;
          }


          // Step 3: Separate the original and copied lists
          current = head;
          Node *copiedHead = head->next;
          Node *copy = copiedHead;

          while (current) {
               current->next = current->next->next;
               if (copy->next) {
                    copy->next = copy->next->next;
               }

               current = current->next;
               copy = copy->next;
          }
          
          return copiedHead;

     }

     Node* copyRandomList_2(Node* head) {                  // S.C : O(N)
          // Edge Case
          if (head == NULL) return head;
          
          unordered_map<Node*, Node*> nodeMap;
          Node *current = head;
          
          // First pass: create new nodes and map the original to the copy
          while (current) {
               nodeMap[current] = new Node(current->val);
               current = current->next;
          }

          current = head;
          while (current) {
               nodeMap[current]->next = nodeMap[current->next];      // Copy the next pointer
               nodeMap[current]->random = nodeMap[current->random];  // Copy the random pointer
               current = current->next;
          }
          
          // Step 3: Return the head of the copied list
          return nodeMap[head];
     }


};   



void printList(Node* head) {
    while (head) {
        std::cout << "Node value: " << head->val;
        if (head->random) {
            std::cout << ", Random points to: " << head->random->val;
        } else {
            std::cout << ", Random points to: null";
        }
        std::cout << std::endl;
        head = head->next;
    }
}

int main() {
    // Create a test case for the linked list
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    
    node1->next = node2;
    node2->next = node3;

    // Setting up random pointers
    node1->random = node3;
    node2->random = node1;
    node3->random = nullptr;

    // Display original list
    cout << "Original List:" << endl;
    printList(node1);

    // Create a deep copy of the list
    Solution sol;
    Node* copiedList = sol.copyRandomList_2(node1);

    // Display copied list
    cout << "\nCopied List:" << endl;
    printList(copiedList);

    return 0;
}