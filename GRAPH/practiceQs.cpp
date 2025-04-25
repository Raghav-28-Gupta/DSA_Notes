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




// GFG : Rotten Oranges
int orangesRottingBFS(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    
    queue<pair<pair<int, int>, int>> q;    // {{row, col}, time}
    int vis[n][m];  //Copy of 'mat' to avoid altering org data
    
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    int cntFresh = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            if(mat[i][j] == 2){
                vis[i][j] = 2;
                q.push({{i, j}, 0});
            }
            else{
                vis[i][j] = 0;
            }
            
            if(mat[i][j] == 1) cntFresh++;
        }
    }
    
    int count = 0;
    int time = 0;   //starting time of the oranges in the queue
    while(!q.empty()){
        int row = q.front().first.first;
        int col = q.front().first.second;
        int tm = q.front().second;
        q.pop();
        
        time = max(time, tm);  // Keep track of the maximum time
        
        for(auto move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;
            if(newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
                vis[newRow][newCol] == 0 && mat[newRow][newCol] == 1){
                    q.push({{newRow, newCol}, tm + 1});
                    vis[newRow][newCol] = 2;
                    count++;
            }
        }
        
    }
    
    if(count != cntFresh) return -1;
    
    return time;
}




// GFG : Distance of nearest cell having 1
vector<vector<int>> nearest(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    vector<vector<int>> vis(n, vector<int> (m, 0));   //Making a duplicated visited grid to retain org data
    vector<vector<int>> dist(n, vector<int> (m, 0));
    queue<pair<pair<int, int>, int>> q;
    
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
     
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 1) {
                q.push({{i, j}, 0});
                vis[i][j] = 1;
            }
        }
    }
    
    while(!q.empty()) {
        int row = q.front().first.first;
        int col = q.front().first.second;
        int steps = q.front().second;
        q.pop();  
        
        // IMPORTANT
        dist[row][col] = steps;
        
        for(auto move : moves) {
            int nrow = row + move.first;
            int ncol = col + move.second;
            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
               vis[nrow][ncol] == 0) {
                   q.push({{nrow, ncol}, steps + 1});
                   vis[nrow][ncol] = 1;     //Mark as visited
            }
        }
        
    }
    
    return dist;
}




// GFG : Replace O's with X's
void fillDfs(int row, int col, vector<vector<int>> &vis, vector<pair<int, int>> &steps, vector<vector<char>>& mat) {
    vis[row][col] = 1;  

    int n = mat.size();
    int m = mat[0].size();

    for (auto step : steps) {
        int nrow = row + step.first;
        int ncol = col + step.second;
        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
            mat[nrow][ncol] == 'O' && vis[nrow][ncol] == 0) {
            fillDfs(nrow, ncol, vis, steps, mat);
        }
    }
}
vector<vector<char>> fill(vector<vector<char>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    vector<pair<int, int>> steps = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<int>> vis(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {  
        // First Column
        if (mat[i][0] == 'O' && vis[i][0] == 0) {
            fillDfs(i, 0, vis, steps, mat);
        }
        // Last Column
        if (mat[i][m - 1] == 'O' && vis[i][m - 1] == 0) {
            fillDfs(i, m - 1, vis, steps, mat);
        }
    }

    for (int i = 0; i < m; i++) {  
        // First Row
        if (mat[0][i] == 'O' && vis[0][i] == 0) {
            fillDfs(0, i, vis, steps, mat);
        }
        // Last Row
        if (mat[n - 1][i] == 'O' && vis[n - 1][i] == 0) {
            fillDfs(n - 1, i, vis, steps, mat);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int l = 0; l < m; l++) {
            if (mat[k][l] == 'O' && vis[k][l] == 0) {
                mat[k][l] = 'X';  
            }
        }
    }

    return mat;
}

// LEETCODE : 130 (Surrounded Regions)
void solve(vector<vector<char>>& board) {
    int n = board.size();
    int m = board[0].size();
    if(n == 0) return;

    vector<vector<int>> vis(n, vector<int>(m, 0));
    queue<pair<int, int>> q;

    vector<pair<int, int>> steps = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(int i = 0; i < m; i++) {
        // first row 
        if(board[0][i] == 'O' && vis[0][i] == 0) {
            vis[0][i] = 1;
            q.push({0, i});
        }

        // last row 
        if(board[n - 1][i] == 'O' && vis[n - 1][i] == 0) {
            vis[n - 1][i] = 1;
            q.push({n - 1, i});
        }
    }


    for(int i = 0; i < n; i++) {
        // first col 
        if(board[i][0] == 'O' && vis[i][0] == 0) {
            vis[i][0] = 1;
            q.push({i, 0});
        }

        // last col 
        if(board[i][m - 1] == 'O' && vis[i][m - 1] == 0) {
            vis[i][m - 1] = 1;
            q.push({i, m - 1});
        }
    }

    while(!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for(auto [dx, dy] : steps){
            int nrow = row + dx;
            int ncol = col + dy;
            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
               board[nrow][ncol] == 'O' && vis[nrow][ncol] == 0) {
                vis[nrow][ncol] = 1;
                q.push({nrow, ncol});
            } 
        }        
    }

    for(int k = 0; k < n; k++) {
        for(int l = 0; l < m; l++){
            if(board[k][l] == 'O' && vis[k][l] == 0) {
                board[k][l] = 'X';
            }
        }
    }
}




