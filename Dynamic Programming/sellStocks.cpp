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



// LEETCODE : 121 (Best Time to Buy and Sell Stock I)
int maxProfitSolverI(vector<int>& prices, int i, int minPrice, int maxProfit) {
     // Base Case
     if(i >= prices.size()) {
         return maxProfit;
     }
     // finding the min stock price 
     minPrice = min(minPrice, prices[i]);
     maxProfit = max(maxProfit, prices[i] - minPrice);

     return maxProfitSolverI(prices, i + 1, minPrice, maxProfit);
}

int maxProfitSolverII(vector<int>& prices) {
     int minPrice = INT_MAX;
     int maxProfit = 0;

     for(auto price : prices) {
         minPrice = min(minPrice, price);
         maxProfit = max(maxProfit, price - minPrice);
     }

     return maxProfit;
}

int maxProfit(vector<int>& prices) {
     return solveLT121UsingRecursion(prices, 0, INT_MAX, 0);
}




// LEETCODE : 122 (Best Time to Buy and Sell Stock II)
int solveLT122UsingRecursion(vector<int>& prices, int index, bool buy) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT122UsingRecursion(prices, index + 1, false);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT122UsingRecursion(prices, index + 1, true);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT122UsingRecursion(prices, index + 1, true);
         // Option 2: Sell on another day
         int skip = 0 + solveLT122UsingRecursion(prices, index + 1, false);
         profit = max(sell, skip);
     }
     
     return profit;
}

int solveLT122UsingMemo(vector<int>& prices, int index, bool buy, vector<vector<int>> &dp) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     if(dp[index][buy] != -1) {
         return dp[index][buy];
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT122UsingMemo(prices, index + 1, false, dp);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT122UsingMemo(prices, index + 1, true, dp);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT122UsingMemo(prices, index + 1, true, dp);
         // Option 2: Sell on another day
         int skip = 0 + solveLT122UsingMemo(prices, index + 1, false, dp);
         profit = max(sell, skip);
     }
     
     return dp[index][buy] = profit;
}

int solveLT122UsingTabulation(vector<int>& prices){
     int n = prices.size();
     vector<vector<int>> dp(n + 1, vector<int>(2, 0));

     // Analyzing Base Case
     dp[n][0] = dp[n][1] = 0;

     for(int index = n - 1; index >= 0; index--) {
         for(int buy = 0; buy <= 1; buy++) {
             int profit = 0;
             if(buy) {
                 // Option 1: Buy the stock and move forward to sell it
                 int take = -prices[index] + dp[index + 1][0];
                 // Option 2: Just skip this one and Buy another one
                 int skip = 0 + dp[index + 1][1];
                 profit = max(take, skip);
             }
             else{
                 // Option 1: Sell on this day and move forward to buy another one
                 int sell = prices[index] + dp[index + 1][1];
                 // Option 2: Sell on another day
                 int skip = 0 + dp[index + 1][0];
                 profit = max(sell, skip);
             }
             
             dp[index][buy] = profit;
         }
     }

     return dp[0][1];
}

// THINK
int solveLT122UsingSpaceOpt(vector<int>& prices){
     int n = prices.size();
     vector<int> curr(2, 0);
     vector<int> prev(2, 0);

     // Analyzing Base Case
     prev[0] = curr[1] = 0;

     for(int index = n - 1; index >= 0; index--) {
         for(int buy = 0; buy <= 1; buy++) {
             int profit = 0;
             if(buy) {
                 // Option 1: Buy the stock and move forward to sell it
                 int take = -prices[index] + prev[0];
                 // Option 2: Just skip this one and Buy another one
                 int skip = 0 + prev[1];
                 profit = max(take, skip);
             }
             else{
                 // Option 1: Sell on this day and move forward to buy another one
                 int sell = prices[index] + prev[1];
                 // Option 2: Sell on another day
                 int skip = 0 + prev[0];
                 profit = max(sell, skip);
             }
             curr[buy] = profit;
         }
         // Shifting
         prev = curr;
     }

     return prev[1];
}

