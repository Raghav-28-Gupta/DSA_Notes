#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <stack>
#include <math.h>
#include <limits.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;



void insertAtBottom(stack<int> &s, int value) {
     // Base Case
     if (s.empty()) {
          s.push(value);
          return;
     }
     
     // Recursively 'storing' and 'removing' Top value
     int top = s.top();
     s.pop();
     insertAtBottom(s,value);

     // Backtrack
     s.push(top);

} 



bool checkSorted(stack<int> &s, int maxVal) {
     // Base Case
     if (s.empty()) {
          return true;
     }

     int top = s.top();
     s.pop();

     if (top < maxVal) {
          bool ans = checkSorted(s,top);
          s.push(top);
          return ans;
     }

     else {
          return false;
     }
}



void reverseStack(stack<int> &s) {
     // Base Case
     if (s.empty()) {
          return;
     }

     int topElement = s.top();
     s.pop();

     reverseStack(s);
     
     insertAtBottom(s, topElement);
}



void sortedInsert(stack<int> &s, int value) {
     // Base Case
     if (!s.empty() && s.top() < value) {
          s.push(value);
          return;
     }
     

     int Top = s.top();
     s.pop();

     sortedInsert(s,value);
     
     // Backtrack
     s.push(Top);
}




// LEETCODE : 20
bool isValidParenthesis_1(string &s) {
     stack<char> st;

     for (int i = 0; i < s.length(); i++) {
          char ch = s[i];

          // Check for open brackets
          if (ch == '(' || ch == '[' || ch == '{' ) {
               st.push(ch);
          }

          else {
               // If stack is empty or top doesn't match, it's invalid
               if (ch == ')' && !st.empty() && st.top() == '('){
                    st.pop();
               }

               else if (ch == '}' && !st.empty() && st.top() == '{'){
                    st.pop();
               }

               else if (ch == ']' && !st.empty() && st.top() == '['){
                    st.pop();
               }

               else {
                    // Bracket -> doesnt match
                    return false;
               }

          }
     }

     if (st.empty()) return true;
     else return false;     
}

bool isValidParenthesis_2(string &s) {
     // Map to match closing brackets with their corresponding opening brackets
     unordered_map<char,char> bracketPairs = {
          {')', '('},
          {'}', '{'},
          {']', '['}
     };

     stack<char> st;
     for (auto c : s) {
          // If the character is a closing bracket
          if (bracketPairs.count(c)) {
               // Check if the stack is not empty and top is the correct opening bracket
               if (!st.empty() && st.top() == bracketPairs[c]) {
                    st.pop();
               }
               else {
                    return false;
               }
          }
          else {
               // Character is an open bracket
               st.push(c);
          }
     }

     return st.empty();

}

// Similarly, Count The Reversals
int countRev(string &s) {
     // Check for ODD String
     if (s.length() % 2 != 0) return -1;
     
     stack<int> stk;
     int ans = 0;

     for (auto pr : s) {
          // If Open Braces
          if (pr == '{') {
               stk.push(pr);
          }

          // If Closed Braces
          else {
               if (!stk.empty() && stk.top() == '{') {
                    stk.pop();
               }
               else {
                    stk.push(pr);
               }
          }
     }

     // IMPORTANT STEP
     // Till here, the unbalanced Stack is obtained

     while(!stk.empty()) {
          auto a = stk.top(); stk.pop();
          auto b = stk.top(); stk.pop();

          if (a == b) {
               ans += 1;
          }
          else {
               ans += 2;
          }
     }
     
     return ans;
}








// Expression contains redundant bracket or not
int checkRedundancy(string &s) {
     // Stack to store characters
     stack<char> st;
    
     for (auto ch : s) {
          // If the current character is a closing parenthesis ')'
          if (ch == ')') {
               bool isRedundant = true;

               while(!st.empty() && st.top() != '(') {
                    char Top = st.top();
                    st.pop();

                    if (Top == '+' || Top == '-' || Top == '/' || Top == '*') {
                         isRedundant = false;
                    }

               }

               if (!st.empty()) {
                    // remove the open parenthesis
                    st.pop();
               }

               if (isRedundant) {
                    return 1;
               }

          }

          else {
               // Push the current character to the stack if it's not a closing parenthesis
               st.push(ch);
          }
     }
     
     // If no redundant parentheses found, return 0
     return 0;

}




