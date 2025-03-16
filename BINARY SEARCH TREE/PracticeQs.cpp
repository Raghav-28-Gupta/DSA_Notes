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



// BASIC STRUCTURE
void inorderTraversal(Node* root) {
     if(!root) return;

     inorderTraversal(root->left);
     cout << root->data << " ";
     inorderTraversal(root->right);
}



// Insertion
Node* insertBST(Node* root, int val) {
     if(!root) {
          return new Node(val);
     }

     if(val < root->data) {
          root->left = insertBST(root->left, val);
     }
     
     if(val > root->data) {
          root->right = insertBST(root->right, val);
     }

     return root;

}


// Searching
Node* searchBST(Node* root, int key) {
     if(!root) {
          return NULL;
     }

     if(root->data == key) {
          return root;
     }

     if (root->data > key) {
          return searchBST(root->left, key);
     }

     if(root->data < key) {
          return searchBST(root->right, key);
     }
}


// Min value
Node* minValueNode(Node* root) {
     Node* current = root;
     
     while(root->left != NULL) {
          current = current->left;
     }

     return current;
}


// Max Value
Node* maxValueNode(Node* root){
     Node* current = root;

     while(root->right != NULL) {
          current = current->right;
     }

     return current;
}



// Delete Node --> LEETCODE : 450
Node* deleteinBST(Node* root, int key) {
     if(!root) return NULL;

     if (key < root->data) {
          root->left = deleteinBST(root->left, key);
     }
     else if (key > root->data) {
          root->right = deleteinBST(root->right, key);
     }
     
     // Node found, handle deletion
     else {
          // Node has only right child or no child
          if(!root->left) {
               Node* temp = root->right;
               delete root;
               return temp;
          }

          // Node has only left child
          if(!root->right) {
               Node* temp = root->left;
               delete root;
               return temp;
          }

          // Node has two children: Get inorder successor (smallest in the right subtree)
          Node* successor = minValueNode(root->right);
          root->data = successor->data;     // Replace the value
          root->right = deleteinBST(root->right, successor->data);
     }

     return root;
}





// -------------------------------------------------------------------------------------------------------------






// LEETCODE : 653
void inorderSort(Node* root, vector<int>& ans) {
     if(!root) return;

     inorderSort(root->left, ans);
     ans.push_back(root->data);
     inorderSort(root->right, ans);
}

bool findTargetUtility(Node* root, vector<int> &ans, int target) {
     int n = ans.size();
     int start = 0;
     int end = n - 1;

     while(start < end) {
          int sum = ans[start] + ans[end];

          if(sum == target) {
               return true;
          }

          else if(sum < target) {
               start++;
          }

          else if(sum > target) {
               end--;
          }
     }

     return false;
}

bool findTarget(Node* root, int k) {
     vector<int> ans;
     inorderSort(root, ans);
     return findTargetUtility(root, ans, k);

}







// LEETCODE : 1038
void bstToGstHelper(Node* root, int& sum) {
     if(!root) return;
     
     // Traverse the right subtree first (greater values)
     bstToGstHelper(root->right, sum);
     
     // Update the current node's value with the accumulated sum
     sum += root->data;
     root->data += sum;

     // Traverse the left subtree (smaller values)
     bstToGstHelper(root->left, sum);
}

Node* bstToGst(Node* root) {
     int sum = 0;
     bstToGstHelper(root, sum);
     return root;
}







// LEETCODE : 783 (Minimum difference between Two Nodes)
void minDiffInBSTHelper(Node* root, int &prev, int &minDiff) {
     if(!root) return;
     
     // Traverse the Left Tree
     minDiffInBSTHelper(root->left, prev, minDiff);
     
     // Process the current Root
     if(prev != -1) {
          minDiff = min(minDiff, root->data - prev);
     }
     prev = root->data;
     
     // Traverse the Right Tree
     minDiffInBSTHelper(root->right, prev, minDiff);
}

int minDiffInBST(Node* root) {
     if(!root) return 0;
     int prev = -1;
     int minDiff = INT_MAX;
     minDiffInBSTHelper(root, prev, minDiff);
     return minDiff;
}







// LEETCODE : 230 (kth Smallest Element In A BST)
void kthSmallestHelper(Node* root, int k, int &count, int &result) {
     if(!root || count >= k) return;

     kthSmallestHelper(root->left, k, count, result);
     
     // Visit the current node
     count++;
     if(count == k) {
          result = root->data;
          return;
     }

     kthSmallestHelper(root->right, k, count, result);

}

int kthSmallest(Node* root, int k) {
     int result;
     int count = 0;
     kthSmallestHelper(root, k, count, result);
     return result;
}