int maxProfit(vector<int>& prices) {
     // bool buy = true;  //Can Buy
     // int n = prices.size();
     // vector<vector<int>> dp(n, vector<int>(2, -1));
     // return solveLT122UsingRecursion(prices, 0, buy); 
     // return solveLT122UsingMemo(prices, 0, buy, dp); 
     // return solveLT122UsingTabulation(prices); 
     return solveLT122UsingSpaceOpt(prices); 
}




// LEETCODE : 123 (Best Time to Buy and Sell Stock III)
int solveLT123UsingRecursion(vector<int>& prices, int index, int buy, int cap) {
     // Base Case
     if(index >= prices.size() || cap == 0) return 0;
     
     int profit = 0;
     if(buy) {
         int take = -prices[index] + solveLT123UsingRecursion(prices, index + 1, 0, cap);
         int skip = 0 + solveLT123UsingRecursion(prices, index + 1, 1, cap);
         profit = max(take, skip);
     }
     else {
         int sell = prices[index] + solveLT123UsingRecursion(prices, index + 1, 1, cap - 1);
         int skip = 0 + solveLT123UsingRecursion(prices, index + 1, 0, cap);
         profit = max(sell, skip);
     }
     
     return profit;
}

int solveLT123UsingMemo(vector<int>& prices, int index, int buy, int cap, vector<vector<vector<int>>> &dp) {
     // Base Case
     if(index >= prices.size() || cap == 0) return 0;
     if(dp[index][buy][cap] != -1) return dp[index][buy][cap];
     
     int profit = 0;
     if(buy) {
         int take = -prices[index] + solveLT123UsingMemo(prices, index + 1, 0, cap, dp);
         int skip = 0 + solveLT123UsingMemo(prices, index + 1, 1, cap, dp);
         profit = max(take, skip);
     }
     else {
         int sell = prices[index] + solveLT123UsingMemo(prices, index + 1, 1, cap - 1, dp);
         int skip = 0 + solveLT123UsingMemo(prices, index + 1, 0, cap, dp);
         profit = max(sell, skip);
     }
     
     return dp[index][buy][cap] = profit;
}

int solveLT123UsingTabulation(vector<int>& prices) {
     int n = prices.size();
     vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (3, 0)));

     for(int index = n - 1; index >= 0; index--){
          for(int buy = 0; buy <= 1; buy ++){
               for(int cap = 1; cap <= 2; cap++){
                    int profit = 0;
                    if(buy) {
                         int take = -prices[index] + dp[index + 1][0][cap];
                         int skip = 0 + dp[index + 1][1][cap];
                         profit = max(take, skip);
                    }
                    else {
                         int sell = prices[index] + dp[index + 1][1][cap - 1];
                         int skip = 0 + dp[index + 1][0][cap];
                         profit = max(sell, skip);
                    }
                    
                    dp[index][buy][cap] = profit;
               }
          }
     }
  
     return dp[0][1][2];
}

int solveLT123UsingSpaceOpt(vector<int>& prices) {
     int n = prices.size();
     vector<vector<int>> curr(2, vector<int> (3, 0));
     vector<vector<int>> prev(2, vector<int> (3, 0));

     for(int index = n - 1; index >= 0; index--){
          for(int buy = 0; buy <= 1; buy ++){
               for(int cap = 1; cap <= 2; cap++){
                    int profit = 0;
                    if(buy) {
                         int take = -prices[index] + prev[0][cap];
                         int skip = 0 + prev[1][cap];
                         profit = max(take, skip);
                    }
                    else {
                         int sell = prices[index] + prev[1][cap - 1];
                         int skip = 0 + prev[0][cap];
                         profit = max(sell, skip);
                    }
                    
                    curr[buy][cap] = profit;
               }
               // Shifting
               prev = curr;
          }
     }
  
     return prev[1][2];
}
 
