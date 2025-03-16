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



// LEETCODE : 509  (Fibonacci Series)


// Recursion with Memoization
int fibMemoization(int n, vector<int> &dp) {
     if(n <= 1) return n;  // Base cases: F(0) = 0, F(1) = 1
     
     if(dp[n] != -1) {
          // If already computed, 
          // return the value
          return dp[n];
     }
     
     // Compute and store in memo
     dp[n] = fibMemoization(n - 1, dp) + fibMemoization(n - 2, dp);
     return dp[n];
}

int fibonacciMemoization(int n){
     vector<int> dp(n + 1, -1);
     return fibMemoization(n, dp);
}

// Tabulation
int fibonacciTabulation(int n){
     if(n <= 1) return n;  // Base cases: F(0) = 0, F(1) = 1
     vector<int> dp(n + 1, 0);    //Create a table

     dp[0] = 0;
     dp[1] = 1;
     for(int i = 2; i <= n; i++) {
          dp[i] = dp[i - 1] + dp[i - 2];
     }

     return dp[n];    // Return the nth Fibonacci number
}

// Space Optimization
int fibonacciSpaceOptimized(int n) {
     if(n <= 1) return n;  // Base cases: F(0) = 0, F(1) = 1
     
     // Variables to store the last two Fibonacci numbers
     int prev = 0;
     int curr = 1;
     int ans = 0;
     for(int i = 2; i <= n; i++) {
          int ans = prev + curr;
          prev = curr;
          curr = ans;
     }

     return curr;   // Return the nth Fibonacci number
}









// LEETCODE : 198 (House Robber)

// Top-Down Approach
int robMemoization(vector<int>& nums, vector<int> &dp, int index) {
     // Base Case
     if(index >= nums.size()) {
          return 0;
     }

     if(dp[index] != -1) {
          return dp[index];
     }
     
     // [1, 2, 3, 1]

     int include = nums[index] + robMemoization(nums, dp, index + 2);
     int exclude = 0 + robMemoization(nums, dp, index + 1);
     
     // Store & Compute ans in DP
     dp[index] = max(include, exclude);
     return dp[index];
}
int rob(vector<int>& nums){
     int n = nums.size();
     vector<int> dp(n+1, -1);
     int index = 0;
     return robMemoization(nums, dp, index);
}

// Approach - 2
// (Bottom-Up Approach)
int robTabulation(vector<int> &nums) {
     int n = nums.size();
     vector<int> dp(n + 2, -1);

     // Base Cases
     dp[n] = 0; 
     dp[n + 1] = 0; 
     
     // Range reverse + copy paste the same logic
     for(int i = n - 1; i >= 0; i--) {
          int include = nums[i] + dp[i + 2];
          int exclude = 0 + dp[i + 1];
          dp[i] = max(include, exclude);
     }

     return dp[0];   // Maximum amount robbed
}

// Approach - 3
int robOptimized(vector<int> &nums) {
     int n = nums.size();

     int next1 = 0;
     int next2 = 0;

     for(int i = n - 1; i >= 0; i--) {
          int include = nums[i] + next2;
          int exclude = 0 + next1;
          int curr = max(include, exclude);
          next2 = next1;
          next1 = curr;
     }

     return next1;
}









// LEETCODE : 300 (Longest Increasing Subsequence)
int lengthOfLISMemo(vector<int>& nums, int lastIndex, int index, vector<vector<int>>& dp) {
     if(index >= nums.size()) {
          return 0;
     }

     if(dp[lastIndex + 1][index] != -1) {
          return dp[lastIndex + 1][index];
     }

     // Include
     int take = 0;  
     if(lastIndex == -1 || nums[index] > nums[lastIndex]) {
          take = 1 + lengthOfLISMemo(nums, index, index + 1, dp);
     }
     
     // Exclude
     int skip = lengthOfLISMemo(nums, lastIndex, index + 1, dp);
     
     // Store the result in dp array
     dp[lastIndex + 1][index] = max(take, skip);
     return dp[lastIndex + 1][index];
}

int lengthOfLIS(vector<int>& nums) {
     int n = nums.size();
     // create a 2D DP
     vector<vector<int>> dp(n, vector<int>(n + 1, -1));
     int lastIndex = -1;
     int index = 0;

     return lengthOfLISMemo(nums, lastIndex, index, dp);
}


// using Recursion
int lengthOfLISRec(vector<int>& nums, int prevIndex, int currIndex) {
     // Base Case 
     if(currIndex >= nums.size()) {
          return 0;
     }
     
     // Include
     int include = 0;
     if(prevIndex == -1 || nums[currIndex] > nums[prevIndex]) {
          include = 1 + lengthOfLISRec(nums, currIndex, currIndex + 1);
     }
     
     // Exclude
     int exclude = lengthOfLISRec(nums, prevIndex, currIndex + 1);
     int finalAns = max(include, exclude);
     
     return finalAns;
}

int lengthOfLIS_2(vector<int>& nums) {
     int prevIndex = -1;
     int currIndex = 0;
     return lengthOfLISRec(nums, prevIndex, currIndex);
}








// 0 - 1 Knapsack Problem
int solveUsingRec(int capacity, int index, vector<int> &val, vector<int> &wt){
     // Base Case
     if(index == 0) {
          if(wt[index] <= capacity) {
               return val[index];
          }
          else {
               return 0;
          }
     }
     
     // Include
     int include = 0;
     if(wt[index] <= capacity) {
          include = val[index] + solveUsingRec(capacity - wt[index], index - 1, val, wt);
     }
     // Exclude 
     int exclude = solveUsingRec(capacity, index - 1, val, wt);
     
     int finalAns = max(include, exclude);
     return finalAns;
}

