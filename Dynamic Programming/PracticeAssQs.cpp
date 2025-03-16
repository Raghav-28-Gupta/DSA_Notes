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


// LEETCODE : 279 (Perfect Squares)
int solveLT279UsingRec(int n){
     // Base Case
     if (n == 0) return 0;

     int ans = INT_MAX;
     int i = 1;
     int j = sqrt(n);
     while(i <= j) {
          int perfSqr = i * i;
          int noOfperfSqrs = 1 + solveLT279UsingRec(n - perfSqr);
          ans = min(ans, noOfperfSqrs);
          i++;
     }

     return ans;
}

int solveLT279UsingMemo(int n, vector<int> &dp){
     // Base Case
     if (n == 0) return 0;
     if(dp[n] != -1) return dp[n];

     int ans = INT_MAX;
     int i = 1;
     int j = sqrt(n);
     while(i <= j) {
          int perfSqr = i * i;
          int noOfperfSqrs = 1 + solveLT279UsingMemo(n - perfSqr, dp);
          ans = min(ans, noOfperfSqrs);
          i++;
     }

     return dp[n] = ans;
}

int solveLT279UsingTabulation(int n){
     vector<int> dp(n + 1, 0);

     // Analysing Base case
     dp[0] = 0;
     
     for(int i = 1; i <= n; i++) {
          int ans = INT_MAX;
          int start = 1;
          int end = sqrt(i);

          while(start <= end) {
               int perfSqr = start * start;
               int noOfperfSqrs = 1 + dp[i - perfSqr];
               ans = min(ans, noOfperfSqrs);
               start++;
          }
          dp[i] = ans;
     }
     
     return dp[n];
}

int numSquares(int n) {
     // return solveLT279UsingRec(n);
     // vector<int> dp(n + 1, -1);
     return solveLT279UsingTabulation(n);
}





// LEETCODE : 983 (Minimum Cost For Tickets)
int solveLT983UsingRec(vector<int>& days, vector<int>& costs, int i){
     // Base Case
     if(i >= days.size()) return 0;

     // 1 Day-Pass
     int option1 = costs[0] + solveLT983UsingRec(days, costs, i + 1);

     // 7 Day-Pass
     int EndDay_7 = i;
     while(EndDay_7 < days.size() && days[EndDay_7] < days[i] + 7) {
          EndDay_7++;
     }
     int option2 = costs[1] + solveLT983UsingRec(days, costs, EndDay_7++);

     // 30 Day-Pass
     int EndDay_30 = i;
     while(EndDay_30 < days.size() && days[EndDay_30] < days[i] + 30) {
          EndDay_30++;
     }
     int option3 = costs[2] + solveLT983UsingRec(days, costs, EndDay_30++);
     
     return min(option1, min(option2, option3));
}

int solveLT983UsingMemo(vector<int>& days, vector<int>& costs, int i, vector<int> &dp){
     // Base Case
     if(i >= days.size()) return 0;
     if(dp[i] != -1) return dp[i];

     // 1 Day-Pass
     int option1 = costs[0] + solveLT983UsingMemo(days, costs, i + 1, dp);

     // 7 Day-Pass
     int EndDay_7 = i;
     while(EndDay_7 < days.size() && days[EndDay_7] < days[i] + 7) {
          EndDay_7++;
     }
     int option2 = costs[1] + solveLT983UsingMemo(days, costs, EndDay_7++, dp);

     // 30 Day-Pass
     int EndDay_30 = i;
     while(EndDay_30 < days.size() && days[EndDay_30] < days[i] + 30) {
          EndDay_30++;
     }
     int option3 = costs[2] + solveLT983UsingMemo(days, costs, EndDay_30++, dp);
     
     return dp[i] = min(option1, min(option2, option3));
}

int solveLT983UsingTabulation(vector<int>& days, vector<int>& costs) {
     int n = days.size();
     vector<int> dp(n + 1, -1);
     
     // Analyzing Base Case
     dp[n] = 0;

     for(int i = n - 1; i >= 0; i--) {
          // 1 Day-Pass
          int option1 = costs[0] + dp[i + 1];

          // 7 Day-Pass
          int EndDay_7 = i;
          while(EndDay_7 < days.size() && days[EndDay_7] < days[i] + 7) {
               EndDay_7++;
          }
          int option2 = costs[1] + dp[EndDay_7];

          // 30 Day-Pass
          int EndDay_30 = i;
          while(EndDay_30 < days.size() && days[EndDay_30] < days[i] + 30) {
               EndDay_30++;
          }
          int option3 = costs[2] + dp[EndDay_30];
          
          dp[i] = min(option1, min(option2, option3));
     }
          
     return dp[0];
}