int maxProfit(vector<int>& prices) {
     // int n = prices.size();
     // int buy = 1;
     // int cap = 2;
     // vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3, -1)));
     // return solveLT123UsingRecursion(prices, 0, buy, cap);
     // return solveLT123UsingMemo(prices, 0, buy, cap, dp);
     // return solveLT123UsingTabulation(prices);
     return solveLT123UsingSpaceOpt(prices);
}




// LEETCODE : 188 (Best Time to Buy and Sell Stock IV)
int solveLT188UsingRecursion(vector<int>& prices, int index, int buy, int cap) {
     // Base Case
     if(index >= prices.size() || cap == 0) return 0;
     
     int profit = 0;
     if(buy) {
         int take = -prices[index] + solveLT188UsingRecursion(prices, index + 1, 0, cap);
         int skip = 0 + solveLT188UsingRecursion(prices, index + 1, 1, cap);
         profit = max(take, skip);
     }
     else {
         int sell = prices[index] + solveLT188UsingRecursion(prices, index + 1, 1, cap - 1);
         int skip = 0 + solveLT188UsingRecursion(prices, index + 1, 0, cap);
         profit = max(sell, skip);
     }
     
     return profit;
}

int solveLT188UsingMemo(vector<int>& prices, int index, int buy, int cap, vector<vector<vector<int>>> &dp) {
     // Base Case
     if(index >= prices.size() || cap == 0) return 0;
     if(dp[index][buy][cap] != -1) return dp[index][buy][cap];
     
     int profit = 0;
     if(buy) {
         int take = -prices[index] + solveLT188UsingMemo(prices, index + 1, 0, cap, dp);
         int skip = 0 + solveLT188UsingMemo(prices, index + 1, 1, cap, dp);
         profit = max(take, skip);
     }
     else {
         int sell = prices[index] + solveLT188UsingMemo(prices, index + 1, 1, cap - 1, dp);
         int skip = 0 + solveLT188UsingMemo(prices, index + 1, 0, cap, dp);
         profit = max(sell, skip);
     }
     
     return dp[index][buy][cap] = profit;
}

int solveLT188UsingTabulation(vector<int>& prices, int k) {
     int n = prices.size();
     vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (k + 1, 0)));

     for(int index = n - 1; index >= 0; index--){
          for(int buy = 0; buy <= 1; buy ++){
               for(int cap = 1; cap <= k; cap++){
                    int profit = 0;
                    if(buy) {
                         int take = -prices[index] + dp[index + 1][0][cap];
                         int skip = 0 + dp[index + 1][1][cap];
                         profit = max(take, skip);
                    }
                    else {
                         int sell = prices[index] + dp[index + 1][1][cap - 1];
                         int skip = 0 + dp[index + 1][0][cap];
                         profit = max(sell, skip);
                    }
                    
                    dp[index][buy][cap] = profit;
               }
          }
     }
  
     return dp[0][1][k];
}

int solveLT188UsingSpaceOpt(vector<int>& prices, int k) {
     int n = prices.size();
     vector<vector<int>> curr(2, vector<int> (k + 1, 0));
     vector<vector<int>> prev(2, vector<int> (k + 1, 0));

     for(int index = n - 1; index >= 0; index--){
          for(int buy = 0; buy <= 1; buy ++){
               for(int cap = 1; cap <= k; cap++){
                    int profit = 0;
                    if(buy) {
                         int take = -prices[index] + prev[0][cap];
                         int skip = 0 + prev[1][cap];
                         profit = max(take, skip);
                    }
                    else {
                         int sell = prices[index] + prev[1][cap - 1];
                         int skip = 0 + prev[0][cap];
                         profit = max(sell, skip);
                    }
                    
                    curr[buy][cap] = profit;
               }
               // Shifting
               prev = curr;
          }
     }
  
     return prev[1][k];
}

int maxProfit(int k, vector<int>& prices) {
     // int n = prices.size();
     // int buy = 1;
     // vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k + 1, -1)));
     // return solveLT188UsingRecursion(prices, 0, buy, k);
     // return solveLT188UsingMemo(prices, 0, buy, k, dp);
     // return solveLT188UsingTabulation(prices, k);
     return solveLT188UsingSpaceOpt(prices, k);
}




