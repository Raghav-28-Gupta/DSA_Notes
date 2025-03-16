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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



class Solution{
public: 

     unordered_map<string, int> subTree_map;
     vector<TreeNode*> result;

     string serialize(TreeNode* root) {
          // Use '#' to denote null nodes in the serialization.
          if (!root) return "#";
          
          // Serialize the current subtree (post-order traversal: left, right, root)
          string subTree = to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
          
          // Count the occurrences of the subtree
          if(subTree_map[subTree] == 1) {
               result.push_back(root);
               
          }
          subTree_map[subTree]++;
          
          return subTree;
     }

     vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
          serialize(root);
          return result;
     }
};



void preOrder(TreeNode* root) {
     if (root == NULL) return;
     cout << root->val << " ";
     preOrder(root->left);
     preOrder(root->right);
}



void printDuplicateTrees(vector<TreeNode*> duplicates) {
     // Sort the roots lexicographically (based on their root node values)
     sort(duplicates.begin(), duplicates.end(), [](TreeNode* a, TreeNode* b) {
        return a->val < b->val;
     });

     // Print each tree's pre-order traversal
     for (TreeNode* root : duplicates) {
        preOrder(root);
        cout << endl;
     }
}




int main() {

    Solution solution;
    // Example 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->right->left = new TreeNode(2);
    root1->right->right = new TreeNode(4);
    root1->right->left->left = new TreeNode(4);

    vector<TreeNode*> duplicates1 = solution.findDuplicateSubtrees(root1);
    cout << "Example 1:" << endl;
    printDuplicateTrees(duplicates1);  // Output should be trees with roots 2 and 4.

    // Example 2
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(4);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(4);
    root2->left->right->left = new TreeNode(3);
    root2->left->right->right = new TreeNode(6);

    vector<TreeNode*> duplicates2 = solution.findDuplicateSubtrees(root2);
    cout << "Example 2:" << endl;
    printDuplicateTrees(duplicates2);  // Output should be trees with roots 3 and 6.

    return 0;
}