// Next Smaller Element
void nextSmallerElement(int arr[], int n, vector<int> &ans) {
     stack<int> st;
     st.push(-1);

     for (int i = n - 1; i >= 0; i--) {
          int element = arr[i];

          if (!st.empty() && st.top() >= element) {
               st.pop();
          }
          
          // Now st.top() is the smallest element
          ans.push_back(st.top());

          // Put the arr[i] for further comparison
          st.push(element);
     }

     // NOTE : reverse the 'ans' vector before printing

}

// Previous Smaller Element
void previousSmallerElement(int arr[], int n, vector<int> &ans) {
     stack<int> st;
     st.push(-1);

     for (int i = 0; i < n; i++) {
          int element = arr[i];

          if (!st.empty() && st.top() >= element){
               st.pop();
          }

          ans.push_back(st.top());

          st.push(element);
     }
}





// LEETCODE : 739 (Daily Temperatures)
vector<int> dailyTemperatures(vector<int>& temperatures) {
     int n = temperatures.size();
     vector<int> ans(temperatures.size(), 0);
     stack<int> stk;

     for (int i = 0; i < n; i++) {
          while(!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
               // Important Step
               ans[stk.top()] = i - stk.top();
               stk.pop();
          }

          stk.push(i);
     }
        
     return ans;
}






// LEETCODE : 84 (Largest Rectangle In Histogram)                   [IMPORTANT]
void nextSmallerRect(vector<int> &heights, vector<int> &nextAns) {
     stack<int> st;
     st.push(-1);   // Here '-1' acts as both value and index
     int n = heights.size();

     for (int i = n - 1; i >= 0; i--) {
          int element = heights[i];

          while(st.top() != -1 && heights[st.top()] >= element){
               // Here st.top() acts like Index No.
               st.pop();
          }
          // Now st.top() is the smallest
          nextAns.push_back(st.top());

          // Again push the i for further comparison
          st.push(i);
     }

}

void prevSmallerRect(vector<int> &heights, vector<int> &prevAns) {
     stack<int> st;
     st.push(-1);   // Here '-1' acts as both value and index
     int n = heights.size();

     for (int i = 0; i < n; i++) {
          int element = heights[i];
     
          while(st.top() != -1 && heights[st.top()] >= element){
               // Here st.top() acts like Index No.
               st.pop();
          }
          // Now st.top() is the smallest
          prevAns.push_back(st.top());

          // Again push the i for further comparison
          st.push(i);
     }

}

int largestRectangleArea(vector<int>& heights) {
     vector<int> prevAns;
     prevSmallerRect(heights, prevAns);

     vector<int> nextAns;
     nextSmallerRect(heights, nextAns);
     reverse(nextAns.begin(), nextAns.end());
     
     // Important Step For nextAns vector
     for (int i = 0; i < nextAns.size(); i++) {
          if (nextAns[i] == -1) {
               nextAns[i] = heights.size();
          }
     }
     
     int maxArea = INT_MIN;
     for (int i = 0; i < nextAns.size(); i++) {
          int width = nextAns[i] - prevAns[i] - 1;
          int height = heights[i];

          int currArea = width * height;
          maxArea = max(maxArea, currArea);
     }

     return maxArea;
}

// Similarly,

// LEETCODE : 85 (Maximal Rectangle)
int maximalRectangle(vector<vector<char>>& matrix) {
     int n = matrix.size();
     int m = matrix[0].size();
     
     vector<vector<int>> v;
     for (int i = 0; i < n; i++) {
          vector<int> t;
          for (int j = 0; j < m; j++) {
               t.push_back(matrix[i][j] - '0');
          }
          v.push_back(t);
     }

     int area = largestRectangleArea(v[0]);
     for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
               if (v[i][j]) {
                    v[i][j] += v[i-1][j];
               }
               else {
                    v[i][j] = 0;
               }
          }

          area = max(area, largestRectangleArea(v[i]));
     }
     
     return area;
}