int mincostTickets(vector<int>& days, vector<int>& costs) {
     // int n = days.size();
     // vector<int> dp(n + 1, -1);
     // return solveUsingMemo(days, costs, 0, dp);
     return solveLT983UsingTabulation(days, costs);
}





// LEETCODE : 712 (Minimum ASCII Delete Sum for Two Strings)
int solveLT712UsingRec(string &s1, string &s2, int i, int j) {
     // Base Case
     if(i == s1.length() || j == s2.length()) {
          int res = 0;
          for(int m = i; m < s1.length(); m++) res += s1[m];
          for(int n = j; n < s2.length(); n++) res += s2[n];
          return res;
     }
     
     int ans = INT_MAX;
     if(s1[i] == s2[j]) ans = solveLT712UsingRec(s1, s2, i + 1, j + 1);
     else {
          int deleteS1 = s1[i] + solveLT712UsingRec(s1, s2, i + 1, j);
          int deleteS2 = s2[j] + solveLT712UsingRec(s1, s2, i, j + 1);
          ans = min(deleteS1, deleteS2);
     }
     
     return ans;
}

int solveLT712UsingMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
     // Base Case
     if(i == s1.length() || j == s2.length()) {
          int res = 0;
          for(int m = i; m < s1.length(); m++) res += s1[m];
          for(int n = j; n < s2.length(); n++) res += s2[n];
          return res;
     }

     if(dp[i][j] != -1) return dp[i][j];
     
     int ans = INT_MAX;
     if(s1[i] == s2[j]) ans = solveLT712UsingMemo(s1, s2, i + 1, j + 1, dp);
     else {
          int deleteS1 = s1[i] + solveLT712UsingMemo(s1, s2, i + 1, j, dp);
          int deleteS2 = s2[j] + solveLT712UsingMemo(s1, s2, i, j + 1, dp);
          ans = min(deleteS1, deleteS2);
     }
     
     return dp[i][j] = ans;
}

int solveLT712UsingTabulation(string s1, string s2) {
     int n1 = s1.length();
     int n2 = s2.length();
     vector<vector<int>> dp(n1 + 2, vector<int>(n2 + 2, 0));
     
     // Analyzing Base Case
     for(int i = n1 - 1; i >= 0; i--){
          dp[i][n2] = s1[i] + dp[i + 1][n2];
     }
     for(int j = n2 - 1; j >= 0; j--){
          dp[n1][j] = s2[j] + dp[n1][j + 1];
     }

     for(int i = n1 - 1; i >= 0; i--) {
          for(int j = n2 - 1; j >= 0; j--) {
               if(s1[i] == s2[j]) {
               dp[i][j] = dp[i + 1][j + 1];
               }    
               else {
               int deleteS1 = s1[i] + dp[i + 1][j];
               int deleteS2 = s2[j] + dp[i][j + 1];
               dp[i][j] = min(deleteS1, deleteS2);
               }
          }
     }
     
     return dp[0][0];
}

// (THINK!!!)
int solveLT712UsingSpaceOpt(string &s1, string &s2) {
     int n1 = s1.length();
     int n2 = s2.length();
     int n3 = max(n1, n2);

     vector<int> prev(n3 + 1, 0);
     vector<int> curr(n3 + 1, 0);
     
     // Analyzing Base Case
     for(int j = n2 - 1; j >= 0; j--){
          prev[j] = s2[j] + prev[j + 1];
     }

     for(int i = n1 - 1; i >= 0; i--) {
          curr[n2] = s1[i] + prev[n2];
          
          for(int j = n2 - 1; j >= 0; j--) {
               if(s1[i] == s2[j]) {
               curr[j] = prev[j + 1];
               }    
               else {
               int deleteS1 = s1[i] + prev[j];
               int deleteS2 = s2[j] + curr[j + 1];
               curr[j] = min(deleteS1, deleteS2);
               }
          }
          // Shifting
          prev = curr;
     }
     
     return prev[0];
}

int minimumDeleteSum(string s1, string s2) {
     // return solveLT712UsingRec(s1, s2, 0, 0);
     // int n1 = s1.length();
     // int n2 = s2.length();
     // vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, -1));
     // return solveLT712UsingMemo(s1, s2, 0, 0, dp);
     return solveLT712UsingSpaceOpt(s1, s2);
}




