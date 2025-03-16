#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;

/*                          ""  (start)
                           /   \
                        "a"    ""  (decision at 'a')
                       /  \    /  \
                  "ab"     "a"  "b"  ""  (decision at 'b')
                 /   \   /   \  /   \  /   \
            "abc" "ab" "ac" "a" "bc" "b" "c" ""  (decision at 'c')

*/


void printSubsequences(string s, string current, int index) {
     // Base Case: If we've processed all characters
     if (index == s.length()) {
        cout << current << endl;
        return;
     }

     // Recursive Case: Two choices, include or exclude the current character

     // Include the current character
     printSubsequences(s, current + s[index], index + 1);

     // Here String s is not passed by reference,
     // So no need to pop().

     // Exclude the current character
     printSubsequences(s, current, index + 1);
}





void findSubsequencesSum_1(int index, int currentSum, int k, vector<int>& arr, vector<int>& currentSubsequence){
     // Printing all subsequences

     // Base Case: If we've reached the end of the array
     if (index == arr.size()){

          if (currentSum == k){
               for (auto c : currentSubsequence){
                    cout << c << " ";
               }
               cout << endl;
          }
          return;
     }

     // Include the current element in the subsequence
     currentSubsequence.push_back(arr[index]);
     findSubsequencesSum_1(index+1, currentSum + arr[index], k, arr, currentSubsequence);
     
     // Exclude the current element in the subsequence
     currentSubsequence.pop_back();
     findSubsequencesSum_1(index+1, currentSum, k, arr, currentSubsequence);

}

bool findSubsequencesSum_2(int index, int currentSum, int k, vector<int>& arr, vector<int>& currentSubsequence){
     // TECHNIQUE of Printing " ONLY 1 " subsequence

     // Base Case: If we've reached the end of the array
     if (index == arr.size()){
          if (currentSum == k){
               for (auto c : currentSubsequence){
                    cout << c << " ";
               }
               cout << endl;
               return true;
          }
          else return false;
     }

     // Include the current element in the subsequence
     currentSubsequence.push_back(arr[index]);
     if(findSubsequencesSum_2(index+1, currentSum + arr[index], k, arr, currentSubsequence) == true){
          return true;
     }
     
     // Exclude the current element in the subsequence
     currentSubsequence.pop_back();
     if(findSubsequencesSum_2(index+1, currentSum, k, arr, currentSubsequence) == true){
          return true;
     }

     return false;
}

int findSubsequencesSum_3(int index, int currentSum, int k, vector<int>& arr){
     // Counting Number of subSequences

     // Base Case: If we've reached the end of the array
     if (index == arr.size()){
          if (currentSum == k){
               return 1;
          }
          else return 0;
     }

     // Include the current element in the subsequence
     int Left = findSubsequencesSum_3(index+1, currentSum + arr[index], k, arr);
     
     // Exclude the current element in the subsequence
     int Right = findSubsequencesSum_3(index+1, currentSum, k, arr);
     
     return Left + Right;
}





// LEETCODE --> 39
void findCombinations(int index, vector<int>& candidates, int target, vector<int> &CurrentCombination, vector<vector<int>> &result ){
     // Base Case: If we've reached the end of the array
     if (target == 0) {
          result.push_back(CurrentCombination);
          return;
     }
     
     for (int i = index; i < candidates.size(); i++){
          if (candidates[i] <= target) {
               // Include the candidate in the current combination
               CurrentCombination.push_back(candidates[i]);
               // Recursively try to find combinations with the current candidate included
               findCombinations(i, candidates, target - candidates[i], CurrentCombination, result);
               // Exclude the candidate from the current combination
               CurrentCombination.pop_back();
          }
     }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> CurrentCombination;
    findCombinations(0, candidates, target, CurrentCombination, result);
    return result;
}




// LEETCODE --> 40
void findCombinations2(int index, vector<int>& candidates, int target, vector<int> &CurrentCombination, vector<vector<int>> &result ){
     // Base Case: If we've reached the end of the array
     if (target == 0) {
          result.push_back(CurrentCombination);
          return;
     }
     
     for (int i = index; i < candidates.size(); i++){
          // Skip duplicates
          if (i > index && candidates[i] == candidates[i - 1]) continue;

          if ( candidates[i] <= target) {
               // Include the candidate in the current combination
               CurrentCombination.push_back(candidates[i]);
               // Recursively try to find combinations with the current candidate included
               findCombinations2(i + 1, candidates, target - candidates[i], CurrentCombination, result);
               // Exclude the candidate from the current combination
               CurrentCombination.pop_back();
          }
     }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
     // IMPORTANT STEP 
     // This helps in easily skipping duplicates
     // Ensures that combinations are built in a sorted order.
     sort(candidates.begin(), candidates.end());
     
     vector<vector<int>> result;
     vector<int> CurrentCombination;
     findCombinations2(0, candidates, target, CurrentCombination, result);
     return result;
}





