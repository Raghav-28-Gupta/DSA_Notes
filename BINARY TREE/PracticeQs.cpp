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



Node* createTree() {
     cout << "Enter value for node: " << endl;
     int value;
     cin >> value;
          
     if (value == -1) {
          return NULL;
     }

     else {
          // Valid Value
          Node *root = new Node(value);
          // Inserting further values using recurison
          cout << "Adding left child for " << value << endl;
          root->left = createTree();

          cout << "Adding right child for " << value << endl;
          root->right = createTree();
               
          return root;
     }
}





// Traversals
void preOrderTraversal(Node* root) {               // N->current + L->left + R->right
     if (root == NULL) {
          return;
     }

     // NLR
     // N
     cout << root->data << " ";
     // L-> Left SubTree
     preOrderTraversal(root->left);
     // R-> Right subTree
     preOrderTraversal(root->right);
}


void inOrderTraversal(Node* root) {                // L->left + N->current + R->right
     if (root == NULL) {
          return;
     }
     
     // LNR
     // L
     inOrderTraversal(root->left);
     // N
     cout << root->data << " ";
     // R
     inOrderTraversal(root->right);
}


void postOrderTraversal(Node* root) {              // L->left + R->right + N->current 
     if (root == NULL) {
          return;
     }
    
     // LRN
     // L
     postOrderTraversal(root->left);
     // R
     postOrderTraversal(root->right);
     // N
     cout << root->data << " ";
}


void levelOrderTraversal(Node* root) {             // [IMPORTANT]
     if (root == NULL) {
          return;
     }

     queue<Node*> q;
     q.push(root);
     q.push(NULL);

     while(!q.empty()) {
          Node *front = q.front();
          q.pop();

          if (front == NULL) {
               cout << endl;
               // Push NULL for next levels
               if (!q.empty()) {
                    q.push(NULL);
               }
          }

          else {
               // First print the data
               cout << front->data << " ";

               // Enqueue left and right children
               if (front->left != NULL) {
                    q.push(front->left);
               }
               if (front->right != NULL) {
                    q.push(front->right);
               }
          }
     }

}


vector<vector<int>> zigzagLevelOrder(Node* root) { 
     vector<vector<int>> result;
     if(!root) return result;      // Empty result

     queue<Node*> q;
     q.push(root);
     bool leftToRight = true;

     while(!q.empty()) {
          int levelSize = q.size();
          vector<int> levelValues(levelSize);

          for(int i = 0; i < levelSize; i++) {
               Node* currentNode = q.front();
               q.pop();
               
               // Insert node's value into the correct position in the level array
               int index = leftToRight? i : (levelSize - i - 1);
               levelValues[index] = currentNode->data;

               if (currentNode->left) q.push(currentNode->left);
               if (currentNode->right) q.push(currentNode->right);
          }

          result.push_back(levelValues);
          leftToRight = !leftToRight;
     }

     return result;
}


vector<int> diagonalTraversal(Node* root) {
     vector<int> result;
     if(!root) return result;

     queue<Node*> q;
     q.push(root);
 
     while(!q.empty()) {
          Node* current = q.front();
          q.pop();
          
          // Process all nodes in the same diagonal
          while(current) {
               result.push_back(current->data);
               
               // If left child exists, push it to queue for the next diagonal
               if (current->left) {
                    q.push(current->left);
               }
               
               // Move to the right node (same diagonal)
               current = current->right;
          }
     }

     return result;

}


// Checkout LEETCODE : 987 --> Vertical Order Traversal

// Checkout LEETCODE : 94  --> Morris Traversal -->  T.C : O(N) , S.C : O(1)












// LEETCODE : 104
int maxDepth(Node* root) {
     // Base case
     if (root == NULL) {
          return 0;
     }

     int leftSubTree = maxDepth(root->left);
     int rightSubTree = maxDepth(root->right);
     int maxHeight = max(leftSubTree, rightSubTree);

     int totalHeight = maxHeight + 1;

     return totalHeight;
     
}

