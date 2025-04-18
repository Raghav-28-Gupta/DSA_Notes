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





























































