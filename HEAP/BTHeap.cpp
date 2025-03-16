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

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Check if Binary Tree is Heap


class Solution {
public:

     solve(TreeNode* root) {
          queue<TreeNode*> q;
          q.push(root);
          bool nullFound = false;

          while(!q.empty()){
               auto node = q.front();
               q.pop();
               
               if(node == NULL) {
                    nullFound = true;
               }
               
               else {
                    // "node" is valid
                    if(nullFound == true){
                         // not a cbt
                         return false;
                    }

                    else {
                         // Continue Processing
                         q.push(node->left);
                         q.push(node->right);
                    }
               }
          }

          return true;
     }


     bool isCompleteTree(TreeNode* root) {
          bool ans = solve(root);
          return ans;
     }

     bool checkMaxProperty(TreeNode* root) {
          if(!root) {
               return true;
          }
          
          if(!root->left && !root->right){
               return true;
          }

          bool leftAns = checkMaxProperty(root->left);
          bool rightAns = checkMaxProperty(root->right);
          
          bool option1 = true;
          if(root->left && root->val < root->left->val) {
               option1 = false;
          }
          
          bool option2 = true;
          if(root->right && root->val < root->right->val) {
               option2 = false;
          }

          bool currAns = option1 && option2;

          return currAns && leftAns && rightAns;
     }
     

     bool isHeap(TreeNode* root) {
          bool Complete = isCompleteTree(root);
          bool heapProperty = checkMaxProperty(root);

          return Complete && heapProperty;
     }

};


// Approach - 2
class altSolution{
public:
     
     int nodeCount(TreeNode* root) {
          if(!root) return 0;
          int leftCount = nodeCount(root->left);
          int rightCount = nodeCount(root->right);
          return 1 + leftCount + rightCount;
     }

     bool isCBT(TreeNode* root, int i, int &n) {
          if(!root) return true;
          elif(i > n) return false;
          return isCBT(root->left, 2*i, n) && isCBT(root->right, 2*i + 1, n);
     }

     bool isMaxProp(TreeNode* root) {
          if(!root) return true;

          if(!root->left && !root->right) {
               return true;
          }

          bool leftAns = isMaxProp(root->left);
          bool rightAns = isMaxProp(root->right);

          bool option1 = false;
          if(root->left && root->data > root->left->data) {
               option1 = true;
          }
          bool option2 = false;
          if(root->right && root->data > root->right->data) {
               option2 = true;
          }

          bool currAns = option1 && option2;

          return currAns && leftAns && rightAns;

     }
     
     bool isHeap_2(TreeNode* root){
          int n = nodeCount(root);
          bool Completeness = isCBT(root, n, 1);
          bool heapProp = isMaxProp(root);

          return Completeness && heapProp;
     }
};