// Top-Down Approach 
int solveUsingMem(int capacity, int index, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp){
     // Base Case
     if(index == 0){
          if(wt[index] <= capacity) {
               return val[index];
          }
          else {
               return 0;
          }
     }
     if(dp[index][capacity] != -1) {
          return dp[index][capacity];
     }

     // Include
     int include = 0;
     if(wt[index] <= capacity) {
          include = val[index] + solveUsingMem(capacity - wt[index], index - 1, val, wt, dp);
     }
     // Exclude
     int skip = solveUsingMem(capacity, index - 1, val, wt, dp);
     return dp[index][capacity] = max(include, skip);
}

// Bottom-Up Approach
int solveUsingTabulation(int capacity, vector<int> &val, vector<int> &wt) {
     int n = val.size();
     // Create a DP table with dimensions (n+1) x (capacity+1)
     vector<vector<int>> dp(n + 1, vector<int> (capacity + 1, 0));
     
     // Reverse the Range
     // And, Fill the DP table
     for(int i = 1; i <= n; i++) {
          for(int j = 1; j <= capacity; j++) {
               if(wt[i - 1] <= j) {
                    // Include the current item or exclude it
                    dp[i][j] = max(dp[i - 1][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
               }
               else{
                    // Exclude the current item
                    dp[i][j] = dp[i - 1][j];
               }
          }
     }
     
     return dp[n][capacity];
}

int knapSack(int capacity, vector<int> &val, vector<int> &wt) {
     return solveUsingTabulation(capacity, val, wt);
}







// LEETCODE : 1143  (Longest Common Subsequence)
int solveLCSUsingRec(string &text1, string &text2, int i, int j) {
     // Base Case 
     if(i >= text1.length()) {
          return 0;
     }
     if(j >= text2.length()) {
          return 0;
     }

     int ans = 0;
     if(text1[i] == text2[j]) {
          ans = 1 + solveUsingRec(text1, text2, i + 1, j + 1);
     }
     else {
          ans = max(solveUsingRec(text1, text2, i + 1, j), solveUsingRec(text1, text2, i, j + 1));
     }

     return ans;
}

int solveLCSUsingMem(string &text1, string &text2, int i, int j, vector<vector<int>> &dp) {
     if(i >= text1.length()) {
          return 0;
     }
     if(j >= text2.length()) {
          return 0;
     }
     if(dp[i][j] != -1) {
          return dp[i][j];
     }
     
     int ans = 0;
     if(text1[i] == text2[j]) {
          ans = 1 + solveUsingMem(text1, text2, i + 1, j + 1, dp);
     }
     else {
          ans = max(solveUsingMem(text1, text2, i + 1, j, dp), solveUsingMem(text1, text2, i, j + 1, dp));
     }

     return dp[i][j] = ans;
}

int solveLCSUsingTabulation(string &text1, string &text2) {
     // dp array of size (i + 1) * (j + 1)
     vector<vector<int>> dp(text1.length() + 1, vector<int> (text2.length() + 1, 0));

     // Reverse the range
     // And, Analyze the Base Case
     for(int i = text1.length() - 1; i >= 0; i--) {
          for(int j = text2.length() - 1; j >= 0; j--) {
               int ans = 0;
               if(text1[i] == text2[j]) {
                    ans = 1 + dp[i+1][j+1];
               }
               else {
                    ans = max(dp[i+1][j], dp[i][j+1]);
               }
               dp[i][j] = ans;
          }
     } 
     
     return dp[0][0];
}

int solveLCSUsingTabSpaceOpt(string &text1, string &text2) {
     // Creating two vectors -> curr & prev
     vector<int> curr(text2.length() + 1, 0);
     vector<int> prev(text2.length() + 1, 0);

     // This means -> dp[i + 1] == prev & dp[i] == curr

     for(int i = text1.length() - 1; i >= 0; i--) {
          for(int j = text2.length() - 1; j >= 0; j--) {
          int ans = 0;
          if(text1[i] == text2[j]) {
               ans = 1 + prev[j+1];
          }
          else {
               ans = 0 + max(prev[j], curr[j+1]);
          }
          curr[j] = ans;
          }
          // Shifting
          prev = curr;
     } 

     return prev[0];
}
     
int longestCommonSubsequence(string text1, string text2) {
     // int i = 0;
     // int j = 0;
     // vector<vector<int>> dp(text1.length() + 1, vector<int> (text2.length() + 1, -1));
     return solveUsingTabSpaceOpt(text1, text2);
}







// LEETCODE : 1691 (Maximum Height by Stacking Cuboids )
bool intialCond(vector<int> &cuboid1, vector<int> &cuboid2) {
     if(cuboid2[0] >= cuboid1[0] && cuboid2[1] >= cuboid1[1] && cuboid2[2] >= cuboid1[2]) {
          return true;
     }
     return false;
}

int solvemaxHeightUsingRec(vector<vector<int>>& cuboids, int curr, int prev) {
     // Base Case
     if(curr >= cuboids.size()) {
          return 0;
     }

     // Include
     int take = 0;
     if(prev == -1 || intialCond(cuboids[prev], cuboids[curr])) {
          take = cuboids[curr][2] + solveUsingRec(cuboids, curr + 1, curr);
     }
     // Exclude
     int skip = 0 + solveUsingRec(cuboids, curr + 1, prev);
     int finalAns = max(take, skip);

     return finalAns;
}

int solvemaxHeightUsingMem(vector<vector<int>>& cuboids, int curr, int prev, vector<vector<int>> &dp) {
     // Base Case
     if(curr >= cuboids.size()) {
          return 0;
     }
     if(dp[curr][prev + 1] != -1) {
          return dp[curr][prev + 1];
     }

     // Include
     int take = 0;
     if(prev == -1 || intialCond(cuboids[prev], cuboids[curr])) {
          take = cuboids[curr][2] + solveUsingMem(cuboids, curr + 1, curr, dp);
     }
     // Exclude
     int skip = 0 + solveUsingMem(cuboids, curr + 1, prev, dp);
     return dp[curr][prev + 1] = max(take, skip);
}

int solvemaxHeightUsingTabulation(vector<vector<int>>& cuboids) {
     int n = cuboids.size();
     vector<vector<int>> dp(n + 1, vector<int> (n + 1, -0));

     for(int curr = n - 1; curr >= 0; curr--) {
          for(int prev = curr - 1; prev >= -1; prev--) {
               // Include
               int take = 0;
               if(prev == -1 || intialCond(cuboids[prev], cuboids[curr])) {
               take = cuboids[curr][2] + dp[curr + 1][curr + 1];
               }
               // Exclude
               int skip = 0 + dp[curr + 1][prev + 1];
               dp[curr][prev + 1] = max(take, skip);
          }
     }
     return dp[0][-1 + 1];
}

int solvemaxHeightUsingTabulationSpaceOpt(vector<vector<int>>& cuboids) {
     int n = cuboids.size();
     vector<int> prevRow(n + 1, 0);
     vector<int> currRow(n + 1, 0);

     for(int curr = n - 1; curr >= 0; curr--) {
          for(int prev = curr - 1; prev >= -1; prev--) {
               // Include
               int take = 0;
               if(prev == -1 || intialCond(cuboids[prev], cuboids[curr])) {
               take = cuboids[curr][2] + prevRow[curr + 1];
               }
               // Exclude
               int skip = 0 + prevRow[prev + 1];
               currRow[prev + 1] = max(take, skip);
          }
          // Shifting 
          prevRow = currRow;
     }
     return prevRow[-1 + 1];
}


int maxHeight(vector<vector<int>>& cuboids) {
     // Sorting all idnividual cuboids and the collection of them 
     // so that the max Height is present at the 2nd (last) index

     for(auto &vec : cuboids) {
          sort(vec.begin(), vec.end());
     }
     sort(cuboids.begin(), cuboids.end());
     
     // int n = cuboids.size();
     // vector<vector<int>> dp(n + 1, vector<int> (n + 1, -1));
     // int curr = 0;
     // int prev = -1;
     // return solveUsingMem(cuboids, curr, prev, dp);

     return solveUsingTabulation(cuboids);
}








// LEETCODE : 375 (Guess Number Higher or Lower II)
// Merge-Interval Method
int solveGMAUsingRec(int i, int j) {
     // Base case
     if(i >= j) {
          return 0;
     }

     int minCost = INT_MAX;
     for(int num = i; num < j; num++) {
          // Taking the worst-case cost between the two subRanges
          int cost = num + max(solveGMAUsingRec(i, num - 1), solveGMAUsingRec(num + 1, j));
          // Keeping track of all the possible guesses
          minCost = min(minCost, cost);
     }
     
     return minCost;
}

int solveGMAUsingMemo(int i, int j, vector<vector<int>> &dp) {
     // Base case
     if(i >= j) {
          return 0;
     }
     if(dp[i][j] != -1) {
          return dp[i][j];
     }

     int minCost = INT_MAX;
     for(int num = i; num < j; num++) {
          // Taking the worst-case cost between the two subRanges
          int cost = num + max(solveGMAUsingMemo(i, num - 1, dp), solveGMAUsingMemo(num + 1, j, dp));
          // Keeping track of all the possible guesses
          minCost = min(minCost, cost);
     }
     
     return dp[i][j] = minCost;
}

int solveGMAUsingTabulation(int n){
     vector<vector<int>> dp(n + 2, vector<int> (n + 2, 0));

     for(int i = n; i >= 1; i--) {
          for(int j = 1; j <= n; j++) {
               if(i >= j) continue;

               else {
               int minCost = INT_MAX;
               for(int num = i; num < j; num++) {
                    // Taking the worst-case cost between the two subRanges
                    int cost = num + max(dp[i][num - 1], dp[num + 1][j]);
                    // Keeping track of all the possible guesses
                    minCost = min(minCost, cost);
               }
               dp[i][j] = minCost;
               }
          }
     }

     return dp[1][n];
}

int getMoneyAmount(int n) {
     // vector<vector<int>> dp(n + 1, vector<int> (n + 1, -1));
     // return solveUsingMemo(1, n, dp);
     return solveGMAUsingTabulation(n);
}








// LEETCODE : 1130 (Minimum Cost Tree From Leaf Values)
int solveUsingRec(vector<int>& arr, map<pair<int, int>,int> &maxi, int left, int right){
     // Base Case
     if(left >= right) {
          return 0;
     }

     int ans = INT_MAX;
     for(int i = left; i < right; i++) {
          int leftRangeMax = maxi[{left, i}];
          int rightRangeMax = maxi[{i + 1, right}];
          // Product of the two maximums
          int NonleafNode = leftRangeMax * rightRangeMax;
          // Recursive call for left and right partitions
          int currentCost =  NonleafNode + 
                              solveUsingRec(arr, maxi, left, i) + 
                              solveUsingRec(arr, maxi, i + 1, right);

          ans = min(ans, currentCost);
     }
     
     return ans;
}

int solveUsingMemo(vector<int>& arr, map<pair<int, int>,int> &maxi, int left, int right, vector<vector<int>> &dp) {
     // Base Case
     if(left >= right) {
          return 0;
     }
     if(dp[left][right] != -1) {
          return dp[left][right];
     }

     int ans = INT_MAX;
     for(int i = left; i < right; i++) {
          int leftRangeMax = maxi[{left, i}];
          int rightRangeMax = maxi[{i + 1, right}];
          // Product of the two maximums
          int NonleafNode = leftRangeMax * rightRangeMax;
          // Recursive call for left and right partitions
          int currentCost =  NonleafNode + 
                              solveUsingMemo(arr, maxi, left, i, dp) + 
                              solveUsingMemo(arr, maxi, i + 1, right, dp);

          ans = min(ans, currentCost);
     }
     
     return dp[left][right] = ans;
}

int solveUsingTabulation(vector<int>& arr, map<pair<int, int>,int> &maxi) {
     int n = arr.size();

     vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

     for(int i = n - 1; i >= 0; i--) {
          for(int j = 0; j <= n - 1; j++) {
               if(i >= j) continue;

               else {
               int ans = INT_MAX;
               for(int k = i; k < j; k++) {
                    int leftRangeMax = maxi[{i, k}];
                    int rightRangeMax = maxi[{k + 1, j}];
                    // Product of the two maximums
                    int NonleafNode = leftRangeMax * rightRangeMax;
                    // Recursive call for left and right partitions
                    int currentCost =  NonleafNode + 
                                   solveUsingMemo(arr, maxi, i, k, dp) + 
                                   solveUsingMemo(arr, maxi, k + 1, j, dp);

                    ans = min(ans, currentCost);
               } 
               dp[i][j] = ans;   
               }
          }    
     }

     return dp[0][n - 1];
}

int mctFromLeafValues(vector<int>& arr) {
     map<pair<int, int>, int> maxi;
     // Can't create pairs in unordered map
     
     int n = arr.size();

     for(int i = 0; i < n; i++){
          for(int j = i; j < n; j++){
               if(i == j) {
               maxi[{i, j}] = arr[i];
               }
               else {
               maxi[{i, j}] = max(maxi[{i, j - 1}], arr[j]);
               }
          }
     }

     // vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
     // int left = 0;
     // int right = n - 1;
     return solveUsingTabulation(arr, maxi);
}









// LEETCODE : 62 (Unique Paths I)
int solveUsingRec(int i, int j) {
     if(i == 0 && j == 0) {
          return 1;
     }

     if(i < 0 || j < 0) {
          return 0;
     }

     // either down or right
     int path1 = solveUsingRec(i - 1, j);
     int path2 = solveUsingRec(i, j - 1);

     return path1 + path2;
}

int solveUsingMem(int i, int j, vector<vector<int>> &dp) {
     if(i == 0 && j == 0) {
          return 1;
     }

     if(dp[i][j] != -1) {
          return dp[i][j];
     }

     if(i < 0 || j < 0) {
          return 0;
     }

     // either down or right
     int path1 = solveUsingMem(i - 1, j, dp);
     int path2 = solveUsingMem(i, j - 1, dp);
     int shortestPath = path1 + path2;
     return dp[i][j] = shortestPath;
}

int solveUsingTabulation(int m, int n){
     vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
     
     for(int i = 0; i < m; i++) {
          for (int j = 0; j < n; j++) {
               // analyze the Base Case
               if (i == 0 && j == 0) dp[i][j] = 1;
               else{
                    int path1 = (i > 0) ? dp[i-1][j] : 0;
                    int path2 = (j > 0) ? dp[i][j-1] : 0;
                    dp[i][j] = path1 + path2;
               }
          }
     }
     
     return dp[m-1][n-1];
}

int solveUsingSpaceOpt(int m, int n) {
     vector<int> prev(n);
     vector<int> curr(n);

     for(int i = 0; i < m; i++) {
          for (int j = 0; j < n; j++) {
               // analyze the Base Case
               if (i == 0 && j == 0) curr[j] = 1;
               else{
               int path1 = (i > 0) ? prev[j] : 0;
               int path2 = (j > 0) ? curr[j-1] : 0;
               curr[j] = path1 + path2;
               }
          }
          // Shifting 
          prev = curr;
     }
     
     return prev[n-1];
}

int uniquePaths(int m, int n) {
     return solveUsingSpaceOpt(m, n);
} 









// LEETCODE : 63 (Unique Paths II)
int solveUsingRec(vector<vector<int>>& obstacleGrid, int m, int n) {
     // Base Case
     if(m == 0 && n == 0) return (obstacleGrid[m][n] == 0) ? 1 : 0;
     if(m < 0 || n < 0 || obstacleGrid[m][n] == 1) return 0;

     int path1 = solveUsingRec(obstacleGrid, m - 1, n);
     int path2 = solveUsingRec(obstacleGrid, m, n - 1);

     return path1 + path2;
}

int solveUsingMemo(vector<vector<int>>& obstacleGrid, int m, int n, vector<vector<int>> &dp) {
     // Base Case
     if(m == 0 && n == 0) return (obstacleGrid[m][n] == 0) ? 1 : 0;
     // Out Of Buund & Obstacle Case
     if(m < 0 || n < 0 || obstacleGrid[m][n] == 1) return 0;
     if(dp[m][n] != -1) return dp[m][n];

     int path1 = solveUsingMemo(obstacleGrid, m - 1, n, dp);
     int path2 = solveUsingMemo(obstacleGrid, m, n - 1, dp);

     return dp[m][n] = path1 + path2;
}

int solveUsingTabulation(vector<vector<int>>& obstacleGrid) {
     int rows = obstacleGrid.size();
     int cols = obstacleGrid[0].size();
     vector<vector<int>> dp(rows + 1, vector<int> (cols + 1, 0));

     for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
               if(i == 0 && j == 0) dp[i][j] = (obstacleGrid[i][j] == 0) ? 1 : 0;
               else if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
               else {
               int path1 = (i > 0) ? dp[i - 1][j] : 0;
               int path2 = (j > 0) ? dp[i][j - 1] : 0;
               dp[i][j] = path1 + path2;
               }
          }
     }
     
     return dp[rows - 1][cols - 1];
}