// LEETCODE : 543
int diameterOfBinaryTree(Node* root) {
     if (root == NULL) {
          return 0;
     }

     int option1 = diameterOfBinaryTree(root->left);
     int option2 = diameterOfBinaryTree(root->right);
     int option3 = maxDepth(root->left) + maxDepth(root->right);
     
     int maxDiameter = max(option1, max(option2, option3));

     return maxDiameter;
}



// Optimal Way
int height(Node* root, int diameter) {
     if (!root) return 0;

     int leftSubTree = height(root->left, diameter);
     int rightSubTree = height(root->right, diameter);
     int currDiameter = leftSubTree + rightSubTree;

     diameter = max(diameter, currDiameter);

     return max(leftSubTree, rightSubTree) + 1;

}

int diameterOfBinaryTree_2(Node* root) {
     if (!root) return 0;

     int diameter = 0;
     int maxDepth = height(root, diameter);

     return diameter;
}










// LEETCODE : 110 (Balanced Binary Tree)
int getHeight(Node* root) {
     if (root == NULL) {
          return 0;
     }

     int leftSubTree = getHeight(root->left);
     int rightSubTree = getHeight(root->right);

     int actualHeight = max(leftSubTree,rightSubTree) + 1;
     
     return actualHeight;
}

bool isBalanced(Node* root) {                        // T.C -> O(N^2)
     // Base case
     if (root == NULL) {
          // Null child will always be balanced
          return true;
     }

     int leftHeight = getHeight(root->left);
     int rightHeight = getHeight(root->right);
     bool checkBalance = (abs(leftHeight - rightHeight) <= 1);

     // Check further through RECURSION
     bool leftCheck = isBalanced(root->left);
     bool rightCheck = isBalanced(root->right);
     
     // Fullfil all 3 conditions
     if (checkBalance && leftCheck && rightCheck) {
          return true;
     }
     else {
          return false;
     }
}


// Optimal Way
int getHeight_2(Node* root, bool &ans) {             // T.C -> O(N)
     // Base Case
     if(!root) return 0;

     int lh = getHeight_2(root->left, ans);
     int rh = getHeight_2(root->right, ans);

     if (ans && abs(lh - rh) > 1) {
          ans = false;
     }

     return max(lh, rh) + 1;

}

bool isBalanced_2(Node* root) {
     // Base case
     if (!root) return true;
     bool ans = true;
     int res = getHeight_2(root, ans);

     return ans;
}










// LEETCODE : 236         (Lowest Common Ancestor)
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
     // Base Cases
     if (root == NULL) {
          return NULL;
     }

     if (root->data == p->data) {
          return p;
     }

     if (root->data == q->data) {
          return q;
     }


     Node* leftAns = lowestCommonAncestor(root->left, p, q);
     Node* rightAns = lowestCommonAncestor(root->right, p, q);


     // Fulfilling Condiitons
     if (leftAns == NULL && rightAns == NULL) {
          return NULL;
     }

     else if (leftAns == NULL && rightAns != NULL) {
          return rightAns;
     }

     else if (leftAns != NULL && rightAns == NULL) {
          return leftAns;
     }

     else if (leftAns != NULL && rightAns != NULL) {
          // Ans -> root node
          return root;
     }

}








// LEETCODE : 112         (Path Sum)
int pathSolver(Node* root, int targetSum, int sum) {
     // Reached at the end
     if (root == NULL) {
          return false;
     }

     // NOT NULL
     sum += root->data;
     if (root->left == NULL && root->right == NULL) {
          // Check for LEAF Node
          if (sum == targetSum) {
               return true;
          }
          else return false;
     }

     bool leftAns = pathSolver(root->left, targetSum, sum);
     bool rightAns = pathSolver(root->right, targetSum, sum);

     return leftAns || rightAns;
}

bool hasPathSum(Node* root, int targetSum) {
     int sum = 0;
     return pathSolver(root, targetSum, sum);
}



