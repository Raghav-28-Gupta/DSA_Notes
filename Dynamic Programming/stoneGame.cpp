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




// LEETCODE : 1140 (Stone Game II)
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