// LEETCODE : 309 (Best Time to Buy and Sell Stock with Cooldown)
int solveLT309UsingRecursion(vector<int>& prices, int index, bool buy) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT309UsingRecursion(prices, index + 1, false);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT309UsingRecursion(prices, index + 1, true);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT309UsingRecursion(prices, index + 2, true);
         // Option 2: Sell on another day
         int skip = 0 + solveLT309UsingRecursion(prices, index + 1, false);
         profit = max(sell, skip);
     }
     
     return profit;
}

int solveLT309UsingMemo(vector<int>& prices, int index, bool buy, vector<vector<int>> &dp) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     if(dp[index][buy] != -1) {
         return dp[index][buy];
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT309UsingMemo(prices, index + 1, false, dp);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT309UsingMemo(prices, index + 1, true, dp);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT309UsingMemo(prices, index + 2, true, dp);
         // Option 2: Sell on another day
         int skip = 0 + solveLT309UsingMemo(prices, index + 1, false, dp);
         profit = max(sell, skip);
     }
     
     return dp[index][buy] = profit;
}

int solveLT309UsingTabulation(vector<int>& prices){
     int n = prices.size();
     vector<vector<int>> dp(n + 2, vector<int>(2, 0));

     // Analyzing Base Case
     dp[n][0] = dp[n][1] = 0;

     for(int index = n - 1; index >= 0; index--) {
          for(int buy = 0; buy <= 1; buy++) {
               int profit = 0;
               if(buy) {
                    // Option 1: Buy the stock and move forward to sell it
                    int take = -prices[index] + dp[index + 1][0];
                    // Option 2: Just skip this one and Buy another one
                    int skip = 0 + dp[index + 1][1];
                    profit = max(take, skip);
               }
               else{
                    // Option 1: Sell on this day and move forward to buy another one
                    int sell = prices[index] + dp[index + 2][1];
                    // Option 2: Sell on another day
                    int skip = 0 + dp[index + 1][0];
                    profit = max(sell, skip);
               }
               
               dp[index][buy] = profit;
          }
     }

     return dp[0][1];
}

// THINK!!!
int solveLT309UsingSpaceOpt(vector<int>& prices){
     int n = prices.size();
     vector<int> curr(2, 0);
     vector<int> prev(2, 0);
     vector<int> prev2(2, 0);   //To Handle (index + 2) case

     // Analyzing Base Case
     prev[0] = curr[1] = 0;

     for(int index = n - 1; index >= 0; index--) {
          for(int buy = 0; buy <= 1; buy++) {
               int profit = 0;
               if(buy) {
                    // Option 1: Buy the stock and move forward to sell it
                    int take = -prices[index] + prev[0];
                    // Option 2: Just skip this one and Buy another one
                    int skip = 0 + prev[1];
                    profit = max(take, skip);
               }
               else{
                    // Option 1: Sell on this day and apply cooldown (move `index + 2`)
                    int sell = prices[index] + prev2[1];
                    // Option 2: Sell on another day
                    int skip = 0 + prev[0];
                    profit = max(sell, skip);
               }
               curr[buy] = profit;
          }
          // Shift `prev2` -> `prev`, `prev` -> `curr`
          prev2 = prev;
          prev = curr;
     }

     return prev[1];
}

int maxProfit(vector<int>& prices) {
     // bool buy = true;  //Can Buy
     // int n = prices.size();
     // vector<vector<int>> dp(n, vector<int>(2, -1));
     // return solveLT309UsingRecursion(prices, 0, buy); 
     // return solveLT309UsingMemo(prices, 0, buy, dp); 
     // return solveLT309UsingTabulation(prices); 
     return solveLT309UsingSpaceOpt(prices); 
}




