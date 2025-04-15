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



// Time Complexity: O(α(N))  where α is the inverse Ackermann function, which grows super slowly
class DisJointSet {
     vector<int> rank, parent, size;

public:
     DisJointSet(int n) {
          rank.resize(n + 1, 0);
          size.resize(n + 1, 0);
          parent.resize(n + 1);
          
          // Each node is its own parent initially
          for(int i = 0; i <= n; i++) parent[i] = i;
     }
          
     // Path compression
     int findUpar(int u) {
          if(u != parent[u]) {
               parent[u] = findUpar(parent[u]);
          }
          
          // Ultimate Parent
          return parent[u];
     }

     void unionByRank(int u, int v) {
          int ult_u = findUpar(u);
          int ult_v = findUpar(v);

          if(ult_u == ult_v) return;

          if(rank[ult_u] > rank[ult_v]) {
               parent[ult_v] = ult_u;
          }
          else if(rank[ult_v] > rank[ult_u]) {
               parent[ult_u] = ult_v;
          }
          else{
               parent[ult_v] = ult_u;
               rank[ult_u]++;
          }
     }

     void unionBySize(int u, int v) {
          int ult_u = findUpar(u);
          int ult_v = findUpar(v);

          if(ult_u == ult_v) return;
          
          // We attach the smaller set under the larger one in Union by Size to optimize the depth of the tree 
          // which helps keep the find() operation fast.

          if(size[ult_u] < size[ult_v]) {
               parent[ult_u] = ult_v;
               size[ult_v] += size[ult_u];
          }

          else {
               parent[ult_v] = ult_u;
               size[ult_u] += size[ult_v];
          }
     }
};



// GFG : Connecting the graph
int Solve(int n, vector<vector<int>>& edge) {
     DisJointSet ds(n);
     
     int cntExtras = 0;
     for(auto node : edge){
          int u = node[0];
          int v = node[1];
          
          if(ds.findUpar(u) == ds.findUpar(v)) {
               cntExtras++;
          }
          
          else{
               ds.unionBySize(u, v);
          }
     }
     
     
     int cntCompo = 0;
     for(int i = 0; i < n; i++) {
         if(ds.parent[i] == i) cntCompo++;
     }
     
     int ans = cntCompo - 1;
     
     if(cntExtras >= ans) return ans;
     return -1;
}




int main() {
     DisJointSet ds(7);

     ds.unionBySize(1, 2);
     ds.unionBySize(2, 3);
     ds.unionBySize(4, 5);
     ds.unionBySize(6, 7);
     ds.unionBySize(5, 6);
     // If 3 & 7 same or not
     if(ds.findUpar(3) == ds.findUpar(7)){
          cout << "Same" << endl;
     } else {
          cout << "Not Same" << endl;
     }

     ds.unionByRank(3, 7);

     if(ds.findUpar(3) == ds.findUpar(7)){
          cout << "Same" << endl;
     } else {
          cout << "Not Same" << endl;
     }
     
     return 0;
}