// LEETCODE : 115 (Distinct Subsequences)
int solveLT115UsingRec(string &s, string &t, int i, int j) {
     // Base Case
     if(j == t.size()) return 1;
     if(i == s.size()) return 0;

     int ans = 0;
     if(t[j] == s[i]) {
         ans += solveLT115UsingRec(s, t, i + 1, j + 1);  //Moving both 1+ ahead
     }
     ans += solveLT115UsingRec(s, t, i + 1, j);   // For more possibilities
     
     return ans;
}

int solveLT115UsingMemo(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
     // Base Case
     if(j == t.size()) return 1;
     if(i == s.size()) return 0;
     if(dp[i][j] != -1) return dp[i][j];

     int ans = 0;
     if(t[j] == s[i]) {
         ans += solveLT115UsingMemo(s, t, i + 1, j + 1, dp);  //Moving both 1+ ahead
     }
     ans += solveLT115UsingMemo(s, t, i + 1, j, dp);   // "Skip" the current word For more possibilities
     
     return dp[i][j] = ans;
}
 
int solveLT115UsingTabulation(string &s, string &t) {
     vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
     
     // Analyzing the Base Case
     for(int k = 0; k <= s.size(); k++) {
         dp[k][t.size()] = 1;
     }

     for(int i = s.size() - 1; i >= 0; i--) {
          for(int j = t.size() - 1; j >= 0; j--) {
               long long ans = 0;
               if(t[j] == s[i]) {
                    ans += dp[i + 1][j + 1];  // Moving both 1+ ahead
               }
               ans += dp[i + 1][j];   // "Skip" the current word For more possibilities
               dp[i][j] = ans;
          }
     }
     return dp[0][0];
}

int solveLT115UsingSpaceOpt(string &s, string &t) {
     vector<int> curr(t.size() + 1, 0);
     vector<int> prev(t.size() + 1, 0);
     
     // Analyzing the Base Case
     prev[t.size()] = 1;

     for(int i = s.size() - 1; i >= 0; i--) {
          curr[t.size()] = 1;  // IMPORTANT 
          for(int j = t.size() - 1; j >= 0; j--) {
               long long ans = 0;
               if(t[j] == s[i]) {
                    ans += prev[j + 1];  // Moving both 1+ ahead
               }
               ans += prev[j];   // "Skip" the current word For more possibilities
               curr[j] = ans;
          }
          // Shifting
          prev = curr;
     }
     return prev[0];
}

int numDistinct(string s, string t) {
     // vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, -1));
     return solveLT115UsingSpaceOpt(s, t);
}





// LEETCODE : 139 (Word Break)
bool checkLT139ValidWord(string &s, vector<string>& wordDict) {
     for(auto i : wordDict) {
          if(s == i) {
               return true;
          }
     }
     return false;
}
 
bool solveLT139UsingRec(string &s, vector<string>& wordDict, int start) {
     // Base Case
     if(start == s.size()) return true;

     string word = "";
     bool flag = false;
     for(int i = start; i < s.size(); i++) {
         word += s[i];
         if(checkLT139ValidWord(word, wordDict)) {
             flag = flag || solveLT139UsingRec(s, wordDict, i + 1);
         }
     }
     
     return flag;
}

bool solveLT139UsingMemo(string &s, vector<string>& wordDict, int start, vector<int> &dp) {
     // Base Case
     if(start == s.size()) return true;
     if(dp[start] != -1) return dp[start];

     string word = "";
     bool flag = false;
     for(int i = start; i < s.size(); i++) {
         word += s[i];
         if(checkLT139ValidWord(word, wordDict)) {
             flag = flag || solveLT139UsingMemo(s, wordDict, i + 1, dp);
         }
     }
     
     return dp[start] = flag;
}
 
bool wordBreak(string s, vector<string>& wordDict) {
     vector<int> dp(s.size() + 1, -1);
     return solveLT139UsingMemo(s, wordDict, 0, dp);
}





// LEETCODE : 140 (Word Break II)
vector<string> solveLT140UsingRec(string s, unordered_map<string, bool> &dict) {
     // Base Case
     if(s.empty()) return {""};
     
     vector<string> result;
     for(int i = 1; i <= s.size(); i++) {
          string prefix = s.substr(0, i);
          if(dict.find(prefix) != dict.end()) {
               auto suffixWays = solveLT140UsingRec(s.substr(i), dict);
               for(auto suffix : suffixWays) {
                    string newWord = suffix.empty() ? "" : " " + suffix;
                    result.push_back(prefix + newWord);
               }
          }
     } 
     
     return result;
}

