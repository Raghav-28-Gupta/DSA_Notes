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



// LEETCODE : 207 (Course Schedule)
void canFinishTopoBfs(int V, vector<vector<int>> &adj, vector<int> &ans) {
     unordered_map<int, int> indegree;
     queue<int> q;

     for(int i = 0; i < V; i++) {
          for(auto nbr: adj[i]) {
               indegree[nbr]++;
          }
     }

     // Initial State
     for(int i = 0; i < V; i++) {
          if(indegree[i] == 0) {
               q.push(i);
          }
     }

     // Main Logic
     while(!q.empty()){
          int frontNode = q.front();
          ans.push_back(frontNode);
          q.pop();

          for(auto nbr: adj[frontNode]) {
               indegree[nbr]--;
               if(indegree[nbr] == 0) {
                    q.push(nbr);
               }
          }
     }
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
     int V = numCourses;

     // Build adjacency list
     vector<vector<int>> adj(V);
     for(auto nbr: prerequisites){
         adj[nbr[1]].push_back(nbr[0]);
     }
     
     vector<int> ans;
     canFinishTopoBfs(V, adj, ans);

     if(ans.size() == V) {
         return true;
     } else return false;
}



// LEETCODE : 210 (Course Schedule II)
void findOrderTopo(int n, vector<vector<int>> adj, vector<int> &ans){
     unordered_map<int, int> indegree;
     queue<int> q;

     // Create indegree map
     for(int i = 0; i < n; i++){
         for(auto nbr: adj[i]) {
             indegree[nbr]++;
         }
     }

     // Initial State
     for(int i = 0; i < n; i++) {
         if(indegree[i] == 0){
             q.push(i);
         }
     }
     
     // Main Logic
     while(!q.empty()) {
         int frontNode = q.front();
         ans.push_back(frontNode);
         q.pop();

         for(auto nbr: adj[frontNode]){
             indegree[nbr]--;
             if(indegree[nbr] == 0){
                 q.push(nbr);
             }
         }
     }
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
     int n = numCourses;
     
     vector<vector<int>> adj(n);
     // Build the Adjacency List
     for(auto nbr: prerequisites){
         adj[nbr[1]].push_back(nbr[0]);
     }
     
     vector<int> ans;
     findOrderTopo(n, adj, ans);

     if(ans.size() != numCourses) return {};
     else return ans;
 
}







