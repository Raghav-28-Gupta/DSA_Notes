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




// Binary Search Tree Iterator
// LEETCODE : 173


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};



class BSTIterator {
private: 
     stack<TreeNode*> nodeStack;
     stack<TreeNode*> nodeStackRev;


     void pushLeftNode(TreeNode* node) {
          while(node) {
               nodeStack.push(node);
               node = node ->left;
          }
     }

     void pushRightNode(TreeNode* node) {
          while(node) {
               nodeStackRev.push(node);
               node = node->right;
          }
     }
       

public:

     BSTIterator(TreeNode* root) {
          pushLeftNode(root);
     }

     BSTIterator_2(TreeNode* root) {
          pushRightNode(root);
     }

    
     int next() {
          TreeNode* topNode = nodeStack.top();
          nodeStack.pop();

          if (topNode->right) {
               pushLeftNode(topNode->right);
          }
        
          return topNode->val;
     }

     int before() {
          TreeNode* topNode = nodeStackRev.top();
          nodeStackRev.pop();

          if (topNode->left) {
               pushLeftNode(topNode->left);
          }
        
          return topNode->val;
     }

    
     bool hasNext() {
        return !nodeStack.empty();
        // Returns true if there is a next element in the in-order traversal
     }

     bool hasBefore() {
        return !nodeStackRev.empty();
     }
};




// LEETCODE : 653 (Two Sum)  -> Already Done With Vector

class solution {
public:

     bool findTarget(TreeNode* root, int k) {
          if (!root) return false;

          BSTIterator it(root);
          int i = it.next;
          int j = it.before;

          while(i < j) {
               int sum = i + j;

               if(sum == k) {
                    return true;
               }
               
               if(sum < k) {
                    i = it.next;
               }

               if(sum > k) {
                    j = it.before;
               }
          }

          return false;
     }
};









int main() {

    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);
    
    BSTIterator* iterator = new BSTIterator(root);
    // In-order: 3, 7, 9, 15, 20
    iterator->next();    // return 3
    iterator->next();    // return 7
    iterator->hasNext(); // return true
    iterator->next();    // return 9
    iterator->hasNext(); // return true
    iterator->next();    // return 15
    iterator->hasNext(); // return true
    iterator->next();    // return 20
    iterator->hasNext(); // return false

    return 0;
}