// LEETCODE --> 416 ( TLE )
bool canPartitionHelper(vector<int>& nums, int index, int target)  {
     // Base Case
     if (target == 0) return true;
     if (target < 0 || index >= nums.size()) return false;

     // Recursive cases: include or exclude the current element
     // If any ONE subSet is found then other will be defintely there
     return canPartitionHelper(nums, index + 1, target - nums[index]) || canPartitionHelper(nums, index + 1, target);
}

bool canPartition(vector<int>& nums) {
     int sum = accumulate(nums.begin(), nums.end(), 0);
     // If total sum is odd, we cannot partition it into two equal subsets
     if (sum % 2 != 0) return false;

     int target = sum/2;
     int index = 0;
     return canPartitionHelper(nums, index, target);
}





// LEETCODE --> 473
bool backtrack(vector<int>& matchsticks, vector<int>& sides, int index) {

     if (index == matchsticks.size()){
          // If all matchsticks are used, check if all sides are equal to target 
          return sides[0] == 0 && sides[1] == 0 && 
                 sides[2] == 0 && sides[3] == 0;
     }


     // Try to put the current matchstick in each side
     for (int i = 0; i < 4; i++) {
          if (matchsticks[index] <= sides[i]){
               sides[i] -= matchsticks[index];  // INCLUDE
               if (backtrack(matchsticks, sides, index + 1)) {
                    return true;
               }

               sides[i] += matchsticks[index];  // BACKTRACK
          }
     }

     return false;
}

bool makesquare(vector<int>& matchsticks) {

     auto TotalSum = accumulate(matchsticks.begin(), matchsticks.end(), 0);

     if (TotalSum % 4 != 0) return false;

     int SideSum = TotalSum / 4;

     // This helps in optimizing the backtracking by trying to fit the largest sticks first.
     sort(matchsticks.begin(), matchsticks.end(), greater<int>());

     vector<int> sides(4, SideSum);

     return backtrack(matchsticks, sides, 0);
        
}






// LEETCODE : 198 ( TLE )
int rob (vector<int>& nums, int i) {
     // Base Case
     if (i >= nums.size()){
          return 0;
     }

     // Option 1: Rob the current house and move to the house after the next one
     int robCurrent = nums[i] + rob(nums, i+2);

     // Option 2: Skip the current house and move to the next house
     int skipCurrent = 0 + rob(nums, i+1);

     return max(robCurrent, skipCurrent);

}
                                                   
int rob(vector<int>& nums) {
    return rob(nums, 0);
}





// LEETCODE : 322 ( TLE )
int minCoins(vector<int>& coins, int amount) {
     // Base Case : amount = 0
     if (amount == 0) return 0;
     // Base Change : amount is negative 
     if (amount < 0) return INT_MAX;

     int result = INT_MAX;

     for (auto coin : coins) {

          if ( coin <= amount ) {
               int subResult = minCoins(coins, amount-coin);

               if ( subResult != INT_MAX ){
                    int coinsUsed = 1 + subResult;
                    result = min(result, coinsUsed);
               }
          }
     }
     
     return result;

}
                                                            
int coinChange(vector<int>& coins, int amount) {
    int result = minCoins(coins, amount);

    // If result is still INT_MAX, it means it's impossible to make up the amount
    return (result == INT_MAX) ? -1 : result;
}





// LEETCODE : 1981 ( TLE )
int minimizeTheDifference(vector<vector<int>>& mat, int target, int row, int sum) {
     // Base Case : When all rows have been considered

     if (row == mat.size()) {
          return abs(target - sum);
     }
     
     int minDiff = INT_MAX;
     for (int col = 0; col < mat[row].size(); col++){
          int recAns = minimizeTheDifference(mat, target, row + 1, sum + mat[row][col]);
          minDiff = min(minDiff, recAns);
     }
     return minDiff;
}







// LEETCODE : 55 ( TLE )
bool canJump_1(vector<int>& nums, int index){
     // Base Case
     if (index >= nums.size()) return false;
     if (index == nums.size() - 1) return true;
     if (nums[index] == 0) return false;   // Stuck at the position

     bool result = false;
     for (int jump = 1; jump <= nums[index]; jump++){
          result = result || canJump_1(nums, index + jump);
     }

     return result;
}    

// LEETCODE : 45 ( TLE )  METHOD - 1
int minJumpsHelper(const std::vector<int>& nums, int currentIndex) {
     int n = nums.size();
    
     // Base case: when current position is the last or beyond
     if (currentIndex >= n - 1) {
        return 0;
     }

     // If we are at a position where we cannot move forward
     if (nums[currentIndex] == 0) {
        return INT_MAX;
     }
 
     int minJumps = INT_MAX;
     int maxReach = currentIndex + nums[currentIndex];

     // Explore all reachable positions
     for (int nextIndex = currentIndex + 1; nextIndex <= maxReach && nextIndex < n; ++nextIndex) {
          int jumps = minJumpsHelper(nums, nextIndex);
          if (jumps != INT_MAX) {
            minJumps = min(minJumps, jumps + 1);
          }
     }

     return minJumps;
}


