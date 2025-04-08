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
    // Base case: out of bounds or water ('0')
    if(i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == '0') {
        return;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    
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
        // edge[0] -> source vertex
        // edge[1] -> destination vertex
        // edge[2] -> weight of the current edge.
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    // Topological Sort
    stack<int> st;
    unordered_map<int, bool> vis;
    for(int i = 0; i < V; i++) {  //For disconnected components
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



// GFG : Dijkstra Algorithm
vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) {
    // Code here
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    set<pair<int, int>> st;
    
    dist[src] = 0;
    st.insert({0, src});
    
    // Main Logic
    while(!st.empty()) {
        auto topElement = *(st.begin());
        int topNode = topElement.second;
        int topDist = topElement.first;
        
        // Pop this node
        st.erase(st.begin());
        
        for(auto nbr: adj[topNode]) {
            // nbr -> Pair{node, weight}
            int nbrNode = nbr.first;
            int nbrWeight = nbr.second;
            
            if(dist[topNode] + nbrWeight < dist[nbrNode]) {
                //1. update the set
                auto result = st.find({dist[nbrNode], nbrNode});
                if(result != st.end()){
                    // remove this entry
                    st.erase(result);
                }
                
                // DON'T Forget!!!
                //2. update the dist
                dist[nbrNode] = dist[topNode] + nbrWeight;
                st.insert({dist[nbrNode], nbrNode});
            }
        }
        
    }
    
    return dist;
}



// GFG : Bellman-Ford
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    // Code here
    vector<int> dist(V, 1e8);      //used 1e8 instead of 1e9(1 billion) as a large value to represent infinity
    dist[src] = 0;                 //as it caused an integer overflow during the addition of edge weights
    
    for(int i = 0; i < V - 1; i++){
        for(auto nbr: edges) {
            int node = nbr[0];
            int destination = nbr[1];
            int weight = nbr[2];
            if(dist[node] != 1e8 && dist[node] + weight < dist[destination]) {
                dist[destination] = dist[node] + weight;
            }
        }
    }
    
    // Check for Negative Cycles
    for(auto nbr: edges) {
            int node = nbr[0];
            int destination = nbr[1];
            int weight = nbr[2];
            if(dist[node] != 1e8 && dist[node] + weight < dist[destination]) {
                return{-1}; //Negative Cycle Present
            }
        }
    
    return dist;
}

 

// GFG : Floyd-Warshall Algorithm (shortest distances between every pair of vertices)
void FloydWarshall(vector<vector<int>>& matrix) {
    // Code here
    int V = matrix.size();
    
    // Convert -1 to infinity
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 1e9; 
            }
        }
    }
    
    // Floyd-Warshall algorithm : using Helper Node
    for (int helper = 0; helper < V; ++helper) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                matrix[i][j] = min(matrix[i][j], matrix[i][helper] + matrix[helper][j]);
            }
        }
    }
    
    // Convert infinity back to -1 for unreachable vertices
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] == 1e9) {
                matrix[i][j] = -1;
            }
        }
    }
}



// GFG : Kosaraju Algorithm (Strongly Connected Components [SCC])
void topDfs(int src, vector<vector<int>> &adj, unordered_map<int, bool> &vis, stack<int> &st){
    vis[src] = true;
    
    for(auto nbr : adj[src]) {
        if(!vis[nbr]) {
            topDfs(nbr, adj, vis, st);
        }
    }
    
    // backtracking
    st.push(src);
}

void topDfsNew(int src, unordered_map<int, list<int>> &adjNew, unordered_map<int, bool> &visited){
    visited[src] = true;
    
    for(auto nbr : adjNew[src]) {
        if(!visited[nbr]) {
            topDfsNew(nbr, adjNew, visited);
        }
    }
}

int kosaraju(vector<vector<int>> &adj) {
    // code here
    int V = adj.size();
    stack<int> st;
    unordered_map<int, bool> vis;
    
    // Step 1 : Topological Sort
    for(int i = 0; i < V; i++) {
        if(!vis[i]){
            topDfs(i, adj, vis, st);
        }
    }
    // stack is ready
    
    
    // Step 2: Transpose Graph
    unordered_map<int, list<int>> adjNew;
    for(int i = 0; i < V; i++) {
        for(auto nbr : adj[i]) {
            // nbr -> children of i node
            int node = nbr;
            // Reversing edges ensures that SCCs now form self-contained groups
            adjNew[node].push_back(i);
        }
    }
    
    
    // Traversal
    int count = 0;
    unordered_map<int, bool> visited;
    while(!st.empty()) {
        int topNode = st.top();
        st.pop();
        
        if(!visited[topNode]){
            topDfsNew(topNode, adjNew, visited);
            // One whole component is traversed 
            count++;
        }
    }
    
    return count;
}



// GFG : Prim's Algorithm (Minimum Spanning Tree)
int spanningTree(int V, vector<vector<int>> adj[]) {
    // code here
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    unordered_map<int, bool> vis;
    
    for(int i = 0; i < V; i++){
        vis[i] = false;
    }
    
    // Initial State
    minHeap.push({0, 0});
    int sumWeigth = 0;
    
    while(!minHeap.empty()){
        auto current = minHeap.top();
        minHeap.pop();
        
        int weight = current.first;
        int node = current.second;
        
        // Already the part of MST
        if(vis[node]) continue;
        
        vis[node] = true;
        sumWeigth += weight;
        
        for(auto &edge : adj[node]){
            int nbr = edge[0];
            int nbrWt = edge[1];
            if(!vis[nbr]) {
                minHeap.push({nbrWt, nbr});
            }
        }
    }
    
    return sumWeigth;
}



