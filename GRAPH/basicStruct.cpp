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


class GraphII{
     public:
          unordered_map<int, list<int>> adjList;

          void addEdge(int u, int v, bool direction){
               // Direction = 0 -> Undirected Graph
               // Direction = 1 -> Directed Graph
               if(direction == 0) {
                    adjList[u].push_back(v);
                    adjList[v].push_back(u);
               }
               else{
                    // Directed Edge
                    adjList[u].push_back(v);
               }
          }
          
          void printAdjList(int n){
               for(int i = 0; i < n; i++) {
                    cout << i << ": ";
                    cout << "{";
                    list<int> temp = adjList[i];
                    for(auto j : temp) {
                         cout << j << ",";
                    }
                    cout << "}" << endl;
               }


               // for(auto i : adjList){
               //      cout << i.first << ": ";
               //      cout << "{";
               //      for(auto j : i.second) {
               //           cout << j << ",";
               //      }
               //      cout << "}" << endl;
               // }

          }



          // Cycle Detection in Undirected Graph Using BFS
          bool cycleDetectionUndirectedBFS(int src, unordered_map<int, bool> &visited){
               queue<int> q;
               unordered_map<int, int> parent;

               // Initial state
               q.push(src);
               visited[src] = true;
               parent[src] = -1;

               while(!q.empty()) {
                    int frontNode = q.front();
                    q.pop();

                    for(auto nbr : adjList[frontNode]) {
                         if(!visited[nbr]) {
                              q.push(nbr);
                              visited[nbr] = true;
                              parent[nbr] = frontNode;
                         }

                         // Cycle Detection case
                         // The key is to check whether the already visited nbr 
                         // was visited from a different path
                         else if(visited[nbr] == true && nbr != parent[frontNode]) {
                              return true;
                         }
                    }
               }

               return false;
          }

          // Cycle Detection in Undirected Graph Using DFS
          bool cycleDetectionUndirectedDFS(int src, unordered_map<int, bool> &visited, int parent) {
               visited[src] = true;

               for(auto nbr : adjList[src]){
                    if(!visited[nbr]) {
                         cycleDetectionUndirectedDFS(nbr, visited, src);
                    }
                    
                    else if(visited[nbr] == true && nbr != parent) {
                         return true;
                    }
               }
               
               return false;
          }

          // Cycle Detection in Directed Graph Using DFS
          bool CycleDetectionDirectedDFS(vector<vector<int>> &adj, int src, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsTracker){
               visited[src] = true;
               dfsTracker[src] = true;
               
               for(auto nbr : adj[src]) {
                    if(!visited[nbr]) {
                         bool ans = CycleDetectionDirectedDFS(adj, nbr, visited, dfsTracker);
                         if(ans = true) {
                              return true;
                         }
                    }
                    else if(visited[nbr] == true && dfsTracker[nbr] == true) {
                         // Cycle Present
                         return true;
                    }
               }
               
               // Backtracking
               dfsTracker[src] = false;
               return false;
           }

          bool isCycle(int n) {
               int src = 0;
               unordered_map<int, bool> visited;
               
               // // if Graph contains components
               // bool ans = false;
               // for(int src = 0; src < n; src++) {
               //      if(!visited[src]) {
               //           ans = cycleDetectionUndirectedBFS(src, visited);
               //      }
               //      if(ans == true) break
               // }
               // return ans;

               // return cycleDetectionUndirectedDFS(src, visited);

               return cycleDetectionUndirectedDFS(src, visited, -1);
          }
          // Cycle Detection can also be solved using Topological order
          // In which the the nodes in ans array != total no. of nodes
          

          // Topological Sort (Applied only on Directed Acyclic Graphs)
          void topDfs(vector<vector<int>>& adj, int src, unordered_map<int, bool> &vis, vector<int> &ans){
               vis[src] = true;
               
               for(auto nbr : adj[src]) {
                    if(!vis[nbr]) {
                         topDfs(adj, nbr, vis, ans);
                    }
               }
               
               // backtracking
               ans.push_back(src);
          }
         
          void topBfs(int n, vector<vector<int>>& adj, vector<int> &ans) {
               unordered_map<int, int> indegree;
               queue<int> q;
               
               // Preparing n-degree map
               for(int src = 0; src < n; src++){
                    for(auto nbr : adj[src]){
                         indegree[nbr]++;
                    }
               }
               
               // Maintaing initia; state in q
               for(int i = 0; i < n; i++) {
                    if(indegree[i] == 0) {
                         q.push(i);
                    }
               }
               
               while(!q.empty()) {
                    int frontNode = q.front();
                    ans.push_back(frontNode);
                    q.pop();
                    
                    // Since FrontNode is removed 
                    // Update the indegree of its children accordingly
                    for(int nbr : adj[frontNode]) {
                         indegree[nbr]--;
                         if(indegree[nbr] == 0){
                              q.push(nbr);
                         }
                    }
               }
          }