// Using 1-D Array
int solveUsingSpaceOptI(vector<vector<int>>& obstacleGrid) {
     int rows = obstacleGrid.size();
     int cols = obstacleGrid[0].size();

     vector<int> prev (cols);
     for(int i = 0; i < rows; i++) {
          vector<int> curr (cols);
          for(int j = 0; j < cols; j++) {
               if(i == 0 && j == 0) curr[j] = (obstacleGrid[i][j] == 0) ? 1 : 0;
               else if (obstacleGrid[i][j] == 1) curr[j] = 0;
               else {
               int path1 = (i > 0) ? prev[j] : 0;
               int path2 = (j > 0) ? curr[j - 1] : 0;
               curr[j] = path1 + path2;
               }
          }
          // Shifting
          prev = curr;
     }
     
     return prev[cols - 1];
}

// Using 2-D Array
int solveUsingSpaceOptII(vector<vector<int>>& obstacleGrid) {
     int rows = obstacleGrid.size();
     int cols = obstacleGrid[0].size();

     vector<int> dp(cols);
     for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
               if(i == 0 && j == 0) dp[j] = (obstacleGrid[i][j] == 0) ? 1 : 0;
               else if (obstacleGrid[i][j] == 1) dp[j] = 0;
               else {
               int pathFromLeft = (j > 0) ? dp[j - 1] : 0;
               dp[j] += pathFromLeft;
               // dp[j] contains the value from the top of the same column
               }
          }
     }
     
     return dp[cols - 1];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
     // int rows = obstacleGrid.size() - 1;
     // int cols = obstacleGrid[0].size() - 1;
     // vector<vector<int>> dp(rows + 1, vector<int> (cols + 1, -1));
     return solveUsingSpaceOptII(obstacleGrid);
}