vector<string> solveLT140UsingMemo(string s, unordered_map<string, bool> &dict, unordered_map<string,vector<string>> &dp) {
     // Base Case
     if(s.empty()) return {""};
     if(dp.find(s) != dp.end()) dp[s]; 
     
     vector<string> result;
     for(int i = 1; i <= s.size(); i++) {
          string prefix = s.substr(0, i);
          if(dict.find(prefix) != dict.end()) {
               auto suffixWays = solveLT140UsingMemo(s.substr(i), dict, dp);
               for(auto suffix : suffixWays) {
                    string newWord = suffix.empty() ? "" : " " + suffix;
                    result.push_back(prefix + newWord);
               }
          }
     } 
     
     return dp[s] = result;
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
     unordered_map<string, bool> dict;
     for(auto word : wordDict) dict[word] = true;

     unordered_map<string,vector<string>> dp;

     return solveLT140UsingMemo(s, dict, dp);

}




// LEETCODE : 95 (Unique Binary Search Trees II)
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




// LEETCODE : 337 (House Robber III)
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




// LEETCODE : 1406 (Stone Game III)                    [IMPORTANT]
int stoneGameIIISolver(vector<int>& stoneValue, int start, vector<int> &dp) {
     int n = stoneValue.size();
     // Base Case
     if(start >= n) return 0;  // No Stones Left
     if(dp[start] != -1) return dp[start];


     int firstsum = 0;
     int maxDiff = INT_MIN;
     for(int i = 0; i < 3 && start + i < n; i++) {
         firstsum += stoneValue[start + i]; // Take 1, 2, or 3 stones.
         int nextPlayerSum = stoneGameIIISolver(stoneValue, start + i + 1, dp);
         maxDiff = max(maxDiff, firstsum - nextPlayerSum);
     }
     
     return dp[start] = maxDiff;
}

string stoneGameIII(vector<int>& stoneValue) {
     int n = stoneValue.size();
     vector<int> dp(n + 1, -1);
     int result = stoneGameIIISolver(stoneValue, 0, dp);

     if(result > 0) return "Alice";
     if(result < 0) return "Bob";
     return "Tie";
}




// LEETCODE : 1140 (Stone Game II)                      [IMPORTANT]
int stoneGameIIRecursion(vector<int>& piles, int i, int M, bool Alice) {
    // Base Case
     if(i == piles.size()) return 0;

     int total = 0;
     int ans = Alice ? INT_MIN : INT_MAX;
     for(int x = 1; x <= 2*M; x++) {
         if(i + x - 1 >= piles.size()) break;
         total += piles[i + x - 1];
         if(Alice) {
             ans = max(ans, total + stoneGameIIRecursion(piles, i + x, max(M, x), !Alice));
         }
         else {
             ans = min(ans, stoneGameIIRecursion(piles, i + x, max(M, x), !Alice));
         }
     }
     
     return ans;
}

int stoneGameIIMemo(vector<int>& piles, int i, int M, bool Alice, vector<vector<vector<int>>> &dp) {
     // Base Case
     if(i == piles.size()) return 0;
     if(dp[i][M][Alice] != -1) return dp[i][M][Alice];

     int total = 0;
     int ans = Alice ? INT_MIN : INT_MAX;
     for(int x = 1; x <= 2*M; x++) {
         if(i + x - 1 >= piles.size()) break;
         total += piles[i + x - 1];
         if(Alice) {
             ans = max(ans, total + stoneGameIIMemo(piles, i + x, max(M, x), !Alice, dp));
         }
         else {
             ans = min(ans, stoneGameIIMemo(piles, i + x, max(M, x), !Alice, dp));
         }
     }
     
     return dp[i][M][Alice] = ans;
}

int stoneGameII(vector<int>& piles) {
     int n = piles.size();
     vector<vector<vector<int>>> dp(n, vector<vector<int>>(n + 1, vector<int>(2, -1)));
     return stoneGameIIMemo(piles, 0, 1, true, dp);
}





// LEETCODE : 877 (Stone Game)                           
int solevUsingRecursion(vector<int>& piles, int start, int end){
     // Base Case
     if(start >= end) return piles[start];

     int pickLeft = piles[start] - solevUsingRecursion(piles, start + 1, end);
     int pickRight = piles[end] - solevUsingRecursion(piles, start, end - 1);
     
     return max(pickLeft, pickRight);
}

int solevUsingMemo(vector<int>& piles, int start, int end, vector<vector<int>> &dp){
     // Base Case
     if(start >= end) return piles[start];
     if(dp[start][end] != -1) return dp[start][end];

     int pickLeft = piles[start] - solevUsingMemo(piles, start + 1, end, dp);
     int pickRight = piles[end] - solevUsingMemo(piles, start, end - 1, dp);
     
     return dp[start][end] = max(pickLeft, pickRight);
}

