#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
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

// LEETCODE : 232  ---> Implement Queue using Stack
class MyQueue {
public:
     stack<int> s1;
     stack<int> s2;

     MyQueue() {
        
     }
    
     void push(int x) {
        s1.push(x);
     }
    

     int pop() {
          int pop = -1;

          if (!s2.empty()) {
               pop = s2.top();
          }
          
          else {
               while(!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
               }
               pop = s2.top();
          }
          
          s2.pop();
          return pop;
     }
    

     int peek() {

          int front = -1;
          if (!s2.empty()) {
               front = s2.top();
          }
        
          else {
               while(!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
               }

               front = s2.top();
          }

          return front;
     }
    
     bool empty() {
        return s1.empty() && s2.empty();
     }
};




// LEETCODE : 225  ---> Implement Stack using Queue
class MyStack {
public:
     queue<int> q;
     MyStack() {
        
     }
    
     void push(int x) {
          q.push(x);
          for(int i = 0; i < q.size() - 1; i++) {
               int front = q.front();
               q.pop();
               q.push(front);
          }
     }
    
     int pop() {
        int front = q.front();
        q.pop();
        return front;
     }
    
     int top() {
        return q.front();
     }
    
     bool empty() {
        return q.empty();
     }
};





int main() {
     MyStack q;
     q.push(1);
     q.push(12);
     q.push(13);
     q.push(14);
     q.push(15);

     cout << q.pop() << endl;

     // cout << q.peek() << endl;

     cout << boolalpha << q.empty();
     
     return 0;
}