          vector<int> topologicalSort(vector<vector<int>>& adj) {
               // Your code here
               unordered_map<int, bool> vis;
               vector<int> ans;
               int n = adj.size();
               
               for(int i = 0; i < n; i++) {
                    if(!vis[i]) {
                         topDfs(adj, i, vis, ans);
                    }
               }
               
               reverse(ans.begin(), ans.end());
               return ans;
          }


          // Shortest Path (Also check practiceQs)
          void shortestPathBfs(int src, vector<vector<int>>& edges, vector<int> &ans, int dest){
               unordered_map<int, bool> &vis;
               unordered_map<int, int> &parent;
               queue<int> q;
               q.push(src);
     
               //Initial State
               vis[src] = true;
               parent[src] = -1;
               
               // Main Logic
               while(!q.empty()) {
                    int frontNode = q.front();
                    q.pop();
     
                    for(auto nbr : edges[frontNode]) {
                         if(!vis[nbr]){
                              q.push(nbr);
                              vis[nbr] = true;
                              parent[nbr] = frontNode;
                         }
                    }
               }
               
               // Parent array is ready
               int node = dest;
               while(node != -1) {
                    ans.push_back(node);
                    node = parent[node];
               }
               
               reverse(ans.begin(), ans.end());
          }
 
          
          // Dijkstra Algorithm (GFG Practice)
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
};



// Weighted Graph
class Graph{
     public:
          unordered_map<int, list<pair<int, int>>> adjList;

          void addEdge(int u, int v, int weight, bool direction){
               // Direction = 0 -> Undirected Graph
               // Direction = 1 -> Directed Graph
               if(direction == 0) {
                    adjList[u].push_back({v, weight});
                    adjList[v].push_back({u, weight});
               }
               else{
                    // Directed Edge
                    adjList[u].push_back({v, weight});
               }
          }
          void printAdjList(int n){
               for(int i = 0; i < n; i++) {
                    cout << i << ": ";
                    cout << "{";
                    list<pair<int, int>> temp = adjList[i];
                    for(auto j : temp) {
                         cout << "(" << j.first << "," << j.second << ")";
                    }
                    cout << "}" << endl;
               }


               // for(auto i : adjList){
               //      cout << i.first << ": ";
               //      cout << "{";
               //      for(auto j : i.second) {
               //           cout << j << ",";
               //      }
               //      cout << "}" << endl;
               // }

          }
          
          // BFS Traversal
          void BFSTraversal(int src) {
               queue<int> q;
               unordered_map<int, bool> visited;
               
               // Initial state
               q.push(src);
               visited[src] = true;

               while(!q.empty()) {
                    int frontNode = q.front();
                    cout << frontNode << ", ";
                    q.pop();

                    for(auto nbr : adjList[frontNode]) {
                         // nbr -> pair
                         // first -> node
                         int node = nbr.first;
                         // second -> weight
                         int weight = nbr.second;
                         if(!visited[node]) {
                              q.push(node);
                              visited[node] = true;
                         }
                    }
               }

               cout << endl;
          }
          
          // DFS Traversal
          void DFSTraversal(int src, unordered_map<int,bool> &visited) {
               visited[src] = true;
               cout << src << ", ";

               for(auto nbr : adjList[src]) {
                    // nbr -> pair
                    // first -> node
                    int node = nbr.first;
                    // second -> weight
                    int weight = nbr.second;
                    if(!visited[node]){
                         DFSTraversal(node, visited);
                    }
               }


          } 
          void dfs(int n){
               int src = 0;
               unordered_map<int,bool> visited;
               
               // for Component Graph
               // for(int src = 0; src < n; src++) {
               //      if(!visited[src]) {
               //           DFSTraversal(src, visited);
               //      }
               // }

               DFSTraversal(src, visited);
          } 

          // Cycle Detection Undirected in GraphII



};




int main() {
     GraphII g;
     g.addEdge(0, 1, 0);
     g.addEdge(1, 2, 0);
     g.addEdge(3, 0, 0);
     g.addEdge(2, 3, 0);
     int n = 4;
     g.printAdjList(4);
     cout << "does it contain cycle: " << boolalpha << g.isCycle(4);

     // Graph g;
     // g.addEdge(0, 3, 3, 1);
     // g.addEdge(0, 5, 3, 1);
     // g.addEdge(0, 2, 3, 1);
     // g.addEdge(2, 5, 3, 1);
     // g.addEdge(3, 5, 3, 1);
     // g.addEdge(5, 4, 3, 1);
     // g.addEdge(5, 6, 3, 1);
     // g.addEdge(4, 1, 3, 1);
     // g.addEdge(6, 1, 3, 1);
     // int n = 7;
     // g.printAdjList(n);
     // cout << endl << "BFS: "; 
     // g.dfs(0);

     return 0;

}