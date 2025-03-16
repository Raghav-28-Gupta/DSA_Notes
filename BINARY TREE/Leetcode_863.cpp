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


class Node {
public:
     int data;
     Node* left;
     Node* right;

     Node (int val) {
          this->data = val;
          left = nullptr;
          right = nullptr;
     }
};



// LEETCODE : 863 (All Nodes Distance in K in Binary Tree)
void mapParent(Node* root, unordered_map<Node*, Node*>& parentMap) {
     if (!root) return;

     if (root->left) {
          parentMap[root->left] = root;
          mapParent(root->left, parentMap);
     }

     if (root->right) {
          parentMap[root->right] = root;
          mapParent(root->right, parentMap);
     }
}


vector<int> distanceK(Node* root, Node* target, int k) {
     unordered_map<Node*, Node*> parentMap;
     parentMap[root] = nullptr;
     mapParent(root, parentMap);

     unordered_map<Node*,bool> visited;
     queue<Node*> q;
     q.push(target);
     visited[target] = true;
    
     int currentLevel = 0;
     while(!q.empty()) {
          int size = q.size();
          if (currentLevel == k) break;

          currentLevel++;
          // Traverse all nodes at the current level
          for (int i = 0; i < size; i++) {
               auto front = q.front();
               q.pop();

               if (front->left && visited.find(front->left) == visited.end()) {
                    // Front has its left child, and not yet visited
                    q.push(front->left);
                    visited[front->left] = true;
               } 

               if (front->right && visited.find(front->right) == visited.end()) {
                    // Front has its right child, and not yet visited
                    q.push(front->right);
                    visited[front->right] = true;
               }

               auto parentNodeOfFront = parentMap[front];
               if (parentNodeOfFront && visited.find(parentNodeOfFront) == visited.end()) {
                    // Front has its Parent Node, and not yet visited
                    q.push(parentNodeOfFront);
                    visited[parentNodeOfFront] = true;
               }
          }
     }


     vector<int> ans;
     while(!q.empty()) {
          auto front = q.front();
          q.pop();
          ans.push_back(front->data);
     }

     return ans;
}





int main() {
    // Construct the binary tree
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    //   /
    //  8
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);

    
    vector<int> res = distanceK(root, root->left->left, 1);
    
    for(auto c : res) {
          cout << c << " ";
    }
    

     return 0;
}