// LEETCODE : 113         (Path Sum II)
void pathSumSolver(Node* root, int targetSum, int sum, vector<int>& tempAns, vector<vector<int>>& result){
     // Reached at the end
     if (root == NULL) {
          return;
     }
     
     // NOT NULL
     sum += root->data;
     tempAns.push_back(root->data);

     if (root->left == NULL && root->right == NULL) {
          if (sum == targetSum) {
               result.push_back(tempAns);
          }
          // Backtrack
          tempAns.pop_back();
          return;
     } 
     
     
     pathSumSolver(root->left, targetSum, sum, tempAns, result);
     pathSumSolver(root->right, targetSum, sum, tempAns, result);

     // Backtrack
     tempAns.pop_back();
}

vector<vector<int>> pathSum(Node* root, int targetSum) {
     vector<int> tempAns;
     vector<vector<int>> result;
     int sum = 0;
     pathSumSolver(root, targetSum, sum, tempAns, result);

     return result;
}



// LEETCODE : 437         (Path Sum III)
int pathSumSolverIII(Node* root, int targetSum, long long currSum) {
     if (!root) return 0;
     
     currSum += root->data;
     int count = 0;

     if(currSum == targetSum) {
          count++;
     }

     count += pathSumSolverIII(root->left, targetSum, currSum);
     count += pathSumSolverIII(root->right, targetSum, currSum);

     return count;
}

int pathSumIII(Node* root, int targetSum) {
     // Empty tree
     if(!root) return 0;

     int totalPaths = pathSumSolverIII(root, targetSum, 0);

     // Recursively check the left and right subtrees
     totalPaths += pathSumIII(root->left, targetSum);
     totalPaths += pathSumIII(root->right, targetSum);

     return totalPaths;
}





int maxPathSum(Node* root, int sum = 0) {
     // Base case : if node is NULL -> return 0
     if (root == NULL) {
          return 0;
     }
     
     // Add current node's data to the path sum
     sum = sum + root->data;
     
     // If it's a leaf node, return the current path sum
     if (root->left == NULL && root->right == NULL) {
          return sum;
     }
     
     // Recursively calculate the maximum sum for left and right subtrees
     int leftSum = maxPathSum(root->left, sum);
     int rightSum = maxPathSum(root->right, sum);

     return max(leftSum, rightSum);
}













// [IMPORTANT]

// LEETCODE : 105 (Binary Tree from Inorder & PreOrder)
void createMapping (unordered_map<int,int> &valMap, vector<int>& inorder) {
     for (int i = 0; i < inorder.size(); i++) {
          valMap[inorder[i]] = i;
     }
}


int getIndexInorder(int element, vector<int>& inorder, int inorderStart, int inorderEnd) {
     int n = inorder.size();
     for (int i = inorderStart; i < inorderEnd; i++) {
          if (inorder[i] == element) {
               return i;
          }
     }

     // Will never hit this condiiton
     return -1;
}


Node* contructTree_1(vector<int>& preorder, vector<int>& inorder, unordered_map<int,int> &valMap, int &preOrderIndex, int inorderStart, int inorderEnd, int size) { 
     // Base cases
     if (preOrderIndex >= size) {
          return NULL;
     }
     if (inorderStart > inorderEnd) {  // For Leaf Node
          return NULL;
     }
     
     // Get element from preorder & create root node
     int element = preorder[preOrderIndex];
     preOrderIndex++;
     Node* root = new Node(element);
     


     // find for element in inorder and calling for Left & Right 
     int ElementInorderIndex = valMap[element];
     // OR
     // int ElementInorderIndex = getIndexInorder(element, inorder, inorderStart, inorderEnd);



     root->left = contructTree_1(preorder, inorder, valMap, preOrderIndex, inorderStart, ElementInorderIndex-1, size);
     root->right = contructTree_1(preorder, inorder, valMap, preOrderIndex, ElementInorderIndex + 1, inorderEnd, size);

     return root;

     // NOTE : Here &preOrderIndex is passed by reference to make sure
     // that every element is processed only 1 time in these recursive calls
}


Node* buildTree_1(vector<int>& preorder, vector<int>& inorder) {
     int preOrderIndex = 0;
     int inorderStart = 0;
     int inorderEnd = inorder.size();
     int size = inorder.size();
     unordered_map<int,int> valMap;
     createMapping(valMap, inorder);

     Node* root = contructTree_1(preorder, inorder, valMap, preOrderIndex, inorderStart, inorderEnd, size);
     return root;
}