// LEETCODE : 44 (Wildcard Matching)
bool solveLT44UsingRec(string &s, string &p, int i, int j) { 
     // Base Cases
     if(i == s.length() && j == p.length()) {
          return true;
     }
     // Pattern string finishes First
     if(j == p.length()) {
          return false;
     }
     // String(s) finishes First
     if(i == s.length()) {
          for(int k = j; k < p.length(); k++) {
               if(p[k] != '*') {
               return false;
               break;
               }
          }

          return true;
     }


     // Main Logic -> Comparing Characters
     if(p[j] == '?' || s[i] == p[j]) {
          return solveLT44UsingRec(s, p, i + 1, j + 1);
     }

     else if(p[j] == '*') {
          // 1st : Replace * -> "."*
          // 2nd : Replace * -> ""
          return solveLT44UsingRec(s, p, i + 1, j) || solveLT44UsingRec(s, p, i, j + 1);
     }
     
     else {
          // Not Match
          return false;
     }
}

bool solveLT44UsingMem(string &s, string &p, int i, int j, vector<vector<int>> &dp) { 
     // Base Cases
     if(i == s.length() && j == p.length()) {
          return true;
     }
     // Pattern string finishes First
     if(j == p.length()) {
          return false;
     }
     // String(s) finishes First
     if(i == s.length()) {
          for(int k = j; k < p.length(); k++) {
               if(p[k] != '*') {
               return false;
               break;
               }
          }
          return true;
     }

     bool ans;
     // Main Logic -> Comparing Characters
     if(p[j] == '?' || s[i] == p[j]) {
          ans = solveLT44UsingMem(s, p, i + 1, j + 1, dp);
     }

     else if(p[j] == '*') {
          // 1st : Replace * -> "."*
          // 2nd : Replace * -> ""
          ans = solveLT44UsingMem(s, p, i + 1, j, dp) || solveLT44UsingMem(s, p, i, j + 1, dp);
     }
     
     else {
          // Not Match
          ans = false;
     }

     return dp[i][j] = ans;
}