// LEETCODE : 235 (Lowest Common Ancestor)
Node* lowestCommonAncestor_1(Node* root, Node* p, Node* q) {        // T.C -> O(N)
     // Base Cases
     if(root == NULL) return NULL;
     if(root->data == p->data) return p;
     if(root->data == q->data) return q;

     Node* leftAns = lowestCommonAncestor_1(root->left, p, q);
     Node* rightAns = lowestCommonAncestor_1(root->right, p, q);

     if(leftAns == NULL && rightAns == NULL) {
          return NULL;
     }

     else if(leftAns == NULL && rightAns != NULL) {
          return rightAns;
     }

     else if(rightAns == NULL && leftAns != NULL) {
          return leftAns;
     }

     else return root;
}


Node* lowestCommonAncestor_2(Node* root, Node* p, Node* q) {        // T.C -> O(logN)
     if(root == NULL) {
          return NULL;
     }        
     
     // If both p and q are smaller than root, LCA lies in the left subtree
     if (p->data < root->data && q->data < root->data) {
          Node* leftAns = lowestCommonAncestor_2(root->left, p, q);
          if(leftAns) {
               return leftAns;
          }
     }
     
     // If both p and q are larger than root, LCA lies in the right subtree
     else if (p->data > root->data && q->data > root->data) {
          Node* rightAns = lowestCommonAncestor_2(root->right, p, q);
          if(rightAns) {
               return rightAns;
          }
     }

     // Else, root is the lowest common ancestor
     else {
          return root;
     }

}








// LEETCODE : 108 (Convert Sorted Array To BST)
Node* buildBST(vector<int> &nums, int left, int right) {
     // Base Case : No elements in the range
     if(left > right) {
          return nullptr;
     }

     int mid = left + (right - left) / 2;
     Node* root = new Node(nums[mid]);

     root->left = buildBST(nums, 0, mid - 1);
     root->right = buildBST(nums, mid + 1, right);

     return root;

}

Node* sortedArrayToBST(vector<int> &nums) {
     return buildBST(nums, 0, nums.size() - 1);
}

void preOrderTraversal(Node* root) {
     if(!root) return;
     cout << root->data << " ";
     preOrderTraversal(root->left);
     preOrderTraversal(root->right);
}





// LEETCODE : 1382 (Balance a BST)
void INORder(Node* root, vector<int> &arr) {
     if(!root) return;
     INORder(root->left, arr);
     arr.push_back(root->data);
     INORder(root->right, arr);
}

Node* balanceBST(Node* root) {
     vector<int> arr;
     INORder(root, arr);
     return buildBST(arr, 0, arr.size() - 1);
}








// [IMPORTANT]

// LEETCODE : 1008 (BST From preOrder Traversal)
// (By changing range for each Node)

Node* constructBST(vector<int>& preorder, int &index, int lower, int upper) {
     // Base case: if index is out of range or value is outside bounds, return nullptr
     if(index >= preorder.size() || preorder[index] > upper || preorder[index] < lower) {
          return nullptr;
     }
     
     // Take the current value and move the index forward
     int value = preorder[index++];
     Node* TreeNode = new Node(value);

     TreeNode->left = constructBST(preorder, index, lower, value);
     TreeNode->right = constructBST(preorder, index, value, upper);

     return TreeNode;
}

Node* bstFromPreorder(vector<int>& preorder) {
     // Note: In this question, we are checking every element of preorder
     // if it satisfies the current range
     // otherwise NULL
     int index = 0;
     return constructBST(preorder, index, INT_MIN, INT_MAX);
}









// Binary Tree to DLL
// [IMPORTANT]
void convertToDLL(Node* root, Node* &head, Node* &prev) {
     if(root == nullptr) return;
     
     // Recursively convert the left subtree
     convertToDLL(root->left, head, prev);
     

     // Now process the current node
     if(prev == nullptr) {
          // This node is the leftmost node (head of DLL)
          head = root;
     }
     else {
          // Link the current node with the previous node
          prev->right = root;
          root->left = prev;
     }
     
     // Move prev to the current node
     prev = root;
     
     // Recursively convert the right subtree
     convertToDLL(root->right, head, prev);
}

Node* treeToDLL(Node* root) {
     Node *head = nullptr;
     Node *prev = nullptr;

     convertToDLL(root, head, prev);

     return head;
}

void printDLL(Node* head) {
     Node* curr = head;
     while(curr){
          cout << curr->data << " ";
          curr = curr->right;
     }
     cout << endl;
}

void printDLLReverse(Node *head) {
     if(!head) return;

     Node* curr = head;
     while(curr->right != nullptr) {
          curr = curr->right;
     }

     while(curr != nullptr){
          cout << curr->data << " ";
          curr = curr->left;
     }
     cout << endl;
}







// LEETCODE : 98 (Validate BST)
bool isValidBSTUtility(Node* root, long long minVal, long long maxVal) {
     // Base case: an empty tree is a valid BST
     if(root == nullptr) return true;
     
     // The current node's value must be strictly between minValue and maxValue
     if(root->data >= maxVal || root->data <= minVal) {
          return false;
     }

     // Recursively check the left and right subtrees with updated ranges
     return isValidBSTUtility(root->left, minVal, root->data) &&
            isValidBSTUtility(root->right, root->data, maxVal);
}