void printTree(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}











// LEETCODE : 105 (Binary Tree from Inorder & PostOrder)

Node* contructTree_2(vector<int>& postorder, vector<int>& inorder, unordered_map<int,int> &valMap, int &postOrderIndex, int inorderStart, int inorderEnd){
     // Base case
     if (postOrderIndex < 0) {
          return NULL;
     }
     if (inorderStart > inorderEnd) {    // Leaf Node
          return NULL;
     }

     // Get element from postorder & create root node
     int element = postorder[postOrderIndex];
     postOrderIndex--;
     Node* root = new Node(element);
     int ElementInorderIndex = valMap[element];

     // right call
     root->right = contructTree_2(postorder, inorder, valMap, postOrderIndex, ElementInorderIndex + 1, inorderEnd);
     // left call
     root->left =  contructTree_2(postorder, inorder, valMap, postOrderIndex, inorderStart, ElementInorderIndex - 1);


     return root;
}


Node* buildTree_2(vector<int>& postorder, vector<int>& inorder) {
     int postOrderIndex = postorder.size() - 1;
     int inorderStart = 0;
     int inorderEnd = inorder.size() - 1;
     int size = inorder.size();
     unordered_map<int,int> valMapIndex;
     createMapping(valMapIndex, inorder);

     Node* root = contructTree_2(postorder, inorder, valMapIndex, postOrderIndex, inorderStart, inorderEnd);

     return root;
}


void printTree_Post(Node* root) {
    if (!root) return;
    printTree_Post(root->left);
    printTree_Post(root->right);
    cout << root->data << " ";
}








// Tree Boundary Traversal
    
void leftBoundary(Node* root, vector<int>& ans) {
     // Base case
     if (root == NULL) {
          return;
     }
     if (root->left == NULL && root->right == NULL) {
          // Leaf Node
          return;
     }

     ans.push_back(root->data);

     if (root->left != NULL) {
          leftBoundary(root->left, ans);
     }
     else {
          leftBoundary(root->right, ans);
     }
}  


void LeafBoundary(Node* root, vector<int>& ans) {
     if (root == NULL) {
          return;
     }
     
     if (root->left == NULL && root->right == NULL) {
          ans.push_back(root->data);
     }

     LeafBoundary(root->left ,ans);
     LeafBoundary(root->right, ans);
}


void rightBoundary(Node* root, vector<int>& ans) {
     // Base case
     if (root == NULL) {
          return;
     }
     if (root->left == NULL && root->right == NULL) {
          // Leaf Node
          return;
     }

     if (root->right != NULL) {
          leftBoundary(root->right, ans);
     }
     else {
          leftBoundary(root->left, ans);
     }

     // Store in reverse order 
     ans.push_back(root->data);

}  


vector<int> boundary(Node* root) {
     vector<int> ans;

     if (root == NULL) {
          return ans;
     }  
     
     // First store the root value
     ans.push_back(root->data);
     
     // leftSubTree : left Boundary
     leftBoundary(root->left, ans);
     // leftSubTree : left Leaf
     LeafBoundary(root->left, ans);
     // rightSubTree : right Leaf
     LeafBoundary(root->right, ans);
     // rightSubTree : right Boundary
     rightBoundary(root->right, ans);

     return ans;
}









// Left View

// Using Level Order Traversal
vector<int> leftView_1(Node* root) {
     vector<int> result;
     if (root == NULL) return result;    // empty vector

     queue<Node*> q;
     q.push(root);
     
     while(!q.empty()) {
          int size = q.size();
          
          for (int i = 0; i < size; i++) {
               Node* frontNode = q.front();
               q.pop();
               
               // If it's the first node at this level, add it to the result
               if (i == 0){ 
                    result.push_back(frontNode->data);
               }
               
               // Add left child first, then right child to the queue
               if (frontNode->left) q.push(root->left);
               if (frontNode->right) q.push(root->right);
          }

     }
     
     return result;
}