// LEETCODE : 714 (Best Time to Buy and Sell Stock with Transaction Fee)
int solveLT714UsingRecursion(vector<int>& prices, int index, bool buy, int fee) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT714UsingRecursion(prices, index + 1, false, fee);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT714UsingRecursion(prices, index + 1, true, fee);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT714UsingRecursion(prices, index + 1, true, fee) - fee;
         // Option 2: Sell on another day
         int skip = 0 + solveLT714UsingRecursion(prices, index + 1, false, fee);
         profit = max(sell, skip);
     }
     
     return profit;
}

int solveLT714UsingMemo(vector<int>& prices, int index, bool buy, vector<vector<int>> &dp, int fee) {
     // Base Case
     if(index >= prices.size()) {
         return 0;
     }

     if(dp[index][buy] != -1) {
         return dp[index][buy];
     }

     int profit = 0;
     if(buy) {
         // Option 1: Buy the stock and move forward to sell it
         int take = -prices[index] + solveLT714UsingMemo(prices, index + 1, false, dp, fee);
         // Option 2: Just skip this one and Buy another one
         int skip = 0 + solveLT714UsingMemo(prices, index + 1, true, dp, fee);
         profit = max(take, skip);
     }
     else{
         // Option 1: Sell on this day and move forward to buy another one
         int sell = prices[index] + solveLT714UsingMemo(prices, index + 1, true, dp, fee) - fee;
         // Option 2: Sell on another day
         int skip = 0 + solveLT714UsingMemo(prices, index + 1, false, dp, fee);
         profit = max(sell, skip);
     }
     
     return dp[index][buy] = profit;
}

int solveLT714UsingTabulation(vector<int>& prices, int fee){
     int n = prices.size();
     vector<vector<int>> dp(n + 1, vector<int>(2, 0));

     // Analyzing Base Case
     dp[n][0] = dp[n][1] = 0;

     for(int index = n - 1; index >= 0; index--) {
          for(int buy = 0; buy <= 1; buy++) {
               int profit = 0;
               if(buy) {
                    // Option 1: Buy the stock and move forward to sell it
                    int take = -prices[index] + dp[index + 1][0];
                    // Option 2: Just skip this one and Buy another one
                    int skip = 0 + dp[index + 1][1];
                    profit = max(take, skip);
               }
               else{
                    // Option 1: Sell on this day and move forward to buy another one
                    int sell = prices[index] + dp[index + 1][1] - fee;
                    // Option 2: Sell on another day
                    int skip = 0 + dp[index + 1][0];
                    profit = max(sell, skip);
               }
               
               dp[index][buy] = profit;
          }
     }

     return dp[0][1];
}

int solveLT714UsingSpaceOpt(vector<int>& prices, int fee){
     int n = prices.size();
     vector<int> curr(2, 0);
     vector<int> prev(2, 0);

     // Analyzing Base Case
     prev[0] = curr[1] = 0;

     for(int index = n - 1; index >= 0; index--) {
          for(int buy = 0; buy <= 1; buy++) {
               int profit = 0;
               if(buy) {
                    // Option 1: Buy the stock and move forward to sell it
                    int take = -prices[index] + prev[0];
                    // Option 2: Just skip this one and Buy another one
                    int skip = 0 + prev[1];
                    profit = max(take, skip);
               }
               else{
                    // Option 1: Sell on this day and move forward to buy another one
                    int sell = prices[index] + prev[1] - fee;
                    // Option 2: Sell on another day
                    int skip = 0 + prev[0];
                    profit = max(sell, skip);
               }
               curr[buy] = profit;
          }
          // Shifting
          prev = curr;
     }

     return prev[1];
}

int maxProfit(vector<int>& prices, int fee) {
     // bool buy = true;  //Can Buy
     // int n = prices.size();
     // vector<vector<int>> dp(n, vector<int>(2, -1));
     // return solveLT714UsingRecursion(prices, 0, buy, fee); 
     // return solveLT714UsingMemo(prices, 0, buy, dp, fee); 
     // return solveLT714UsingTabulation(prices, fee); 
     return solveLT714UsingSpaceOpt(prices, fee);
}