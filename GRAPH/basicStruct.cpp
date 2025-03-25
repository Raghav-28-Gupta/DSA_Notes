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


          // Cycle Detection
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
                         else if(visited[nbr] == true && nbr != parent[frontNode]) {
                              return true;
                         }
                    }
               }

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

               return cycleDetectionUndirectedBFS(src, visited);
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