bool solveLT44UsingTabulation(string &s, string &p) {
     int m = s.length();
     int n = p.length();
     vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

     // Analyze the Base Case
     dp[m][n] = true;
     
     for(int col = 0; col < n; col++) {
          bool flag = true;
          for(int k = col; k < p.length(); k++) {
               if(p[k] != '*') {
                    flag = false;
                    break;
               }
          }
          dp[m][col] = flag;
     }
     
     // Solving
     for(int i = m - 1; i >= 0; i--) {
          for(int j = n - 1; j >= 0; j--) {
               bool ans;
               // Main Logic -> Comparing Characters
               if(p[j] == '?' || s[i] == p[j]) {
                    ans = dp[i+1][j+1];
               }

               else if(p[j] == '*') {
                    // 1st : Replace * -> "."*
                    // 2nd : Replace * -> ""
                    ans = dp[i+1][j] || dp[i][j+1];
               }
               
               else {
                    // Not Match
                    ans = false;
               }

               dp[i][j] = ans;
          }
     }

     return dp[0][0];
}

bool isMatch(string s, string p) {
     // vector<vector<int>> dp(s.length() + 1, vector<int>(p.length() + 1, - 1));
     // bool ans = solveUsingMem(s , p, 0, 0, dp);
     return solveLT44UsingTabulation(s, p);
}







