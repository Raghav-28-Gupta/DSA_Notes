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



class DisJointSet {
public:
     vector<int> rank, parent;

private:
     DisJointSet(int n) {
          rank.resize(n + 1, 0);
          parent(n + 1);
          for(int i = 0; i <= n; i++) parent[i] = i;
     }
          
     int findUpar(int u) {
          if(u != parent[u]) {
               parent[u] = find(parent[u]);
          }
          
          // Ultimate Parent
          return parent[u];
     }

     int unionByRank(int u, int v) {
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
};




int msin() {
     DisJointSet ds(7);

     ds.unionByRank(1, 2);
     ds.unionByRank(2, 3);
     ds.unionByRank(4, 5);
     ds.unionByRank(6, 7);
     ds.unionByRank(5, 6);
     // If 3 & 7 same or not
     if(ds.findUpar(3) == ds.findUpar(7)){
          cout << "Same" << endl;
     } else {
          cout << "Not Same" << endl;
     }

     ds.unionByRank(3, 7);
     
     return 0;
}







