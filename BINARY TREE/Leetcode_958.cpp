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


// Check Completeness of a Binary Tree


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
                    // "node: is valid
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

          return nullFound;
     }


     bool isCompleteTree(TreeNode* root) {
          bool ans = solve(root);
          return ans;
     }
};