// LEETCODE : 10 (Regular Expression Matching)
bool solveLT10UsingRecII(string &s, string &p, int i, int j) {
     // Base Cases
     if(j < 0) return i < 0; 

     // String(s) exhausted First
     if(i < 0) {
          if(j >= 1 && p[j] == '*') {
               // Check if the remaining pattern can match an empty string
               return solveLT10UsingRecII(s, p, i, j - 2);
          }
          return false;
     }
     
     // Check for '*' in the pattern
     if(j >= 1 && p[j] == '*') {
          // '*' Matches zero or more of the preceding character
          if(solveLT10UsingRecII(s, p, i, j - 2)) return true;
          
          if(p[j - 1] == s[i] || p[j - 1] == '.') {
               return solveLT10UsingRecII(s, p, i - 1, j);   // Match one or more occurrences
          }
          else {
               return false;
          }
     }

     if(s[i] == p[j] || p[j] == '.') {
          return solveLT10UsingRecII(s, p, i - 1, j - 1);
     }
     
     // No match Found 
     return false;
}

bool solveLT10UsingMemoII(string &s, string &p, int i, int j, vector<vector<int>> &dp) {
     // Base Cases
     if(j < 0) return dp[i + 1][j + 1] = (i < 0); 
     
     if(dp[i + 1][j + 1] != -1) return dp[i + 1][j + 1];

     // String(s) exhausted First
     if(i < 0) {
          if(j >= 1 && p[j] == '*') {
               // Check if the remaining pattern can match an empty string
               return dp[i + 1][j + 1] = solveLT10UsingMemoII(s, p, i, j - 2, dp);
          }
          return dp[i + 1][j + 1] = false;
     }
     
     // Check for '*' in the pattern
     if(j >= 1 && p[j] == '*') {
          // '*' Matches zero or more of the preceding character
          if(solveLT10UsingMemoII(s, p, i, j - 2, dp)) return dp[i + 1][j + 1] = true;
          
          if(p[j - 1] == s[i] || p[j - 1] == '.') {
               return dp[i + 1][j + 1] = solveLT10UsingMemoII(s, p, i - 1, j, dp);   // Match one or more occurrences
          }
          else {
               return dp[i + 1][j + 1] = false;
          }
     }

     if(s[i] == p[j] || p[j] == '.') {
          return dp[i + 1][j + 1] = solveLT10UsingMemoII(s, p, i - 1, j - 1, dp);
     }
     
     else {
          // No match Found 
          return dp[i + 1][j + 1] = false;
     }

     return dp[i + 1][j + 1];
}

bool solveUsingRecI(string &s, string &p, int i, int j) {
     // Base Case
     if(i >= s.length() && j >= p.length()) return true;
     
     // String(s) exhausted first
     if(j >= p.length()) return false;

     bool currMatch = (i < s.length()) && (s[i] == p[j] || p[j] == '.');
     

     // If the string is exhausted but the pattern isn't, 
     // the recursive logic for '*' or other checks naturally handles the case.
     if(j + 1 < p.length() && p[j + 1] == '*') {
          // Case 1: Treat the preceding character and '*' as empty
          bool treatASEmpty = solveLT10UsingRecI(s, p, i, j + 2);
          // Case 2: Match the current character and recurse
          bool matchMultiple = currMatch && solveLT10UsingRecI(s, p, i + 1, j);
          return treatASEmpty || matchMultiple;
     }
     
     if(currMatch) {
          return solveLT10UsingRecI(s, p, i + 1, j + 1);
     }

     // No match found
     return false;
}

bool solveLT10UsingMemoI(string &s, string &p, int i, int j, vector<vector<int>> &dp) {
     // Base Case
     if(i >= s.length() && j >= p.length()) {
          return dp[i + 1][j + 1] = true;
     } 
     
     // Return memoized result if already computed
     if (dp[i + 1][j + 1] != -1){
          return dp[i + 1][j + 1];
     } 
     
     // String(s) exhausted first
     if(j >= p.length()) return dp[i + 1][j + 1] = false;

     bool currMatch = (i < s.length()) && (s[i] == p[j] || p[j] == '.');
     

     // If the string is exhausted but the pattern isn't, 
     // the recursive logic for '*' or other checks naturally handles the case.
     if(j + 1 < p.length() && p[j + 1] == '*') {
          // Case 1: Treat the preceding character and '*' as empty
          bool treatASEmpty = solveLT10UsingMemoI(s, p, i, j + 2, dp);
          // Case 2: Match the current character and recurse
          bool matchMultiple = currMatch && solveLT10UsingMemoI(s, p, i + 1, j, dp);
          return dp[i + 1][j + 1] = treatASEmpty || matchMultiple;
     }
     
     if(currMatch) {
          return dp[i + 1][j + 1] = solveLT10UsingMemoI(s, p, i + 1, j + 1, dp);
     }
     
     else {
          // No match found
          return dp[i + 1][j + 1] = false;
     }
}