// LEETCODE : 907 (Sum Of Subarray Minimums)
long long sumSubarrayMins(vector<int>& arr) {
     const int MOD = 1e9 + 7;     // define it const : Good Practice
     
     int n = arr.size();
     vector<int> ple(n);
     vector<int> nle(n);
     stack<int> st;

     // Calculate Previous Less Element (PLE)
     for (int i = 0; i < n; i++) {
          while (!st.empty() && arr[st.top()] >= arr[i]) {
               st.pop();
          }

          ple[i] = st.empty() ? -1 : st.top();
          st.push(i);
     }

     // Clear the stack to reuse it for Next Less Element (NLE)
     while(!st.empty()) {
          st.pop();
     }

     // Calculate Next Less Element (NLE)
     for (int i = n-1; i >= 0; i--) {
          while (!st.empty() && arr[st.top()] > arr[i]) {
               st.pop();
          }

          nle[i] = st.empty() ? n : st.top();
          st.push(i);
     }

     // Calculate the total sum of minimums of all subarrays
     long long result = 0;
     for (int i = 0; i < n; i++) {
          long long left = i - ple[i];
          long long right = nle[i] - i;
          result = (result + arr[i] * left * right) % MOD;
     }

     return result;

}

// Similarly, LEETCODE : 2104
long long sumSubarrayMins_1(vector<int>& arr) {
     const int MOD = 1e9 + 7;     // define it const : Good Practice
     
     int n = arr.size();
     vector<int> ple(n);
     vector<int> nle(n);
     stack<int> st;

     // Calculate Previous Less Element (PLE)
     for (int i = 0; i < n; i++) {
          while (!st.empty() && arr[st.top()] >= arr[i]) {
               st.pop();
          }

          ple[i] = st.empty() ? -1 : st.top();
          st.push(i);
     }

     // Clear the stack to reuse it for Next Less Element (NLE)
     while(!st.empty()) {
          st.pop();
     }

     // Calculate Next Less Element (NLE)
     for (int i = n-1; i >= 0; i--) {
          while (!st.empty() && arr[st.top()] > arr[i]) {
               st.pop();
          }

          nle[i] = st.empty() ? n : st.top();
          st.push(i);
     }

     // Calculate the total sum of minimums of all subarrays
     long long result = 0;
     for (int i = 0; i < n; i++) {
          long long left = i - ple[i];
          long long right = nle[i] - i;
          result = (result + arr[i] * left * right) % MOD;
     }

     return result;
}

long long sumSubarrayMaxs_1(vector<int>& arr) {
     const int MOD = 1e9 + 7;     // define it const : Good Practice
     
     int n = arr.size();
     vector<int> ple(n);
     vector<int> nle(n);
     stack<int> st;

     // Calculate Previous Greater Element (PGE)
     for (int i = 0; i < n; i++) {
          while (!st.empty() && arr[st.top()] <= arr[i]) {
               st.pop();
          }

          ple[i] = st.empty() ? -1 : st.top();
          st.push(i);
     }

     // Clear the stack to reuse it for Next Greater Element (NGE)
     while(!st.empty()) {
          st.pop();
     }

     // Calculate Next Greater Element (NGE)
     for (int i = n-1; i >= 0; i--) {
          while (!st.empty() && arr[st.top()] < arr[i]) {
               st.pop();
          }

          nle[i] = st.empty() ? n : st.top();
          st.push(i);
     }

     // Calculate the total sum of minimums of all subarrays
     long long result = 0;
     for (int i = 0; i < n; i++) {
          long long left = i - ple[i];
          long long right = nle[i] - i;
          result = (result + arr[i] * left * right) % MOD;
     }

     return result;
}

long long subArrayRanges(vector<int>& nums) {
     auto sumOfMaximums = sumSubarrayMaxs_1(nums);
     auto sumOfMinimums = sumSubarrayMins_1(nums);
     return sumOfMaximums - sumOfMinimums;
        
}