// Using TRICK
void leftViewSolver(Node* root, int level, vector<int>& ans) {
     if (root == NULL) return;
    
     // IMPORTANT
     if (level == ans.size()) {
          ans.push_back(root->data);
     }

     leftViewSolver(root->left, level + 1, ans);
     leftViewSolver(root->right, level + 1, ans);
}

vector<int> leftView_2(Node* root) {
     vector<int> result;
     int level = 0;
     leftViewSolver(root, level, result);
     return result;
} 








// Top View
vector<int> topView (Node* root) {
     // Using Level Order Traversal
     
     queue<pair<Node*,int>> q;
     q.push(make_pair(root,0));
     unordered_map<int,Node*> distMap;

     int minDist = INT_MAX;
     int maxDist = INT_MIN;
     
     // Rule -> left(-1) , right(+1) in distance
     while(!q.empty()) {
          pair<Node*, int> frontPair = q.front();
          q.pop();

          Node* frontNode = frontPair.first;
          int hd = frontPair.second;
          
          // For later iteration
          minDist = min(minDist, hd);
          maxDist = max(maxDist, hd);

          if (distMap.find(hd) == distMap.end()) {
               distMap[hd] = frontNode;
          }

          if (frontNode->left) q.push(make_pair(root->left, hd-1));
          if (frontNode->right) q.push(make_pair(root->right, hd+1));
     }

     vector<int> ans;
     for (int i = minDist; i < maxDist; i++) {
          Node *temp = distMap[i];
          ans.push_back(temp->data);
     }
    
     return ans;

}

// Bottom View
vector<int> bottomView (Node* root) {
     // Using Level Order Traversal

     queue<pair<Node*,int>> q;
     q.push(make_pair(root, 0));
     unordered_map<int,Node*> distMap;

     int minDist = INT_MAX;
     int maxDist = INT_MIN;

     // Rule -> left(-1) , right(+1) in distance
     while(!q.empty()) {
          pair<Node*, int> frontPair = q.front();
          q.pop();

          Node* frontNode = frontPair.first;
          int hd = frontPair.second;

          // For later iteration
          maxDist = max(maxDist, hd);
          minDist = min(minDist, hd);
          
          // the last node encountered is the one 
          // visible when viewed from below.
          // So no checking required
          distMap[hd] = frontNode;



          if (frontNode->left) q.push(make_pair(root->left, hd-1));
          if (frontNode->right) q.push(make_pair(root->right, hd+1));
     }
    
     vector<int> ans;
     for (int i = minDist; i < maxDist; i++) {
          Node *temp = distMap[i];
          ans.push_back(temp->data);
     }

     return ans;
}







// LEETCODE : 783 (Minimum Distance Between Bst Nodes)
void minDiffInBST_Solver(Node* root, Node* &prev, int &minDiff) {
     // Using Inorder Traversal
     if (!root) return;

     minDiffInBST_Solver(root->left, prev, minDiff);

     if (prev) {
          minDiff = min(minDiff, root->data - prev->data);
     }
     // Update prev
     prev = root;

     minDiffInBST_Solver(root->right, prev, minDiff);
}

int minDiffInBST(Node* root) {
     Node* prev = nullptr;
     int minDiff = INT_MAX;
     
     minDiffInBST_Solver(root, prev, minDiff);

     return minDiff;

}








// [IMPORTANT]
// LEETCODE : 783 (Maximum of Width Of Binary Tree) 
int widthOfBinaryTree(Node* root) {

     // Using Level Order Traversal

     if (!root) return 0;

     // Queue for level-order traversal: (node, index in complete binary tree)
     queue<pair<Node*,unsigned long long>> q;
     q.push({root, 1});
     int maxWidth = 0;

     while(!q.empty()) {
          unsigned long long size = q.size();
          unsigned long long leftMostIndex = q.front().second;
          unsigned long long rightMostIndex = q.back().second;
          unsigned long long currentLevelWidth = rightMostIndex - leftMostIndex + 1;
          
          maxWidth = max(maxWidth, int(currentLevelWidth));

          for(int i = 0; i < size; i++) {
               auto front = q.front();
               q.pop();

               auto node = front.first;
               auto CurrIndex = front.second;

               if (node->left) q.push({node->left, 2 * CurrIndex});
               if (node->right) q.push({node->right, 2 * CurrIndex + 1});
          }
     }

     return maxWidth;

}






