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


class Graph{
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

};


class GraphII{
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

};


int main() {
     // Graph g;
     // g.addEdge(0, 1, 1);
     // g.addEdge(0, 2, 1);
     // g.addEdge(1, 2, 1);
     // g.addEdge(2, 3, 1);
     // int n = 4;
     // g.printAdjList(4);

     GraphII g;
     g.addEdge(0, 1, 3, 1);
     g.addEdge(0, 2, 6, 1);
     g.addEdge(1, 2, 3, 1);
     g.addEdge(2, 3, 2, 1);
     int n = 4;
     g.printAdjList(4);

     return 0;

}