// LEETCODE : 224       (Basic Calculator)       [IMPORTANT]
int calculate(string s) {
     stack<int> stk;    // Stack to store results and signs

     int current_result = 0;
     int sign = 1;
     int n = s.length();

     int i = 0;
     while (i < n) {
          char c = s[i];

          if (isdigit(c)) {
               // Parse the full number
               int num = 0;
               while ( i < n && isdigit(s[i]) ) {
                    num = num*10 + (s[i] - '0');
                    i++;
               }
               current_result += sign * num;
               i--; // Adjust index after the while loop
          }

          else if (c == '+') {
               sign = 1;
          }
          
          else if (c == '-') {
               sign = -1;
          }

          else if (c =='(') {
               // Push current result and sign to the stack
               stk.push(current_result);
               stk.push(sign);
               
               // Reset for new subexpression
               current_result = 0;
               sign = 1;
          }

          else if (c == ')') {
               // Pop the sign and the previous result from the stack
               int prev_sign = stk.top(); stk.pop();
               int prev_result = stk.top(); stk.pop();

               current_result = prev_result + current_result * prev_sign; 
          }
          
          // Ignore Spaces
          i++;
     }
     
     return current_result;
}





// The Celebrity Problem                         [IMPORTANT]
int findCelebrity_1(vector<vector<int>> &M, int n) {
     stack<int> stk;
     
     // Step : 1 -> Push all the persons into the stack
     for (int i = 0; i < n; i++) {
          stk.push(i);
     }
     
     // Step : 2 -> run discard method to get mightBecelebrity
     while(stk.size() != 1){
          int a = stk.top(); stk.pop();
          int b = stk.top(); stk.pop();
          
          // If a knows b ??
          if (M[a][b]) {
               // a is not celebrity,
               // b might be
               stk.push(b);
          }

          else {
               // b is not celebrity,
               // a might be
               stk.push(a);
          }
     }
     
     // Step : 3 -> Check that single person is really a celebrity??
     int mightBecelebrity = stk.top(); stk.pop();
     
     // Everyone should know Celebrity
     for (int i = 0; i < n; i++) {
          if (M[mightBecelebrity][i] != 0){
               return -1;
          }
     }
     
     return mightBecelebrity;

}

bool isCandidate(int candidate,vector<vector<int>> &M, int n) {
     for (int i = 0; i < n; i++) {
          if (i!=candidate && (M[candidate][i] == 1 || M[i][candidate] == 0)) {
               return false;
          }
     }
     return true;
}

int findCelebrity_2(vector<vector<int>> &M, int n) {
     // Two-pointer approach
     int i = 0, j = n - 1;

     // Narrow down to a potential candidate
     while (i < j) {
          if (M[i][j] == 1) {
               // i knows j, so i can't be a celebrity, 
               // Move i forward
               i++;
          }

          else {
               // j knows i, so j can't be a celebrity, 
               // Move j backward
               j--;
          }
     }
     
     // i is now the candidate
     int candidate = i;
     
     if (isCandidate(candidate,M,n)){
          return candidate;
     }
     
     // No Celebrity Found
     return -1;
}




// Checkout LEETCODE : 1019 (Next Greater Element in LL) -> LINKED LIST folder

// Checkput LEETCODE : 901  (Oline Stock Pan)




// LEETCODE : 1003
bool isWordValid(string &s) {
     // Check 1st alphabet
     if (s[0] != 'a') return false;

     stack<char> stk;
     for (auto ch : s) {
          if (ch == 'a') {
               stk.push(ch);
          }

          else if (ch == 'b') {
               if (!stk.empty() && stk.top() == 'a') {
                    stk.push('b');
               }
               else {
                    return false;
               }
          }
          
          else {
               if (!stk.empty() && stk.top() == 'b') {
                    stk.pop();

                    if (!stk.empty() && stk.top() == 'a') {
                         stk.pop();
                    }
                    else {
                         return false;
                    }
               }
               else {
                    return false;
               }
          }
     }
     
     return stk.empty();

}




// LEETCODE : 394                                [IMPORTANT]
string decodeString(string s) {
     stack<int> countStack;     // Stack to hold the repeat counts
     stack<string> stringStack;   // Stack to hold the previous strings
     string currentString = "";
     int currentNum = 0;
     
     for (auto c : s) {
          if (isdigit(c)) {
               currentNum = currentNum * 10 + (c - '0');

          }
          
          else if (c =='[') {
               // Push the current count and string to their respective stacks
               countStack.push(currentNum);
               stringStack.push(currentString);

               // Reset for the new context
               currentNum = 0;
               currentString = "";
          }

          else if (c == ']') {
               int repeatCount = countStack.top(); countStack.pop();
               string prevString = stringStack.top(); stringStack.pop();
               
               // Repeat the currentString and append to the previous one
               string temp = "";
               for (int i = 0; i < repeatCount; i++) {
                    temp += currentString;
               }
               currentString = prevString + temp;
          }

          else {
               // It is a letter,
               // Accumulate it to the currentString
               currentString += c;
          }

     }
     return currentString;
}




