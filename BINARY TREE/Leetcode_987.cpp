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






vector<vector<int>> verticalTraversal(Node* root) {    // LEETCODE : 987
     // Map to store nodes based on their column position.
     map<int, vector<pair<int,int>>> columnTable;

     // Queue to store the node, its row and column.
     queue<pair<Node*, pair<int,int>>> q;
     q.push({root, {0,0}});         // root is at row 0 and column 0

     while(!q.empty()) {
          auto p = q.front();
          q.pop();

          Node* node = p.first;
          int row = p.second.first;
          int column = p.second.second;
          
          // Store the node's value with its row in the appropriate column
          columnTable[column].emplace_back(row, node->data);
          
          // Move to the left and right children, updating row and column
          if(node->left) q.push({node->left, {row + 1, column - 1}});
          if(node->right) q.push({node->right, {row - 1, column + 1}});
     }

     vector<vector<int>> result;

     for(auto &col : columnTable) {
          // Sort the nodes in the current column by (row, value)
          sort(col.second.begin(), col.second.end());
          
          vector<int> sortedColumn;
          for(auto &p : col.second) {
               sortedColumn.push_back(p.second);
          }
          
          result.push_back(sortedColumn);
     }

     return result;
}



void printResult(const vector<vector<int>>& result) {
     for (const auto& col : result) {
          cout << "[";
          for (auto i = 0; i < col.size(); ++i) {
               cout << col[i];
               if (i < col.size() - 1) cout << ", ";
          }
          cout << "] ";
     }
     cout << endl;
}



// Example usage
int main() {
    // Example 1: root = [3,9,20,null,null,15,7]
    Node* root = new Node(3);
    root->left = new Node(9);
    root->right = new Node(20);
    root->right->left = new Node(15);
    root->right->right = new Node(7);

    vector<vector<int>> result = verticalTraversal(root);
    printResult(result);  // Output: [[9],[3,15],[20],[7]]

    return 0;
}