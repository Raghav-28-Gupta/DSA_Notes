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



void reverseQueue_1(queue<int> &q) {
     stack<int> st;

     while(!q.empty()) {
          int element = q.front();
          q.pop();

          st.push(element);
     }
     
     while(!st.empty()) {
          int element = st.top();
          st.pop();

          q.push(element);
     }
     
}


void reverseQueue_2(queue<int> &q) {
     // Base Case
     if (q.empty()) {
          return;
     }

     int frontElement = q.front();
     q.pop();

     reverseQueue_2(q);
     
     // Backtracking
     q.push(frontElement);
}



// [IMPORTANT]
void reverseInGroups(queue<int>& q, int k) {
     if (q.empty() || k <= 0) return;

     stack<int> st;
     queue<int> tempQueue;

     while (!q.empty()) {
          int count = 0;
          
          // Take the first k elements from the queue and push into stack
          while(!q.empty() && count < k) {
               st.push(q.front());
               q.pop();
               count++;
          }
          
          // Pop from the stack and push back into a temp queue (to reverse)
          while(!st.empty()) {
               tempQueue.push(st.top());
               st.pop();
          }
          
          // Push the remaining elements (less than k)
          if (count < k) {
               while(!q.empty()) {
                    tempQueue.push(q.front());
                    q.pop();
               }
          }
     }
     
     q = tempQueue;
}




vector<int> rearrangeQueue(queue<int> &q1) {
     vector<int> ans;
     queue<int> q2;

     int size = q1.size();
     int half = size / 2;

     while (half--) {
          q2.push(q1.front());
          q1.pop();
     }

     while(!q1.empty()) {
          ans.push_back(q1.front());
          q1.pop();
          ans.push_back(q2.front());
          q2.pop();
     }

     return ans;
}





// [IMPORTANT]

// Sliding Window Teqhnique
vector<int> firstNegativeInWindow(int A[], int N, int K) {
     deque<int> dq;
     vector<int> result;

     for (int i = 0; i < N; i++) {
          // Remove elements that are out of this window
          if (!dq.empty() && dq.front() < i-K+1) { // OR ---> (dq.front() == i - k)
               dq.pop_front();
          }

          // Add current element index if it is negative
          if (A[i] < 0) {
               dq.push_back(i);
          }
          
          // Start adding results after the first window is formed
          if (i >= K-1) {
               if(!dq.empty()) {
                    result.push_back(A[dq.front()]);
               }
               else {
                    // No negative number in the window
                    result.push_back(0);
               }
          }
     }
     
     return result;
}


vector<int> maxSlidingWindow(vector<int>& nums, int k) {
     deque<int> dq;   // Will store indices of elements in the window
     vector<int> result;
     int N = nums.size();

     for (int i = 0; i < N; i++) {
          // Remove elements not within the sliding window
          if (!dq.empty() && dq.front() < i-k+1) {
               dq.pop_front();
          }
          
          // Remove elements from the back of the deque which are less than the current element
          while(!dq.empty() && nums[dq.back()] < nums[i]) {
               dq.pop_back();
          }
          
          // Add the current element's index to the deque
          dq.push_back(i);
          


          // If we've processed at least k elements, 
          // the front of the deque is the max of the current window
          if (i >= k-1) {
               result.push_back(nums[dq.front()]);
          }
     }
     
     return result;
}





// First non-repeating character in a stream
string FirstNonRepeating(string &A) {
     
     unordered_map<char,int> freqChar;
     queue<char> q;
     string result;

     for (int i = 0; i < A.length(); i++) {
          char ch = A[i];
          freqChar[ch]++;

          q.push(ch);

          while(!q.empty() && freqChar[ch] > 1) {
               q.pop();
          }
         
          if (q.empty()) {
               result += '#';
          }
          else {
               result += q.front();
          }
     }
     
     return result;
}






// LEETCODE : 1823 (Josephus Problem)                       [IMPORTANT]
int findTheWinner(int n, int k) {
     queue<int> q;
     
     // Initialize the queue with friends numbered 1 to n
     for (int i = 1; i <= n; i++) {
          q.push(i);
     }

     // Simulate the elimination process
     while(q.size() > 1) {
          // Move the first (k-1) friends to the back of the queue
          for (int i = 1; i < k; i++) {
               int front = q.front();
               q.pop();
               q.push(front);
          }

          // Eliminate the k-th friend
          q.pop();
     }
     
     return q.front();
}






// LEETCODE : 950 (Reveal Cards In Increasing Order)        [IMPORTANT]
vector<int> deckRevealedIncreasing(vector<int>& deck) {
     // First Sort the cards
     int n = deck.size();
     sort(deck.begin(), deck.end());
     
     // Fill the queue with indices 0, 1, ..., n-1
     queue<int> indexQ;
     for (int i = 0; i < n; i++) {
          indexQ.push(i);
     }

     vector<int> result(n);

     for (int i = 0; i < n; i++) {
          // Get the current position from the front of the queue
          int pos = indexQ.front();
          indexQ.pop();

          // Place the card in the result array
          result[pos] = deck[i];
          
          // If there are still indices left, simulate moving the next card(Here: INDEX) to the bottom
          if (!indexQ.empty()) {
               int nextPos = indexQ.front();
               indexQ.pop();
               indexQ.push(nextPos);
          }
     }
     
     return result;
}







int main() {
     // queue<int> q;
     // q.push(10);
     // q.push(20);
     // q.push(30);
     // q.push(40);
     // q.push(50);
     // q.push(60);

     // while (!q.empty()) {
     //      cout << q.front() << " ";
     //      q.pop();
     // }


     vector<int> deck = {17, 13, 11, 2, 3, 5, 7};
    
     // Call the function
     vector<int> result = deckRevealedIncreasing(deck);
    
     // Output the result
     for (int card : result) {
        cout << card << " ";
     }
     cout << endl;

     return 0;
}