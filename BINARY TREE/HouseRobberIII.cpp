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


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
     
     int robHelper(TreeNode* root, unordered_map<TreeNode*, int> &dp) {
          // Base Case
          if(!root) return 0;
          if(dp.find(root) != dp.end()) return dp[root];
     
          int robThisHouse = 0;
          int dontRobThisHouse = 0;
          
          // Include
          robThisHouse += root->val;
          if(root->left){
               robThisHouse += robHelper(root->left->left, dp) + robHelper(root->left->right, dp);
          }
          if(root->right){
               robThisHouse += robHelper(root->right->left, dp) + robHelper(root->right->right, dp);
          }
          // Exclude
          dontRobThisHouse = robHelper(root->right, dp) + robHelper(root->left, dp);
     
          return dp[root] = max(robThisHouse, dontRobThisHouse);
     }
     
     int rob(TreeNode* root) {
          unordered_map<TreeNode*, int> dp;
          return robHelper(root, dp);
     }
};