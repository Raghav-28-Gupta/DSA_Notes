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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};




// Recover Binary Search Tree



class Solution {
     TreeNode* FirstViolation = nullptr;
     TreeNode* SecondViolation = nullptr;
     TreeNode* Predecessor = nullptr;

public:

     void solve(TreeNode* curr) {
          if(!curr) return;
          
          solve(curr->left);
          
          // Store & Compute
          if(Predecessor && Predecessor->val > curr->val) {
               // Property is Violated
               if(!FirstViolation) {
                    FirstViolation = Predecessor;
               }
               SecondViolation = curr;
          }
          
          Predecessor = curr;

          solve(curr->right);

     }


     void recoverTree(TreeNode* root) {
          solve(root);
          if(FirstViolation && SecondViolation) {
               // Swap
               swap(FirstViolation->val, SecondViolation->val);
          }  
     }
};