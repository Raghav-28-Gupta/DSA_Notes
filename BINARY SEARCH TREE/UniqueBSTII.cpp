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
         
          vector<TreeNode*> generateTreesHelper(int start, int end) {
               // Base Case
               if(start > end) return {nullptr};
               
               vector<TreeNode*> trees;
               for(int i = start; i <= end; i++) {
                    auto leftSubtree = generateTreesHelper(start, i - 1);
                    auto rightSubtree = generateTreesHelper(i + 1, end);
                    for(auto left : leftSubtree){
                         for(auto right : rightSubtree) {
                              TreeNode* root = new TreeNode(i);
                              root->left = left;
                              root->right = right;
                              trees.push_back(root);
                         }
                    }
               }
               return trees;
          }
          
          
          vector<TreeNode*> generateTrees(int n) {
               if(n == 0) return {nullptr};
               return generateTreesHelper(1, n);
          }
     };