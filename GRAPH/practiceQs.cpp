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



// LEETCODE : 127 (Word Ladder)
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    // Visisted Set
    unordered_set<string> st(wordList.begin(), wordList.end());
    // Now, since I have used beginword 
    // I have to remove it from the set
    st.erase(beginWord);
    
    while(!q.empty()){
        auto frontPair = q.front();
        q.pop();

        string frontString = frontPair.first;
        int frontDist = frontPair.second;
        
        if(frontString == endWord){
            return frontDist;
        }

        for(int i = 0; i < frontString.length(); i++) {
            char orgCharacter = frontString[i];
            for(char ch = 'a'; ch <= 'z'; ch++){
                frontString[i] = ch;
                if(st.find(frontString) != st.end()) {
                    // valid String
                    q.push({frontString, frontDist + 1});
                    st.erase(frontString);
                }
            }
            frontString[i] = orgCharacter;
        }
    }
    return 0;
}

// GFG : Word Ladder II
vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;
    // To track shortest Transformation
    queue<pair<vector<string>, int>> q;
    q.push({{beginWord}, 1});
    unordered_set<string> st(wordList.begin(), wordList.end()) ;
    
    
    // If the targetWord is not in the wordList, there's no possible transformation
    if (st.find(endWord) == st.end()) {
        return {};
    }
    
    int preLevel = -1;
    vector<string> toBeRemoved;
    
    while(!q.empty()) {
        auto frontNode = q.front();
        q.pop();
        
        auto currSeq = frontNode.first;
        auto currWord = currSeq[currSeq.size() - 1];
        auto currLevel = frontNode.second;
        
        if(currLevel != preLevel){
            for(auto wrd: toBeRemoved) st.erase(wrd);
            toBeRemoved.clear();
            preLevel = currLevel;
        }
        
        if(currWord == endWord){
            ans.push_back(currSeq);
        }
        
        for(int i = 0 ; i < currWord.length(); i++){
            char originalChar = currWord[i];
            for(char ch = 'a'; ch <= 'z'; ch++) {
                currWord[i] = ch;
                if(st.find(currWord) != st.end()) {
                    auto temp = currSeq;
                    temp.push_back(currWord);
                    q.push({temp, currLevel + 1});
                    toBeRemoved.push_back(currWord);
                }
            }
            currWord[i] = originalChar;
        }
        
    }
    
    return ans;
}




// LEETCODE : 1631 (Path With Minimum Effort)
int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size();
    int cols = heights[0].size();

    // Set up a min-heap priority queue (smallest element on top)
    priority_queue<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    // vector<pair<int, pair<int, int>>> -> Underlying container (a vector of pairs)
    // greater<pair<int, pair<int, int>>>> pq -> Comparator to define min-heap behavior
    
    q.push(0, {0, 0});
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    dist[0][0] = 0;

    vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    while(!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        int curAbsDiff = current.first;
        int x = current.second.first;
        int y = current.second.second;
        
        // Check for destination
        if(x == rows-1 && y == cols-1){
            return curAbsDiff;
        }

        if(curAbsDiff > dist[x][y]) continue;

        else{
            for(auto &[dx, dy] : dir){
                int newX = x + dx;
                int newY = y + dy;

                if(newX < rows && newY < cols && newX >= 0 && newY >= 0) {
                    int newAbsDist = abs(heights[x][y] - heights[newX][newY]);
                    int maxAbsDist = max(curAbsDiff, newAbsDist);
                    if(maxAbsDist < dist[newX][newY]){
                        dist[newX][newY] = maxAbsDist;
                        pq.push({maxAbsDist, {newX, newY}});
                    }
                }
            }
        }

    }
    
    return -1;
}



// GFG : Minimum Spanning Tree (Prim's Algorithm)
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
        
        // Adding to the MST
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



// GFG : Eventual Safe States
bool eventualSafeNodesDfsSolver(int src, vector<int> adj[], unordered_map<int, bool> &vis, vector<int> &safeNode, unordered_map<int, bool> &dfsTracker){
    vis[src] = true;
    dfsTracker[src] = true;
    safeNode[src] = 0;
    
    for(auto nbr : adj[src]){
        if(!vis[nbr]){
            bool ans = eventualSafeNodesDfsSolver(nbr, adj, vis, safeNode, dfsTracker);
            if(ans == true) return true;
        }
        
        if(vis[nbr] && dfsTracker[nbr] == true){
            return true;
        }
    }
    
    // Backtracking
    dfsTracker[src] = false;
    safeNode[src] = 1;
    return false;
}

vector<int> eventualSafeNodesTopoSolver(int V, vector<int> adj[]) {
    vector<vector<int>> reverseGraph(V);
    vector<int> indegree(V, 0);
    
    for(int i = 0; i < V; i++) {
        for(auto nbr : adj[i]) {
            reverseGraph[nbr].push_back(i);
            indegree[i]++;  // original node with out-edge gets incremented
        }
    }
    
    queue<int> q;
    for(int i = 0; i < V; i++) {
        if(indegree[i] == 0){
            q.push(i);
        }
    }
    
    vector<int> safeNodes;
    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();
        safeNodes.push_back(frontNode);
        
        for(auto nbr : reverseGraph[frontNode]){
            indegree[nbr]--;
            if(indegree[nbr] == 0){
                q.push(nbr);
            }
        }
    }
    
    sort(safeNodes.begin(), safeNodes.end());
    return safeNodes;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    unordered_map<int, bool> vis;
    unordered_map<int, bool> dfsTracker;
    vector<int> safeNode(V, 0);
    vector<int> ans;
    
    for(int i = 0; i < V; i++){
        if(!vis[i]){
            bool ans = eventualSafeNodesDfsSolver(i, adj, vis, safeNode, dfsTracker);
        }
    }
    
    for(int i = 0; i < V; i++) {
        if(safeNode[i]) ans.push_back(i);
    }
    
    return ans;
    
    // return eventualSafeNodesTopoSolver(V, adj);
}



// GFG : Minimum Multiplications to reach End
int minimumMultiplications(vector<int>& arr, int start, int end) {
    const int mod = 100000;
    queue<pair<int, int>> q;
    q.push({start, 0});  // {current node, steps taken}
    
    vector<int> dist(100000, INT_MAX); 
    dist[start] = 0;
    
    while (!q.empty()) {
        int node = q.front().first;
        int steps = q.front().second;
        q.pop();
        
        for (auto ele : arr) {
            int newNode = (node * ele) % mod;
            if (steps + 1 < dist[newNode]) {
                dist[newNode] = steps + 1;
                if (newNode == end) return steps + 1;
                q.push({newNode, steps + 1});
            }
        }
    }
    
    return (start == end) ? 0 : -1; 
}