// GFG && LEETCODE : 1020 (Number Of Enclaves)
int numberOfEnclaves(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    if(n == 0) return 0;

    vector<vector<int>> vis(n, vector<int>(m, 0));
    queue<pair<int, int>> q;

    vector<pair<int, int>> steps = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(int i = 0; i < m; i++) {
        // first row 
        if(grid[0][i] == 1 && vis[0][i] == 0) {
            vis[0][i] = 1;
            q.push({0, i});
        }

        // last row 
        if(grid[n - 1][i] == 1 && vis[n - 1][i] == 0) {
            vis[n - 1][i] = 1;
            q.push({n - 1, i});
        }
    }


    for(int i = 0; i < n; i++) {
        // first col 
        if(grid[i][0] == 1 && vis[i][0] == 0) {
            vis[i][0] = 1;
            q.push({i, 0});
        }

        // last col 
        if(grid[i][m - 1] == 1 && vis[i][m - 1] == 0) {
            vis[i][m - 1] = 1;
            q.push({i, m - 1});
        }
    }

    while(!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for(auto step : steps){
            int nrow = row + step.first;
            int ncol = col + step.second;
            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
               grid[nrow][ncol] == 1 && vis[nrow][ncol] == 0) {
                vis[nrow][ncol] = 1;
                q.push({nrow, ncol});
            } 
        }        
    }
    
    int count = 0;
    for(int k = 0; k < n; k++) {
        for(int l = 0; l < m; l++){
            if(grid[k][l] == 1 && vis[k][l] == 0) {
                count++;
            }
        }
    }
    
    return count;
}




// GFG : Number of Distinct Islands
void countDistinctIslandsDFS(int row, int col, vector<vector<int>>& grid, vector<vector<int>> &vis, vector<pair<int, int>> &vec, int row0, int col0){
    int n = grid.size();
    int m = grid[0].size();

    vis[row][col] = 1;
    vec.push_back({row - row0, col - col0});   // store relative position
    vector<pair<int, int>> steps = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(auto step : steps) {
        int nrow = row + step.first;
        int ncol = col + step.second;
        if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
           vis[nrow][ncol] == 0 && grid[nrow][ncol] == 1){
            countDistinctIslandsDFS(nrow, ncol, grid, vis, vec, row0, col0);
        }
    }
}

int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n, vector<int> (m, 0));
    set<vector<pair<int, int>>> st;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 1 && vis[i][j] == 0) {
                vector<pair<int, int>> vec;
                countDistinctIslandsDFS(i, j, grid, vis, vec, i, j);
                st.insert(vec);
            }
        }
    }

    return st.size();
}




// LEETCODE : 785 (Is Graph Bipartite?)
bool isBipartiteDFS(vector<vector<int>> &edges, vector<int> &col, int src, int color){
    col[src] = color;  //starting with color '0' first
    
    for(auto nbr : edges[src]) {
        if(col[nbr] == -1) {
            if(!isBipartiteDFS(edges, col, nbr, !color)) return false;
        }
        else if(col[nbr] == color) {  //if nbr has the same color as the parent 
            return false;
        }
    }
    
    return true;
}