bool solveUsingTabulation(string &s, string &p) {
     int m = s.length();
     int n = p.length();
     vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
     dp[m][n] = true;

     for(int i = m; i >= 0; i--) {
          for(int j = n - 1; j >= 0; j--) {
               bool currMatch = (i < m) && (s[i] == p[j] || p[j] == '.');
               
               if((j + 1 < n) && p[j + 1] == '*') {
               // Case 1: Treat the preceding character and '*' as empty
               bool treatASEmpty = dp[i][j + 2];
               // Case 2: Match the current character and recurse
               bool matchMultiple = currMatch && dp[i + 1][j];
               dp[i][j] = treatASEmpty || matchMultiple;
               }
               
               else if(currMatch) {
               dp[i][j] = dp[i + 1][j + 1];
               }

               else {
               // No match found
               dp[i][j] = false;
               }
          }
     }

     return dp[0][0];
}

bool solveLT10UsingSpaceOpt(string &s, string &p) {
     int m = s.length();
     int n = p.length();

     vector<int> curr(n + 1, 0);
     vector<int> prev(n + 1, 0);
     prev[n] = true;

     for(int i = m; i >= 0; i--) {
          curr[n] = (i == m); // Empty pattern matches only an empty string
          for(int j = n - 1; j >= 0; j--) {
               bool currMatch = (i < m) && (s[i] == p[j] || p[j] == '.');
               
               if((j + 1 < n) && p[j + 1] == '*') {
               // Case 1: Treat the preceding character and '*' as empty
               bool treatASEmpty = curr[j + 2];
               // Case 2: Match the current character and recurse
               bool matchMultiple = currMatch && prev[j];
               curr[j] = treatASEmpty || matchMultiple;
               }
               
               else if(currMatch) {
               curr[j] = prev[j + 1];
               }

               else {
               // No match found
               curr[j] = false;
               }
          }
          // Shifting
          prev = curr;
     }

     return prev[0];
}

bool isMatch(string s, string p) {
     // vector<vector<int>> dp(s.length() + 2, vector<int>(p.length() + 2, -1));
     // return solveUsingMemoI(s, p, 0, 0, dp);
     return solveLT10UsingSpaceOpt(s, p);
}





// LEETCODE : 64 (Minimum Path Sum)
int solveLT64UsingRec(vector<vector<int>>& grid, int i, int j) {
     // Base Case
     if(i == 0 && j == 0) {
          return grid[0][0];
     }
     if(i < 0 || j < 0) return INT_MAX;

     int path1 = (i > 0) ? grid[i][j] + solveLT64UsingRec(grid, i - 1, j) : INT_MAX;
     int path2 = (j > 0) ? grid[i][j] + solveLT64UsingRec(grid, i, j - 1): INT_MAX;
     int finalAns = min(path1, path2);
     return finalAns;
}

int solveLT64UsingMemo(vector<vector<int>>& grid, int i, int j, vector<vector<int>> &dp) {
     // Base Case
     if(i == 0 && j == 0) {
          return grid[0][0];
     }
     if(i < 0 || j < 0) return INT_MAX;
     if(dp[i][j] != -1) return dp[i][j];

     int path1 = (i > 0) ? grid[i][j] + solveLT64UsingMemo(grid, i - 1, j, dp) : INT_MAX;
     int path2 = (j > 0) ? grid[i][j] + solveLT64UsingMemo(grid, i, j - 1, dp): INT_MAX;
     
     return dp[i][j] = min(path1, path2);
}

int solveLT64UsingTabulation(vector<vector<int>>& grid) {
     int m = grid.size();
     int n = grid[0].size();
     vector<vector<int>> dp(m, vector<int> (n, 0));

     for(int i = 0; i < m; i++) {
          for(int j = 0; j < n; j++) {
                    if(i == 0 && j == 0) {
                    dp[i][j] = grid[0][0];
               }
               else {
                    int path1 = (i > 0) ? grid[i][j] + dp[i - 1][j] : INT_MAX;
                    int path2 = (j > 0) ? grid[i][j] + dp[i][j - 1] : INT_MAX;
                    dp[i][j] = min(path1, path2);
               }
          }
     }
     
     return dp[m - 1][n - 1];
}

int solveLT64UsingSpaceOpt(vector<vector<int>>& grid) {
     int m = grid.size();
     int n = grid[0].size();
     vector<int> prev (n, 0);
     vector<int> curr(n, 0);

     for(int i = 0; i < m; i++) {
          for(int j = 0; j < n; j++) {
                    if(i == 0 && j == 0) {
                    curr[j] = grid[0][0];
               }
               else {
                    int path1 = (i > 0) ? grid[i][j] + prev[j] : INT_MAX;
                    int path2 = (j > 0) ? grid[i][j] + curr[j - 1] : INT_MAX;
                    curr[j] = min(path1, path2);
               }
          }
          // Shifting
          prev = curr;
     }
     
     return prev[n - 1];
}

int minPathSum(vector<vector<int>>& grid) {
     // int i = grid.size() - 1;
     // int j = grid[0].size() - 1;
     // vector<vector<int>> dp(i + 1, vector<int> (j + 1, -1));
     return solveLT64UsingSpaceOpt(grid);
}






// LEETCODE : 120 (Triangle)
int solveLT120UsingRec(vector<vector<int>>& triangle, int i, int j, int n) {
     // Base Case
     if(i == n - 1) return triangle[i][j];
     
     int down = triangle[i][j] + solveLT120UsingRec(triangle, i + 1, j, n);
     int diag = triangle[i][j] + solveLT120UsingRec(triangle, i + 1, j + 1, n);
     return min(down, diag);
} 

int solveLT120usingMemo(vector<vector<int>>& triangle, vector<vector<int>>& dp, int i, int j, int n) {
     // Base Case
     if(i == n - 1) return triangle[i][j];
     if(dp[i][j] != -1) return dp[i][j];

     int down = triangle[i][j] + solveLT120usingMemo(triangle, dp, i + 1, j, n);
     int diag = triangle[i][j] + solveLT120usingMemo(triangle, dp, i + 1, j + 1, n);
     return dp[i][j] = min(down, diag);
}

