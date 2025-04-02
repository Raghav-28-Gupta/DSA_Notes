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


// GFG : Bridge edge in a graph
void isBridgeDfs(int src, int parent, vector<int> adj[], vector<int> &tin, vector<int> &low, unordered_map<int, bool> &vis, int &isBridge, int &timer, int c, int d){
     timer++;
     vis[src] = true;
     tin[src] = timer;
     low[src] = timer;
     
     for(auto nbr: adj[src]) {
          if(nbr == parent) continue;  // Ignore parent edge
          
          if(!vis[nbr]) {
               isBridgeDfs(nbr, src, adj, tin, low, vis, isBridge, timer, c, d);
               
               // Update low value after returning from recursion
               low[src] = min(low[src], low[nbr]);
               
               // Check if (node, neighbor) is a bridge
               if(low[nbr] > tin[src]) {
                    if((nbr == c && src == d) || (nbr == d && src == c)) {
                         isBridge = 1;
                    }
               }
          }
          
          else{
               // Back edge case
               low[src] = min(low[src], tin[nbr]);
          }
     }
     
 }
 
int isBridge(int V, vector<int> adj[], int c, int d) {
     // Code here
     vector<int> tin(V);
     vector<int> low(V);
     int timer = 0;
     unordered_map<int, bool> vis;
     int isBridge = 0;
     
     for(int i = 0; i < V; i++){
          if(!vis[i]) {
               isBridgeDfs(i, -1, adj, tin, low, vis, isBridge, timer, c, d);
          }
     }
     
     return isBridge;
}




// LEETCODE : 1192 (Critical Connections in a Network)
void criticalConnectionsDfs(int src, int parent, vector<vector<int>>& connections, unordered_map<int, bool> &vis, int &timer,
     vector<int> &low, vector<int> &tin, vector<vector<int>> &ans){

     timer++;
     vis[src] = true;
     low[src] = tin[src] = timer;

     for(auto nbr: connections[src]) {
          if(nbr == parent) continue;

          if(!vis[nbr]) {
               criticalConnectionsDfs(nbr, src, connections, vis, timer, low, tin, ans);

               low[src] = min(low[src], low[nbr]);

               // Check for the bridge
               if(low[nbr] > tin[src]){
                    vector<int> temp;
                    temp.push_back(src);
                    temp.push_back(nbr);
                    ans.push_back(temp);
               }
          }

          else{
               // Back edge case
               low[src] = min(low[src], tin[nbr]);
          }
     }
}
 
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
     unordered_map<int, bool> vis;
     vector<int> low(n);
     vector<int> tin(n);
     int timer = 0;

     vector<vector<int>> ans;

     // Build Adjacency list
     vector<vector<int>> adj(n);
     for(auto nbr: connections) {
          adj[nbr[0]].push_back(nbr[1]);
          adj[nbr[1]].push_back(nbr[0]);
     }

     for(int i = 0; i < n; i++) {
          if(!vis[i]){
               criticalConnectionsDfs(i, -1, adj, vis, timer, low, tin, ans);
          }
     }

     return ans;
}


 












