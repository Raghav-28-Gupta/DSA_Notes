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


int solve(Node* root, int cameras) {
     if (!root) return 1;   // Null node is assumed to be covered

     int left = solve(root->left, cameras);
     int right = solve(root->right, cameras);
     
     if (left == 0 || right == 0) {     // Either node is not covered
          cameras ++;
          return 2;                     // Camera installed
     }
     
     if (left == 2 || right == 2) {
          return 1;                     // Covered
     }

     return 0;                          // NOT Covered
}



int minCameraCover(Node* root) {
     int cameras = 0;
     int rootState = solve(root, cameras);
     if (rootState == 0){
          cameras ++;
     }

     return cameras;
}




int main() {
    Node* root1 = new Node(0);
    root1->left = new Node(0);
    root1->left->left = new Node(0);
    root1->left->right = new Node(0);

    cout << "Minimum number of cameras for Example 1: " << minCameraCover(root1) << endl;

    // Example 2: [0,0,null,0,null,0,null,null,0]
    Node* root2 = new Node(0);
    root2->left = new Node(0);
    root2->left->left = new Node(0);
    root2->left->left->right = new Node(0);
    root2->left->left->right->right = new Node(0);

  
    cout << "Minimum number of cameras for Example 2: " << minCameraCover(root2) << endl;





    return 0;

}