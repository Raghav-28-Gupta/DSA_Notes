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



// GFG : Alien Dictionary
vector<int> topoOrder(int N, unordered_map<int, vector<int>> &adjList, unordered_map<int, int> inDegree) {
     queue<int> q;
     for(auto &entry: inDegree) {
          if(entry.second == 0) {
          q.push(entry.first);
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

     return topoSort;
}


string findOrder(vector<string> &words) {
     // used map to optimize the length of adjList && inDegree
     unordered_map<int, vector<int>> adjList;
     unordered_map<int, int> inDegree;
     unordered_set<int> vis;

     // to check topo size
     for(auto word : words) {
          for(auto it : word) {
               vis.insert(it - 'a');
               if(!inDegree.count(it - 'a')){
               inDegree[it - 'a'] = 0;
               }
          }
     }

     for(int i = 0; i < words.size() - 1; i++){
          string st1 = words[i];
          string st2 = words[i + 1];
          int len = min(st1.length(), st2.length());

          if (st1.substr(0, len) == st2.substr(0, len) && st1.length() > st2.length()) {
          return ""; // Invalid prefix case
          }

          for(int j = 0; j < len; j++) {
               if(st1[j] != st2[j]) {
               adjList[st1[j] - 'a'].push_back(st2[j] - 'a');
               inDegree[st2[j] - 'a']++;
               break;
               }
          }
     }


     vector<int> topoSort = topoOrder(26, adjList, inDegree);

     if(topoSort.size() != vis.size()) return "";

     string ans = "";
     for(auto it : topoSort) {
          ans = ans + char(it + 'a');
     }

     return ans;
}