bool isBipartiteBFS(vector<vector<int>> &edges, vector<int> &col, int src) {
    queue<int> q;
    q.push(src);
    col[src] = 0;   //Assuming colors -> 0 & 1

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        
        for(auto nbr : edges[node]) {
            if(col[nbr] == -1) { //not yet visited
                col[nbr] = !col[node];
                q.push(nbr);
            }
            else if(col[nbr] == col[node]) {  //if same as the parent
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> col(V, -1);
    
    for(int i = 0; i < V; i++) {
        if(col[i] == -1){
            if(!isBipartiteBFS(graph, col, i)) return false;
        }
    }

    for(int i = 0; i < V; i++) {
        if(col[i] == -1){
            //Assuming colors -> 0 & 1
            if(!isBipartiteDFS(graph, col, i, 0)) return false;
        }
    }
    
    return true;
}




// GFG : Directed Graph Cycle
bool isCyclicDFS(vector<vector<int>> &adjList, unordered_map<int, bool> &vis, unordered_map<int, bool> &dfsTracker, int src) {
    vis[src] = true;
    dfsTracker[src] = true;
    
    for(auto nbr : adjList[src]) {
        if(!vis[nbr]) {
            if(isCyclicDFS(adjList, vis, dfsTracker, nbr)) return true;
        }
        // If the node has been previously visited 
        // But it has to be visited on the same path
        else if(vis[nbr] == true && dfsTracker[nbr] == true){
            return true;
        }
    }
    
    // Backtracking
    dfsTracker[src] = false;
    return false;
}

bool isCyclic(int V, vector<vector<int>> &edges) {
    // Build adjacency List
    vector<vector<int>> adjList(V);
    for(auto node : edges) {
        adjList[node[0]].push_back(node[1]);
    }
    
    unordered_map<int, bool> vis;
    unordered_map<int, bool> dfsTracker;
    
    for(int i = 0; i < V; i++) {
        if(!vis[i]){
            if(isCyclicDFS(adjList, vis, dfsTracker, i)){
                return true;
            }
        }
    } 
    
    return false;
}




// LEETCODE : 802 (Find Eventual Safe States)
bool eventualSafeNodesDFS(vector<vector<int>>& graph, unordered_map<int, bool> &vis, vector<int> &safeNode, unordered_map<int, bool>  &dfsTracker, int src){
    vis[src] = true;
    dfsTracker[src] = true;

    for(auto nbr: graph[src]) {
        if(!vis[nbr]) {
            if(eventualSafeNodesDFS(graph, vis, safeNode, dfsTracker, nbr)){
                safeNode[nbr] = false;
                return true;
            } 
        }
        else if(vis[nbr] == true && dfsTracker[nbr] == true) {
            safeNode[nbr] = false;
            return true;
        }
    }
    
    // Backtracking 
    safeNode[src] = 1;
    dfsTracker[src] = false;
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int V = graph.size();
    unordered_map<int, bool> vis;
    unordered_map<int, bool> dfsTracker;
    vector<int> safeNode(V, 0);
    vector<int> ans;
    
    for(int i = 0; i < V; i++){
        if(!vis[i]){
            bool ans = eventualSafeNodesDFS(graph, vis, safeNode, dfsTracker, i);
        }
    }
    
    for(int i = 0; i < V; i++) {
        if(safeNode[i]) ans.push_back(i);
    }
    
    return ans;
}




// NOTE : By only placing nodes with zero indegree, we ensure that all prerequisites for a node are placed before it
// GFG : Prerequisite Tasks
bool isPossible(int N, int P, vector<pair<int, int> >& prerequisites) {
    vector<vector<int>> adjList(N);
    for(auto it : prerequisites) {
        adjList[it.second].push_back(it.first);
    }
    
    vector<int> inDegree(N, 0);
    for(int i = 0; i < N; i++){
        for(auto nbr : adjList[i]){
            inDegree[nbr]++;
        }
    }
    
    queue<int> q;
    for(int i = 0; i < N; i++) {
        // having  no prerequisites
        if(inDegree[i] == 0){
            q.push(i);
        }
    }
    
    vector<int> topoSort;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        topoSort.push_back(node);
        
        for(auto nbr : adjList[node]) {
            // conceptually "remove" the outgoing edges
            // of node with inDegree '0'
            inDegree[nbr]--;
            if(inDegree[nbr] == 0) {
                q.push(nbr);
            }
        }
    }
    
    if(topoSort.size() != N) return false;
    return true;
}
// GFG : Course Schedule
vector<int> findOrder(int N, vector<vector<int>> prerequisites) {
    vector<vector<int>> adjList(N);
    for(auto it : prerequisites) {
        adjList[it[1]].push_back(it[0]);
    }
    
    vector<int> inDegree(N, 0);
    for(int i = 0; i < N; i++){
        for(auto nbr : adjList[i]){
            inDegree[nbr]++;
        }
    }
    
    queue<int> q;
    for(int i = 0; i < N; i++) {
        // having  no prerequisites
        if(inDegree[i] == 0){
            q.push(i);
        }
    }
    
    vector<int> topoSort;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        topoSort.push_back(node);
        
        for(auto nbr : adjList[node]) {
            // conceptually "remove" the outgoing edges
            // of node with inDegree '0'
            inDegree[nbr]--;
            if(inDegree[nbr] == 0) {
                q.push(nbr);
            }
        }
    }
    
    if(topoSort.size() != N) return {};
    return topoSort;
}






















