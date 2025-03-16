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


// LEETCODE : 1463 (Cherry Pickup II)
int solveUsingRec(vector<vector<int>>& grid, int n, int m, int i, int j1, int j2) {
     // Base Case
     if(j1 < 0 || j2 < 0 || j1 > m-1 || j2 > m-1){
          return -1e9;
     }
     if(i == n-1) {
          if(j1 == j2) return grid[i][j1]; //Any one only
          else return grid[i][j1] + grid[i][j2];
     }

     // All Possible pathways
     int maxi = -1e9;
     for(int dj1 = -1; dj1 < 2; dj1++){
          for(int dj2 = -1; dj2 < 2; dj2++) {
               int value = 0;

               if(j1 == j2) value = grid[i][j1]; //Any one only
               else value = grid[i][j1] + grid[i][j2];
               
               value += solveUsingRec(grid, n, m, i + 1, j1 + dj1, j2 + dj2);
               maxi = max(maxi, value);
          }
     }
     
     return maxi;
}

int solveUsingMemo(vector<vector<int>>& grid, int n, int m, int i, int j1, int j2, vector<vector<vector<int>>>& dp) {

     // Base Case
     if(j1 < 0 || j2 < 0 || j1 > m-1 || j2 > m-1){
          return -1e9;
     }
     if(i == n-1) {
          if(j1 == j2) return grid[i][j1]; //Any one only
          else return grid[i][j1] + grid[i][j2];
     }
     if(dp[i][j1][j2] != -1) return dp[i][j1][j2];

     // All Possible pathways
     int maxi = -1e9;
     for(int dj1 = -1; dj1 < 2; dj1++){
          for(int dj2 = -1; dj2 < 2; dj2++) {
               int value = 0;

               if(j1 == j2) value = grid[i][j1]; //Any one only
               else value = grid[i][j1] + grid[i][j2];
               
               value += solveUsingMemo(grid, n, m, i + 1, j1 + dj1, j2 + dj2, dp);
               maxi = max(maxi, value);
          }
     }
     
     return dp[i][j1][j2] = maxi;
}

int solveUsingTabulation(vector<vector<int>>& grid){
     int n = grid.size();
     int m = grid[0].size();
     vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
     
     for(int j1 = 0; j1 < m; j1++) {
          for(int j2 = 0; j2 < m; j2++) {
               if(j1 == j2) dp[n-1][j1][j2] = grid[n-1][j1];
               else dp[n-1][j1][j2] = grid[n-1][j1] + grid[n-1][j2];
          }
     }

     for(int i = n-2; i >= 0; i--) {
          for(int j1 = 0; j1 < m; j1++) {
               for(int j2 = 0; j2 < m; j2++) {
               int maxi = -1e9;
               for(int dj1 = -1; dj1 < 2; dj1++){
                    for(int dj2 = -1; dj2 < 2; dj2++) {
                         int value = 0;

                         if(j1 == j2) value = grid[i][j1]; //Any one only
                         else value = grid[i][j1] + grid[i][j2];
                         
                         if(j1 + dj1 >= 0 && j1 + dj1 < m && j2 + dj2 >= 0 && j2 + dj2 < m){
                              value += dp[i + 1][j1 + dj1][j2 + dj2];
                         }
                         else {
                              value += -1e9;
                         }
                         
                         maxi = max(maxi, value);
                    }
               }
               dp[i][j1][j2] = maxi;
               }
          }
     }
     
     return dp[0][0][m-1];
}

int solveUsingSpaceOpt(vector<vector<int>>& grid) {
     int n = grid.size();
     int m = grid[0].size();
     vector<vector<int>> curr(m, vector<int>(m));
     vector<vector<int>> prev(m, vector<int>(m));
     
     for(int j1 = 0; j1 < m; j1++) {
          for(int j2 = 0; j2 < m; j2++) {
               if(j1 == j2) prev[j1][j2] = grid[n-1][j1];
               else prev[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
          }
     }

     for(int i = n-2; i >= 0; i--) {
          for(int j1 = 0; j1 < m; j1++) {
               for(int j2 = 0; j2 < m; j2++) {
               int maxi = -1e9;
               for(int dj1 = -1; dj1 < 2; dj1++){
                    for(int dj2 = -1; dj2 < 2; dj2++) {
                         int value = 0;

                         if(j1 == j2) value = grid[i][j1]; //Any one only
                         else value = grid[i][j1] + grid[i][j2];
                         
                         if(j1 + dj1 >= 0 && j1 + dj1 < m && j2 + dj2 >= 0 && j2 + dj2 < m){
                              value += prev[j1 + dj1][j2 + dj2];
                         }
                         else {
                              value += -1e9;
                         }
                         
                         maxi = max(maxi, value);
                    }
               }
               curr[j1][j2] = maxi;
               }
          }
          // Shifting 
          prev = curr;
     }
     
     return prev[0][m-1];


}


int cherryPickup(vector<vector<int>>& grid) {
     // int n = grid.size();
     // int m = grid[0].size();
     // vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
     // return solveUsingMemo(grid, n, m, 0, 0, m - 1, dp);

     return solveUsingSpaceOpt(grid);
}