// LEETCODE : 45 ( TLE )  METHOD - 2
void canJump_2(vector<int>& nums, int index, int &ans, int step){
     // Base Case
     if (index == nums.size() - 1){
          ans = min(ans,step);
          return;
     }
     if (index >= nums.size()) return;   

     for (int jump = 1; jump <= nums[index]; jump++){
          canJump_2(nums, index + jump, ans, step + 1);
     }

} 

int jump(vector<int> &nums){
     int ans = INT_MAX;
     canJump_2(nums, 0, ans, 0);
     return ans;
}







// LEETCODE : 120 ( TLE )
int minPathSumBottomUp(const vector<vector<int>>& triangle, int row, int col) {
     // Base case: if we are at the last row, return the current value
     if(row == triangle.size() - 1){
          return triangle[row][col];
     }
     
     int Directly_Downwards = triangle[row][col] + minPathSumBottomUp(triangle, row + 1, col);
     int Diagonal_Downwards = triangle[row][col] + minPathSumBottomUp(triangle, row+1, col + 1);

     return min(Directly_Downwards, Diagonal_Downwards);

}





// LEETCODE : 121 ( Buy and Sell Stock ) : Recursion
void maxProfit(vector<int>& prices, int index, int &minPrice, int &maxPrice){

     if (index == prices.size()) return;

     if (prices[index] < minPrice) minPrice = prices[index];
     int todayProfit = prices[index] - minPrice;

     if (todayProfit > maxPrice) maxPrice = todayProfit;
     
     maxProfit(prices, index + 1, minPrice, maxPrice);
}





// LEETCODE : 44 ( Wild Card Matching ) --> TLE
bool isMatch(string &s, string &p, int si, int pi) {

     if (si == s.size() && pi == p.size()) return true;

     if (si == s.size() && pi < p.size()){
          if ( p[pi] != '*') {
          return false;
          }
          return true;
     }
     
     if (s[si] == p[pi] || p[pi] == '?'){
          return isMatch(s, p, si + 1, pi + 1);
     }

     if (p[pi] == '*') {
          // Treating '*' as empty or null (as per question)
          bool caseA = isMatch(s, p, si, pi + 1);
          // Let '*' consume one char
          bool caseB = isMatch(s, p, si + 1, pi);

          return caseA || caseB;
     }
     // Char doesn't exist
     return false;
}





// LEETCODE : 1155 ( Number Of Dice Rolls With Target Sum )
int numRollsToTarget(int n, int k, int target) {
     // Base Case
     if (n == 0 && target == 0) return 1;
     if (n == 0 && target != 0) return 0;
     if (n != 0 && target == 0) return 0;
     if (target < 0) return 0;

     int numRoll = 0;

     for (int i = 1; i <= k; i++){
          if (i > target) return 0;
          if (i == target) return 1;
          numRoll += numRollsToTarget(n - 1, k, target - i); 
     }

     return numRoll;
}





// LEETCODE : 279 (Perfect Squares)
int numSquares(int n) {
     // Base Case
     if (n == 0) return 0;

     int ans = INT_MAX;

     for (int i = 1; i <= sqrt(n); i++) {
          int perfectSquare = i * i;
          // Recursively find the minimum number of squares for (n - square).
          ans = min(ans, numSquares(n - perfectSquare) + 1);
          // Without '+1', the result would ignore the square currently being considered.
     }

     return ans;

}





// LEETCODE : 983 (Minimum Cost For Tickets)
int mincostTickets(vector<int>& days, vector<int>& costs, int index) {
     // Base Case
     if (index == days.size()) return 0;

     // 1 Day Pass taken
     int oneDay = costs[0] + mincostTickets(days, costs, index + 1);



     // 7 Days Pass taken
     int passEndDay = days[index] + 7 - 1;
     int j = index;
     while (days[j] <= passEndDay && j < days.size()) {
          j++;
     }
     int sevenDay = costs[1] + mincostTickets(days, costs, j);



     // 30 Days Pass taken
     passEndDay = days[index] + 30 - 1;
     j = index;
     while (days[j] <= passEndDay && j < days.size()) {
          j++;
     }
     int thirtyDay = costs[2] + mincostTickets(days, costs, j);



     return min(oneDay , min(sevenDay, thirtyDay));

}






int main() {
     vector<int> candidates1 = {10, 1, 2, 7, 6, 1, 5};
     int target1 = 8;
     vector<vector<int>> result1 = combinationSum2(candidates1, target1);

     cout << "Example 1 Output: " << endl;
     for (auto& combination : result1) {
          cout << "[ ";
          for (int num : combination) {
            cout << num << " ";
          }
          cout << "]" << endl;
     }


     return 0;
}