bool isValidBST(Node* root) {
     if(!root) return true;
     long long minVal = LONG_MIN;
     long long maxVal = LONG_MAX;
     // Use LONG_MIN and LONG_MAX to avoid overflow issues
     return isValidBSTUtility(root, minVal, maxVal);
}







// Predecessor and Successor                 [IMPORTANT]
void findPreSuc(Node* root, Node* &prev, Node* &succ, int key) {
     if(!root) return;


     // If the key is found in the BST
     if(root->data == key) {
          // Predecessor is the maximum of the left subtree
          if(root->left) prev = maxValueNode(root->left);

          // Successor is the minimum of the right subtree
          if(root->right) succ = minValueNode(root->right);

          return;
     }

     else if(key > root->data){
          prev = root;   // potential predecessor
          findPreSuc(root->right, prev, succ, key);
     }

     else {
          succ = root;   // potential successor
          findPreSuc(root->left, prev, succ, key);
     }
}








// Brothers From Different Roots
// Approach - 1   (Using Set)
void InOrderTraverse_1(Node* root, unordered_set<int> &values) {
     if(!root) return;
     InOrderTraverse_1(root->left, values);
     values.insert(root->data);
     InOrderTraverse_1(root->right, values);
}

int countPairsWithSum_1(Node* root, unordered_set<int> &values, int x) {
     if(!root) return 0;

     int compliment = x - root->data;
     int count = values.count(compliment) ? 1 : 0;
     
     count += countPairsWithSum_1(root->left, values, x);
     count += countPairsWithSum_1(root->right, values, x);

     return count;
}

int countPairs_1(Node* root1, Node* root2, int x) {
     unordered_set<int> values;

     // Collect all values from the first BST into the set
     InOrderTraverse_1(root1, values);
     
     // Count pairs by finding complements in the second BST
     return countPairsWithSum_1(root2, values, x);
}



// Approach - 2   (Using Array)
void InOrderTraverse_2(Node* root, vector<int> &arr) {
     if(!root) return;
     InOrderTraverse_2(root->left, arr);
     arr.push_back(root->data);
     InOrderTraverse_2(root->right, arr);
}

int countPairsWithSum_2 (vector<int> &arr1, vector<int> &arr2, int x) {
     int count = 0;

     int i = 0;                   // Pointer for arr1 (starting from the beginning)
     int j = arr2.size() - 1;     // Pointer for arr2 (starting from the end)

     while(i < arr1.size() && j >= 0) {
          int sum = arr1[i] + arr2[j];

          if(sum == x) {
               count ++;
               i++;
               j--;
          }

          else if(sum < x) {
               i++;
          }

          else {
               j--;
          }
     }

     return count;

}

int countPairs_2(Node* root1, Node* root2, int x) {
     vector<int> arr1, arr2;
     
     // Convert both BSTs to sorted arrays
     InOrderTraverse_2(root1, arr1);
     InOrderTraverse_2(root2, arr2);

     return countPairsWithSum_2(arr1, arr2, x);

}









// Check whether BST contains Dead End
void isDeadEndHelper(Node* root, unordered_set<int> &nodeSet, unordered_set<int> &leafSet) {
     if(!root) return;
     
     // Insert current node data into the node set
     nodeSet.insert(root->data);
     
     // Check if it is a leaf node
     if(!root->left && !root->right) {
          leafSet.insert(root->data);
     }
     
     isDeadEndHelper(root->left, nodeSet, leafSet);
     isDeadEndHelper(root->right, nodeSet, leafSet);
}

bool isDeadEnd(Node* root) {
     unordered_set<int> nodeSet;
     unordered_set<int> leafSet;

     // Insert initial range limits
     nodeSet.insert(0);

     // Filling Sets
     isDeadEndHelper(root, nodeSet, leafSet);

     // Check if any leaf node is a dead end
     for(auto leaf : leafSet) {
          if(nodeSet.count(leaf + 1) && nodeSet.count(leaf - 1)) {
               return true;
          }
     }

     return false;
}

















int main() {

     // Node* root2 = new Node(5);
     // root2->left = new Node(3);
     // root2->right = new Node(6);
     // root2->left->left = new Node(2);
     // root2->left->right = new Node(4);
     // root2->right->right = new Node(7);

     // Node* root = new Node(4);
     // root->left = new Node(1);
     // root->right = new Node(6);
     // root->left->left = new Node(0);
     // root->left->right = new Node(2);
     // root->left->right->right = new Node(3);
     // root->right->right = new Node(7);
     // root->right->left = new Node(5);
     // root->right->right->right = new Node(8);


     // Node* root1 = new Node(2);
     // root1->left = new Node(1);
     // root1->right = new Node(3);
     


     Node* root = nullptr;
     root = insertBST(root, 8);
     root = insertBST(root, 5);
     root = insertBST(root, 2);
     root = insertBST(root, 7);
     root = insertBST(root, 9);
     root = insertBST(root, 1);

     if (isDeadEnd(root)) {
          cout << "Yes" << endl;
     } else {
          cout << "No" << endl;
     }
     


     return 0;
}