// [IMPORTANT]
// Checkout -> LEETCODE : 863 (All Nodes Distance in K in Binary Tree)







// LEETCODE : 222 (Count Complete Tree Nodes) 
int left_Height(Node* root) {                // T.C -> O(logN)
     int count = 0;
     while(root) {
          count++;
          root = root->left;
     }
     
     return count;
}

int right_Height(Node* root) {               // T.C -> O(logN)
     int count = 0;
     while(root) {
          count++;
          root = root->right;
     }
     
     return count;
}


int countNodes(Node* root) {                 // Worst L.C -> O( log^2N )
     if (!root) return 0;   
     
     int lh = left_Height(root);
     int rh = right_Height(root);
     
     if (lh == rh) return (1 << lh) - 1;   // 2^lh - 1

     // if -> lh != rh
     // ans = 1 + (...) + (...)

     int lans = countNodes(root->left);
     int rans = countNodes(root->right);

     return 1 + lans + rans;
}








// Transform to Sum Tree
int toSumTree(Node* root) {
     // If node is NULL
     if (!root) return 0;

     // Recursively calculate the sum of the left and right subtrees
     int leftSum = toSumTree(root->left);
     int rightSum = toSumTree(root->right);
     
     int oldVal = root->data;

     root->data = leftSum + rightSum;

     return oldVal + root->data;
}

void printTreeSum(Node* root) {
     if (root == NULL) return;
     printTreeSum(root->left);
     cout << root->data << " ";
     printTreeSum(root->right);
}








// LEETCODE : 94 (Flatten Binary Tree-to-Linked List) 
void flatten(Node* root) {
     if(!root) return;

     flatten(root->left);

     if(root->left) {
          // Store the original right subtree
          Node* rightSubTree = root->right;
          // Move the left subtree to the right
          root->right = root->left;
          root->left = NULL;
          
          // Move to the end of the new right subtree (which was the left subtree)
          Node* current = root->right;
          while(current->right) {
               current = current->right;
          }
          
          // Attach the original right subtree
          current->right = rightSubTree;
     }
     
     flatten(root->right);
}

void printLinkedList(Node* root) {
     while (root) {
        cout << root->data;
        if (root->right) cout << " -> ";
        root = root->right;
     }
     cout << endl;
}









// Sum of nodes on the longest path from root to leaf node
void findLongestPath_1 (Node* root, int currentSum, int currentLength, int &maxSum, int &maxLength) {
     // Base case
     if(!root) return;

     // Update the current path length and sum
     currentLength++;
     currentSum += root->data;

     // If this node is a leaf node
     if(!root->left && !root->right) {
          // Check if this path is the longest or if it has a larger sum for the same length
          if (currentSum > maxSum) {
               maxLength = currentLength;
               maxSum = currentSum;
          }
          
          else {
               if (currentLength == maxLength) {
                    maxSum = max(currentSum, maxSum);
               }
          }

     }

     findLongestPath_1(root->left, currentSum, currentLength, maxSum, maxLength);
     findLongestPath_1(root->right, currentSum, currentLength, maxSum, maxLength);

}

int sumOfLongRootToLeafPath_1(Node* root) {
     if (!root) return 0;

     int maxSum = 0;
     int maxLength = 0;

     findLongestPath_1(root, 0, 0, maxSum, maxLength);

     return maxSum;
}

// Alternative
pair<int, int> findLongestPath_2(Node* root) {
     if (!root) return {0, 0};

     pair<int, int> lh = findLongestPath_2(root->left);
     pair<int, int> rh = findLongestPath_2(root->right);

     int sum = root->data;
     if (lh.first == rh.first) {
          sum += lh.second > rh.second ? lh.second : rh.second;
     }

     else if (lh .first > rh.first) {
          sum += lh.second;
     }
     
     else {
          sum += rh.second;
     }

     return {max(lh.first, rh.first) + 1, sum};
}