int solveUsingTabulation(vector<int>& piles) {
     int n = piles.size();
     vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

     for(int i = 0; i < n; i++) {
         dp[i][i] = piles[i];
     }
     
     for(int len = 2; len <= n; len++) {
         for(int i = 0; i <= n - len; i++) {
             int j = i + len - 1;
             int pickLeft = piles[i] - dp[i + 1][j];
             int pickRight = piles[j] - dp[i][j - 1];
             dp[i][j] = max(pickLeft, pickRight);
         }
     }
     
     return dp[0][n - 1] > 0;
}

bool stoneGame(vector<int>& piles) {
     // int n = piles.size();
     // int start = 0;
     // int end = n - 1;
     // vector<vector<int>> dp(n, vector<int>(n, -1));
     // return solveUsingMemo(piles, start, end, dp) > 0;
     return solveUsingTabulation(piles);
}





// LEETCODE : 97 (Interleaving String)
bool solveLT97UsingRecursion(string s1, string s2, string s3) {
     // Base Case
     if(s1.length() + s2.length() != s3.length()) return false;
     if(s1.empty() && s2.empty() && s3.empty()) return true;

     bool res = false;
     if(!s1.empty() && s1[0] == s3[0]){
         res = res || solveLT97UsingRecursion(s1.substr(1), s2, s3.substr(1));
     }
     if(!s2.empty() && s2[0] == s3[0]){
         res = res || solveLT97UsingRecursion(s1, s2.substr(1), s3.substr(1));
     }
     
     return res;
}

bool solveLT97UsingMemo(string s1, string s2, string s3, int i, int j, vector<vector<int>> &dp) {
     // Base Case
     if (i == s1.length() && j == s2.length()) return true;
     if(dp[i][j] != -1) return dp[i][j];

     bool res = false;
     if(i < s1.length() && s1[i] == s3[i + j]){
         res = res || solveLT97UsingMemo(s1, s2, s3, i + 1, j, dp);
     }
     if(j < s2.length() && s2[j] == s3[i + j]){
         res = res || solveLT97UsingMemo(s1, s2, s3, i, j + 1, dp);
     }
     
     return dp[i][j] = res;
}

bool solveLT97UsingTabulation(string s1, string s2, string s3) {
     vector<vector<bool>> dp(s1.length() + 1, vector<bool>(s2.length() + 1, false));
     dp[s1.length()][s2.length()] = true;

     for(int i = s1.length(); i >= 0; i--) {
         for(int j = s2.length(); j >= 0; j--) {
             if(i < s1.length() && s1[i] == s3[i + j]){
                 dp[i][j] = dp[i][j] || dp[i + 1][j];
             }
             if(j < s2.length() && s2[j] == s3[i + j]){
                 dp[i][j] = dp[i][j] || dp[i][j + 1];
             }
         }
     }
     
     return dp[0][0];
}

bool isInterleave(string s1, string s2, string s3) {
     if(s1.length() + s2.length() != s3.length()) return false;
     // vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, -1));
     // return solveLT97UsingRecursion(s1, s2, s3);
     // return solveLT97UsingMemo(s1, s2, s3, 0, 0, dp);
     return solveLT97UsingTabulation(s1, s2, s3);
}





// LEETCODE : 1312 (Minimum Insertion Steps to Make a String Palindrome)
int solveLT1312UsingRecursion(string &s, int left, int right) {
     // Base Case: when left >= right, it's already a palindrome
     if(left >= right) return 0;
     
     int res = 0;
     if(s[left] == s[right]) {
         res = solveLT1312UsingRecursion(s, left + 1, right - 1);
     }
     else {
         res = 1 + min(solveLT1312UsingRecursion(s, left + 1, right), solveLT1312UsingRecursion(s, left, right - 1));
     }
     
     return res;
}

int solveLT1312UsingMemo(string &s, int left, int right, vector<vector<int>> &dp) {
     // Base Case: when left >= right, it's already a palindrome
     if(left >= right) return 0;
     if(dp[left][right] != -1) return dp[left][right];
     
     int res = 0;
     if(s[left] == s[right]) {
         res = solveLT1312UsingMemo(s, left + 1, right - 1, dp);
     }
     else {
         res = 1 + min(solveLT1312UsingMemo(s, left + 1, right, dp), solveLT1312UsingMemo(s, left, right - 1, dp));
     }
     
     return dp[left][right] = res;
}

int minInsertions(string s) {
     // vector<vector<int>> dp(s.length() + 1, vector<int>(s.length() + 1, -1));
     // return solveLT1312UsingMemo(s, 0, s.length() - 1, dp);
     return solveLT1312UsingTabulation(s, 0, s.length() - 1, dp);
}




