#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
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


struct Node {
    int val;
    Node* left;
    Node* right;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
    Node(int x, Node* left, Node* right) : val(x), left(left), right(right) {}
};


// Morris Traversal

vector<int> morrisInorderTraversal(Node* root) {
     vector<int> result;
     Node* current = root;

     while(current) {
          if(current->left == nullptr) {
               // Visit the node and move to the right
               result.push_back(current->val);
               current = current->right;
          }

          else {
               // Find the inorder predecessor of the current node
               Node* predecessor = current->left;
               while(predecessor->right != nullptr && predecessor->right != current) {
                    predecessor = predecessor->right;
               }

               if (predecessor->right == nullptr) {
                    // Establish link back to the current node and move to the left child
                    predecessor->right = current;
                    current = current->left;
               }

               else {
                    // The link was already established, so we remove it and visit the node
                    predecessor->right = nullptr;
                    result.push_back(current->val);
                    current = current->right;
               }
          }
     }

     return result;
}

void printResult(const vector<int>& result) {
     for (int val : result) {
         cout << val << " ";
     }
     cout << endl;
}

int main() {
    // Example 1: Input: root = [1,null,2,3]
    Node* example1 = new Node(1);
    example1->right = new Node(2);
    example1->right->left = new Node(3);

    vector<int> result1 = morrisInorderTraversal(example1);
    cout << "Morris Traversal result: ";
    printResult(result1);

    // Example 2: Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
    Node* example2 = new Node(1);
    example2->left = new Node(2, new Node(4), new Node(5, new Node(6), new Node(7)));
    example2->right = new Node(3, nullptr, new Node(8, new Node(9), nullptr));

    vector<int> result2 = morrisInorderTraversal(example2);
    cout << "Morris Traversal result: ";
    printResult(result2);

    
    return 0;
}