// LEETCODE : 853   ( Car Fleet )
int carFleet(int target, vector<int>& position, vector<int>& speed) {
     int n = position.size();
     vector<pair<int,double>> cars;   // Pair of position and time to reach the target
     
     // Calculate time for each car to reach the target
     for (int i = 0; i < n; i++) {
          double time = (double)(target - position[i]) / (double)speed[i];
          cars.push_back({position[i], time});
     }
     
     // Sort cars by their starting position in Ascending order
     sort(cars.begin(), cars.end()), [] (const pair<int,double> &a, const pair<int,double> &b) {
          return a.first < b.first;
     };
     
     // Stack to store the times of fleets
     stack<double> fleetStack;
     for (int i = 0; i < n; i++) {
          double currentTime = cars[i].second;

          if (!fleetStack.empty() && currentTime >= fleetStack.top()) {
               fleetStack.pop();
          }

          fleetStack.push(currentTime);
     }
       
     return fleetStack.size();

}





// LEETCODE : 71 (Decode String)
void buildAns(stack<string> &s, string &ans) {
     // Base Case
     if (s.empty()) {
          return;
     }

     string minPath = s.top(); 
     s.pop();
     buildAns(s,ans);

     // Backtrack
     ans += minPath;
}

string simplifyPath(string path) {
     stack<string> s;
     int i = 0;
     while (i < path.size()) {
          int start = i;
          int end = i + 1;
          while (end < path.size() && path[end] != '/') {
               ++end;
          }
          string minPath = path.substr(start, end - start);
          i = end;   // DON'T FORGET

          if (minPath == "/" || minPath == "/.") {
               continue;
          }
          
          if (minPath != "/..") {
               s.push(minPath);
          }

          else if (!s.empty()) {
               s.pop();
          }
     }

     // IMPORTANT STEP
     string ans = s.empty() ? "/" : "";
     // Reverse the string
     buildAns(s,ans);
     return ans;
}





// LEETCODE : 735 (Aestroid Collison)            [IMPORTANT]
vector<int> asteroidCollision(const vector<int>& asteroids) {
     vector<int> stack;

     for (auto asteroid : asteroids) {
          bool exploded = false;

          while(!stack.empty() && asteroid < 0 && stack.back() > 0) {
               if (stack.back() < -asteroid) {
                    stack.pop_back();       // Right-moving asteroid is smaller and explodes.
                    continue;               // Check the next asteroid in the stack.
               }
               else if (stack.back() == -asteroid) {
                    stack.pop_back();       // Both asteroids explode.
               }

               exploded = true;
               break;
          }

          if (!exploded) {
               stack.push_back(asteroid);
          }
     }

     return stack;   // No collision or asteroid survived the collision.
}






int main() {
     // stack<int> s;
     // s.push(10);
     // s.push(20);
     // s.push(30);
     // s.push(40);
     // s.push(50);

     // sortedInsert(s,23);

     // cout << "Output: " << boolalpha << checkSorted(s,maxVal);

     vector<int> asteroids1 = {5, 10, -5};
     vector<int> result1 = asteroidCollision(asteroids1);
     for (int asteroid : result1) cout << asteroid << " "; // Output: 5 10
     cout << endl;

     // Example 2:
     vector<int> asteroids2 = {8, -8};
     vector<int> result2 = asteroidCollision(asteroids2);
     for (int asteroid : result2) cout << asteroid << " "; // Output: (empty)
     cout << endl;

     // Example 3:
     vector<int> asteroids3 = {10, 2, -5};
     vector<int> result3 = asteroidCollision(asteroids3);
     for (int asteroid : result3) cout << asteroid << " "; // Output: 10
     cout << endl;
     


     return 0;
}


















