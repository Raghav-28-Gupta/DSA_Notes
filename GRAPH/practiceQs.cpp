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


// LEETCODE : 200 (Number of Islands)
void numIslandsUsingDFS(vector<vector<char>>& grid, int i, int j){
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Base case: out of bounds or water ('0')
    if(i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == '0') {
        return;
    }

    // Mark the cell as visited by setting it to '0'
    grid[i][j] = '0';

    numIslandsUsingDFS(grid, i, j + 1);   //Right
    numIslandsUsingDFS(grid, i + 1, j);   //UP
    numIslandsUsingDFS(grid, i, j - 1);   //Left
    numIslandsUsingDFS(grid, i - 1, j);   //Down
}

int numIslands(vector<vector<char>>& grid) {
    if(grid.empty()) {
        return 0;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    int islandCount = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] == '1') {
                
                numIslandsUsingDFS(grid, i, j);
                islandCount++;
            }
        }
    }

    return islandCount;
}




// LEECODE : 994 (Rotting Oranges)
void orangesRottingDFS(vector<vector<int>>& grid, int i, int j, int time) {
    int rows = grid.size();
    int cols = grid[0].size();

    if(i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == 0) {
        return;
    }
    
    // if orange is Fresh and Rottable
    if(grid[i][j] > 1 && grid[i][j] < time) return;

    grid[i][j] = time; // Mark the time it took to rot this orange

    orangesRottingDFS(grid, i, j + 1, time + 1);   //Right
    orangesRottingDFS(grid, i + 1, j, time + 1);   //UP
    orangesRottingDFS(grid, i, j - 1, time + 1);   //Left
    orangesRottingDFS(grid, i - 1, j, time + 1);   //Down
}
// THINK !!!
int orangesRottingBFS(vector<vector<int>>& grid){
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int, int>> q;
    int freshCount = 0, minutes = 0;
    
    // Directions for 4-directional movement
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++){
            if(grid[r][c] == 2) {
                q.push({r, c}); //Store the position of rotten oranges
            }
            else if(grid[r][c] == 1) {
                freshCount++;
            }
        }
    }

    if(freshCount == 0) return 0;

    while(!q.empty()) {
        int size = q.size();
        bool rotten = false;   // Flag to check if at least one fresh orange got rotten this round

        for(int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            for(auto [dx, dy] : directions) {
                int newX = x + dx, newY = y + dy;
                
                // Check if the new position is within bounds and has a fresh orange
                if(newX >= 0 && newY >= 0 && newX < rows && newY < cols && grid[newX][newY] == 1) {
                    grid[newX][newY] = 2;
                    freshCount--;
                    q.push({newX, newY});
                    rotten = true;
                } 
            }
        }
        
        if(rotten) minutes++;
    }

return (freshCount == 0) ? minutes : -1;
}

int orangesRotting(vector<vector<int>>& grid) {
    if(grid.empty()) return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    int maxTime = 2;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] == 2) {
                orangesRottingDFS(grid, i, j, 2);
            }
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] == 1) return -1;
            maxTime = max(maxTime, grid[i][j]);
        }
    }

    return maxTime - 2;
    
    // return orangesRottingBFS(grid);
}




// GFG : Shortest Path in Undirected
vector<int> shortestPath(vector<vector<int>>& adj, int src) {
    // code here
    int n = adj.size();
    vector<int> dist(n, -1); // Initialize all distances as -1 (unreachable)
    
    queue<int> q;
    q.push(src);
    dist[src] = 0; // Distance to source is 0
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Process all adjacent nodes
        for (int neighbor : adj[node]) {
            // If this node hasn't been visited yet
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1; // Update distance : shortest path to predecessor plus one edge.
                q.push(neighbor);
            }
        }
    }
    
    return dist;
}



// GFG : Shortest path in Directed Acyclic Graph
void topDfs(int src, vector<pair<int, int>> adj[], unordered_map<int, bool> &vis, stack<int> &st){
        vis[src] = true;
        
        for(auto nbr: adj[src]) {
            int node = nbr.first;
            if(!vis[node]) {
                topDfs(node, adj, vis, st);
            }
        }
        
        // backtracking 
        st.push(src);
    }
  
vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
    // code here

    // First Build Adjacency List
    vector<pair<int, int>> adj[V];
    for(auto edge: edges){
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    // Topological Sort
    stack<int> st;
    unordered_map<int, bool> vis;
    for(int i = 0; i < V; i++) {
        if(!vis[i]) {
            topDfs(i, adj, vis, st);
        }
    }

    // Initialize Distances
    vector<int> dist(V, INT_MAX);
    dist[0] = 0;

    // Main Logic
    while(!st.empty()) {
        int topNode = st.top();
        st.pop();
        
        // Check if dist[topNode] holds a valid distance value
        if(dist[topNode] != INT_MAX) {
            for(auto nbr: adj[topNode]) {
                int node = nbr.first;
                int weight = nbr.second;
                dist[node] = min(dist[node], dist[topNode] + weight);
            }
        }
        
    }

    // Convert Infinity to -1
    for(int i = 0; i < V; i++){
        if(dist[i] == INT_MAX) {
            dist[i] = -1;
        }
    }

    return dist;
}




















