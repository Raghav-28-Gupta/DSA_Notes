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



// LEETCODE : 547 (Number of Provinces)    &&    GFG : Number of Provinces
void isConnectedBfs(vector<vector<int>>& adjList, unordered_map<int, bool> &vis, int src){
     queue<int> q;
     q.push(src);
     vis[src] = true;
     
     while(!q.empty()) {
          int node = q.front();
          q.pop();
          
          for(auto nbr : adjList[node]) {
               if(!vis[nbr]){
                    q.push(nbr);
                    vis[nbr] = true;
               }
          }
     }
 }

int findCircleNum(vector<vector<int>>& isConnected) {
     int V = isConnected.size();
     
     // build Ajacency List
     vector<vector<int>> adjList(V);
     for(int i = 0; i < V; i++) {
          for(int j = 0; j < V; j++) {
               if(isConnected[i][j] == 1 && i != j){
                    adjList[i].push_back(j);
               }
          }
     }
     
     unordered_map<int, bool> vis;
     int count = 0;
     for(int i = 0; i < V; i++) {
          if(!vis[i]){
               count++;
               isConnectedBfs(adjList, vis, i);
          }
     }

     return count;
}

// GFG
void numProvincesDfs(vector<vector<int>> &adjList, int V, unordered_map<int, bool> &vis, int src){
     vis[src] = true;
     for(auto nbr : adjList[src]) {
         if(!vis[nbr]) {
             numProvincesDfs(adjList, V, vis, nbr);
         }
     }
}

int numProvinces(vector<vector<int>> adj, int V) {
     vector<vector<int>> adjList(V);
     for(int i = 0 ; i < V; i++) {
         for(int j = 0; j < V; j++) {
             if(adj[i][j] == 1 && i != j) {
                 adjList[i].push_back(j);
             }
         }
     }
     
     unordered_map<int, bool> vis;
     int count = 0;
     for(int i = 0; i < V; i++) {
         if(!vis[i]) {
             count++;
             numProvincesDfs(adjList, V, vis, i);
         }
     }
     
     return count;
}




// LEETCODE : 200 (Number of Islands) 
void numIslandsUsingDFS(vector<vector<char>>& grid, int i, int j){
     int rows = grid.size();
     int cols = grid[0].size();

     if(i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == '0') {
         return;
     }

     grid[i][j] = '0';
     numIslandsUsingDFS(grid, i, j + 1);   //Right
     numIslandsUsingDFS(grid, i + 1, j);   //UP
     numIslandsUsingDFS(grid, i, j - 1);   //Left
     numIslandsUsingDFS(grid, i - 1, j);   //Down
}
 
void numIslandsUsingBFS(vector<vector<char>>& grid, vector<vector<int>> &vis, int row, int col) {
     int n = grid.size();
     int m = grid[0].size();

     vis[row][col] = 1;
     queue<pair<int, int>> q;
     q.push({row, col});

     vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

     while(!q.empty()) {
         int row = q.front().first;
         int col = q.front().second;
         q.pop();

         for(auto [dx, dy] : dir) {
             int newRow = row + dx;
             int newCol = col + dy;
             if(newRow >= 0 && newRow < n && newCol >= 0 && newCol < m && 
                 grid[newRow][newCol] == '1' && !vis[newRow][newCol]) {
                 q.push({newRow, newCol});
                 vis[newRow][newCol] = 1;
             }
         }
     }
}

int numIslands(vector<vector<char>>& grid) {
     if(grid.empty()) {
         return 0;
     }
     int rows = grid.size();
     int cols = grid[0].size();
     
     vector<vector<int>> vis(rows, vector<int> (cols, 0));
     int islandCount = 0;
     for(int i = 0; i < rows; i++) {
         for(int j = 0; j < cols; j++) {
             if(grid[i][j] == '1' && !vis[i][j]) {
                 islandCount++;
                 numIslandsUsingBFS(grid, vis, i, j);
             }
         }
     }

     return islandCount;
}























