int solveLT120usingTabulation(vector<vector<int>>& triangle) {
     int n = triangle.size();
     int m = triangle[n-1].size();
     vector<vector<int>> dp(n, vector<int>(n, -1));

     for(int k = 0; k < m; k++) {
          dp[n-1][k] = triangle[n-1][k];
     }

     for(int i = n - 2; i >= 0; i--) {
          for(int j = i; j >= 0; j--) {
               int down = triangle[i][j] + dp[i + 1][j];
               int diag = triangle[i][j] + dp[i + 1][j + 1];
               dp[i][j] = min(down, diag);
          }
     }
     
     return dp[0][0];
}

int solveLT120usingSpaceOpt(vector<vector<int>> &triangle){
     int n = triangle.size();
     int m = triangle[n - 1].size();
     vector<int> curr(n);
     vector<int> prev(n);

     for(int k = 0; k < m; k++) {
          prev[k] = triangle[n-1][k];
     }

     for(int i = n - 2; i >= 0; i--) {
          for(int j = i; j >= 0; j--) {
               int down = triangle[i][j] + prev[j];
               int diag = triangle[i][j] + prev[j + 1];
               curr[j] = min(down, diag);
          }
          // Shifting
          prev = curr;
     }
     
     return prev[0];

}

int minimumTotal(vector<vector<int>>& triangle) {
     // int n = triangle.size();
     // vector<vector<int>> dp(n, vector<int>(n, -1));
     // return solveusingMemo(triangle, dp, 0, 0, n);
     return solveLT120usingSpaceOpt(triangle);
}





// LEETCODE : 931 (Minimum Falling Path Sum)
int solveLT931UsingRec(vector<vector<int>>& matrix, int row, int col) {
     // Base Case
     if(col < 0 || col >= matrix[0].size()) return 1e9;
     if(row == 0) return matrix[0][col];

     int left = matrix[row][col] + solveLT931UsingRec(matrix, row - 1, col);
     int down = matrix[row][col] + solveLT931UsingRec(matrix, row - 1, col - 1);
     int right = matrix[row][col] + solveLT931UsingRec(matrix, row - 1, col + 1);
     
     return min(down, min(left, right));
}

int solveLT931UsingMemo(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& dp) {
     // Base Case
     if(col < 0 || col >= matrix[0].size()) return 1e9;
     if(row == 0) return matrix[0][col];
     if(dp[row][col] != -1) return dp[row][col];

     int left = matrix[row][col] + solveLT931UsingMemo(matrix, row - 1, col, dp);
     int down = matrix[row][col] + solveLT931UsingMemo(matrix, row - 1, col - 1, dp);
     int right = matrix[row][col] + solveLT931UsingMemo(matrix, row - 1, col + 1, dp);
     
     return min(down, min(left, right));
}

int solveLT931UsingTabulation(vector<vector<int>>& matrix){
     int rowN = matrix.size();
     int colN = matrix[0].size();
     vector<vector<int>> dp(rowN, vector<int>(colN, -1));

     for(int k = 0; k < colN; k++) {
          dp[0][k] = matrix[0][k];
     }

     for(int row = 1; row < rowN; row++) {
          for(int col = 0; col < colN; col++) {
               int left = matrix[row][col] + dp[row - 1][col];
               int down = (col > 0) ? matrix[row][col] +  dp[row - 1][col - 1] : 1e9;
               int right = (col < colN - 1) ? matrix[row][col] +  dp[row - 1][col + 1] : 1e9;
               dp[row][col] = min(down, min(left, right));
          }
     }

     int mini = 1e9;
     for(int i = 0; i < colN; i++) {
          mini = min(mini, dp[rowN - 1][i]);
     }

     return mini; 
}

int solveLT931UsingSpaceOpt(vector<vector<int>>& matrix){
     int rowN = matrix.size();
     int colN = matrix[0].size();
     vector<int> curr(colN);
     vector<int> prev(colN);

     for(int k = 0; k < colN; k++) {
          prev[k] = matrix[0][k];
     }

     for(int row = 1; row < rowN; row++) {
          for(int col = 0; col < colN; col++) {
               int left = matrix[row][col] + prev[col];
               int down = (col > 0) ? matrix[row][col] + prev[col - 1] : 1e9;
               int right = (col < colN - 1) ? matrix[row][col] + prev[col + 1] : 1e9;
               curr[col] = min(down, min(left, right));
          }
          // Shifting
          prev = curr;
     }

     int mini = 1e9;
     for(int i = 0; i < colN; i++) {
          mini = min(mini, prev[i]);
     }

     return mini; 
}

int minFallingPathSum(vector<vector<int>>& matrix) {
     // int row = matrix.size();
     // int col = matrix[0].size();
     // vector<vector<int>> dp(row, vector<int>(col, -1));
     // int mini = 1e9;
     // for(int i = 0; i <= col; i++) {
     //     mini = min(mini, solveUsingMemo(matrix, row - 1, i, dp));
     // }
     // return mini;
     return solveLT931LT931UsingSpaceOpt(matrix);
}









 





























int main() {
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Output: " << lengthOfLIS_2(nums1) << endl; // Expected: 4

    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Output: " << lengthOfLIS_2(nums2) << endl; // Expected: 4

    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "Output: " << lengthOfLIS_2(nums3) << endl; // Expected: 1

    return 0;
}