int sumOfLongRootToLeafPath_2(Node* root) {
     pair<int, int> h = findLongestPath_2(root);
     return h.second;
}









// Maximum sum of Non-adjacent nodes
int getMaxSum(Node* root, unordered_map<Node*,int> &memo) {
     if(!root) return 0;

     // If the result is already computed, return it (Memoization)
     if (memo.find(root) != memo.end()) {
          return memo[root];
     }
     
     // Sum when we include the current node
     int include = root->data;
     if(root->left) {
          include += getMaxSum(root->left->left, memo) + getMaxSum(root->left->right, memo);
     }
     
     if(root->right) {
          include += getMaxSum(root->right->right, memo) + getMaxSum(root->right->left, memo);
     }
     

     int exclude = getMaxSum(root->left, memo) + getMaxSum(root->right, memo);

     memo[root] = max(include, exclude);

     return memo[root];
}

int maxSumNonAdjacent(Node* root) {
     if(!root) return 0;

     unordered_map<Node*,int> memo;

     return getMaxSum(root, memo);

}










// Burning Tree    ---->     [IMPORTANT]
void mapParents(Node* root, int target, unordered_map<Node*,Node*> &parentMap, Node* &targetNode) {
     queue<Node*> q;
     q.push(root);

     while(!q.empty()) {
          Node* node = q.front();
          q.pop();

          if(node->data == target) {
               targetNode = node;
          }

          if(node->left) {
               parentMap[node->left] = node;
               q.push(node->left);
          }

          if(node->right) {
               parentMap[node->right] = node;
               q.push(node->right);
          }
     }
}


int minTimeToBurnTreeUtil(Node* root, unordered_map<Node*,Node*> &parentMapNode, Node* &targetNode) {
     unordered_set<Node*> visited;
     queue<Node*> q;
     q.push(targetNode);
     visited.insert(targetNode);

     int Time = 0;

     while(!q.empty()) {
          int size = q.size();
          bool fireSpread = false;

          for(int i = 0; i < size; i++) {
               Node* node = q.front();
               q.pop();
               
               // Burn the left child
               if(node->left && visited.find(node->left) == visited.end()) {
                    fireSpread = true;
                    visited.insert(node->left);
                    q.push(node->left);
               }
               
               // Burn the right child
               if(node->right && visited.find(node->right) == visited.end()) {
                    fireSpread = true;
                    visited.insert(node->right);
                    q.push(node->right);
               }

               // Burn the parent
               if(parentMapNode[node] && visited.find(parentMapNode[node]) == visited.end()) {
                    fireSpread = true;
                    visited.insert(parentMapNode[node]);
                    q.push(parentMapNode[node]);
               }
          }
          
          // If fire has spread in this second, increment the time
          if(fireSpread) Time++;
     }

     return Time;
}


int minTimeToBurnTree(Node* root, int target) {
     if(!root) return 0;
     
     // Parent map to store the parent of each node
     unordered_map<Node*,Node*> parentMap;
     Node* targetNode = nullptr;
     
     // Step 1: Map the parent pointers and find the target node
     mapParents(root, target, parentMap, targetNode);

     return minTimeToBurnTreeUtil(root, parentMap, targetNode);
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

     // Node* root = new Node(1);
     // root->left = new Node(2);
     // root->right = new Node(3);
     // root->left->left = new Node(4);
     // root->left->right = new Node(5);
     // root->right->left = new Node(6);
     // root->right->right = new Node(7);
     // root->left->left->left = new Node(8);


     Node* root = new Node(1);
     root->left = new Node(2);
     root->right = new Node(3);
     root->left->left = new Node(4);
     root->left->right = new Node(5);
     root->right->right = new Node(6);
     root->left->right->left = new Node(7);
     root->left->right->right = new Node(8);
     root->right->right->right = new Node(9);
     root->right->right->right->right = new Node(10);


     cout << "Minimum time to burn the tree: " << minTimeToBurnTree(root, 8) << " seconds" << endl;

     return 0;
}


     
