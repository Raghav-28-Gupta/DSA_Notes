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

/*


                                    [38, 27, 43, 3, 9, 82, 10]
                                    /                         \
                       [38, 27, 43]                           [3, 9, 82, 10]
                        /      \                              /           \
               [38, 27]       [43]                    [3, 9]               [82, 10]
                /   \                                /     \                /    \
           [38]    [27]                            [3]     [9]            [82]  [10]
               \    /                                 \    /                 \   /
           [27, 38]                                 [3, 9]                [10, 82]
                  \                                 /                       /
                  [27, 38, 43]                     [3, 9, 10, 82]
                             \                     /
                            [3, 9, 10, 27, 38, 43, 82]


*/


void merge(vector<int>& arr, int left, int mid, int right) {
     int n1 = mid - left + 1; // Size of left subarray
     int n2 = right - mid;    // Size of right subarray

     // Create temporary subarrays
     vector<int> leftArr(n1);
     vector<int> rightArr(n2);

     // Copy data to temporary subarrays
     for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
     }
     for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
     }


     int i = 0;  // Initial index of left subarray
     int j = 0;  // Initial index of right subarray
     int k = left;  // Initial index of merged subarray

     while (i < n1 && j < n2) {
          if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
          } else {
            arr[k] = rightArr[j];
            j++;
          }

          k++;
     }

     // Copy any remaining elements of leftArr[], if any
     while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
     }

     // Copy any remaining elements of rightArr[], if any
     while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
     }
}

void mergeSort(vector<int>& arr, int left, int right) {
     if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
     }
}



void quickSort (vector<int>& arr, int start, int end) {
     // Base Case
     if (start >= end) return;

     int pivot = end;
     int i = start - 1;
     int j = start;

     while (j < pivot){
          if (arr[j] < arr[pivot]) {
               i++;
               swap(arr[i], arr[j]);
          }
          j++;
     }
     i++;
     swap(arr[i], arr[pivot]);

     quickSort(arr, start, i-1);
     quickSort(arr, i+1, end);
}





// Merge Sort (with S.C : O(1) )
void merge_2(vector<int>& arr, int left, int mid, int right) {
     int totalLength = right - left + 1;
     int gap = totalLength / 2 + totalLength % 2;  // Ceil(totalLength / 2)

     while (gap > 0){
          int i = left;
          int j = gap + i;

          while (j <= right){
               if (arr[i] > arr[j]){
                    swap(arr[i], arr[j]);
               }
               i++, j++;
          }
          
          gap = gap <= 1 ? 0 : (gap / 2) + (gap % 2);
     }
}

void mergeSort_2(vector<int>& arr, int left, int right) {
     if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort_2(arr, left, mid);
        mergeSort_2(arr, mid + 1, right);

        // Merge the sorted halves
        merge_2(arr, left, mid, right);
     }

}






// Count Inversions (Application of Merge Sort)
long mergeAndCount(vector<int>& arr, vector<int>& temp, int start, int mid, int end){
     int i = start;
     int j = mid + 1;
     int k = start;

     int inversions = 0;

     while (i <= mid && j <= end) {
          if (arr[i] < arr[j]) {
               temp[k++] = arr[i++];
          }

          else {
               temp[k++] = arr[j++];
               // Count inversions
               inversions += (mid + 1) - i;   
               // The number of elements remaining in the left subarray 
               // starting from index i to mid is (mid - i + 1)
          }
     }

     while (i <= mid) {
          temp[k++] = arr[i++];
     }

     while (j <= end) {
          temp[k++] = arr[j++];
     }

     while (start <= end){
          arr[start] = temp[start];
          start++;
     }


     return inversions;

}

long mergeSortAndCount(vector<int>& arr, vector<int>& temp, int start, int end) {
     
     long inversions = 0;

     if (start < end) {
        int mid = start + (end - start) / 2;

        // Count inversions in the left subarray
        inversions += mergeSortAndCount(arr, temp, start, mid);

        // Count inversions in the right subarray
        inversions += mergeSortAndCount(arr, temp, mid + 1, end);

        // Count inversions during merge
        inversions += mergeAndCount(arr, temp, start, mid, end);
     }

     return inversions;
}

long numberOfPermutations(vector<int>& arr) {
     long inversions = 0;
     vector<int> temp(arr.size(),0);

     inversions = mergeSortAndCount(arr, temp, 0, arr.size() - 1);
     return inversions;
}





// LEETCODE : 53 (T.C : O(n log n))
int maxCrossingSum(vector<int>& nums, int left, int mid, int right) {
     int leftSum = INT_MIN;
     int sum = 0;

     for (int i = mid; i >= left; i--) {
          sum += nums[i];
          if (sum > leftSum) {
               leftSum = sum;
          }
     }
     
     int rightSum = INT_MIN;
     sum = 0;

     for (int j = mid + 1; j <= right; j++) {
          sum += nums[j];
          if (sum > rightSum) {
               rightSum = sum;
          }
     }
     
     return leftSum + rightSum;

}

int maxSubArray(vector<int>& nums, int left, int right) {
     // Base Case
     if (left == right){
          return nums[left];
     }

     int mid = left + (right - left) / 2;
     
     int maxLeftSum = maxSubArray(nums, left, mid);
     int maxRightSum = maxSubArray(nums, mid + 1, right);
     int maxCrossSum = maxCrossingSum(nums, left, mid, right);


     return max({maxLeftSum, maxRightSum, maxCrossSum});
}



/*___________________________________________________________________________________________________________________________*/




void permute(vector<int>& nums, int index, vector<vector<int>> &result) {
     // Base Case
     if (index == nums.size()) {
          result.push_back(nums);
          return;
     }

     for (int j = index; j < nums.size(); j++) {
          // Swap to create a new permutation
          swap(nums[index], nums[j]);

          permute(nums, index + 1, result);

          // Swap back to restore the order
          // Backtracking
          swap(nums[index], nums[j]);
     }

}
// Checkout LEETCODE : 60






// LEETCODE : 131 (Palindrome Partitioning)
// METHOD : 1
bool IsPalindrome(string &s, int start, int end) {
     while (start < end) {
          if (s[start] != s[end]){
               return false;
          }
          start++;
          end--;
     }

     return true;
}

void partition_1(string &s, int start, vector<string> &CurrentString, vector<vector<string>> &result) {
     // Base Case
     if (start == s.length()){
          result.push_back(CurrentString);
          return;
     }

     
     for (int i = start; i < s.length(); i++) {
          // Check if the substring is a palindrome
          if (IsPalindrome(s, start, i)){

               CurrentString.push_back(s.substr(start, i - start + 1));

               partition_1(s, i + 1, CurrentString, result);
               
               // Backtrack
               CurrentString.pop_back();
          }
     }

}


// METHOD : 2 (Expand around Centre Approach)
vector<string> expandAroundCentre (string &s, int left, int right) {
     vector<string> palindromes;
     while (left >= 0 && right < s.length() && s[left] == s[right]) {
          palindromes.push_back(s.substr(left, right - left + 1));
          left--;
          right++;
     }

     return palindromes;
}

void partition_2(string &s, int start, vector<string> &CurrentString, vector<vector<string>> &result) { 
     // Base Case
     if (start == s.length()){
          result.push_back(CurrentString);
          return;
     }

     for (int i = start; i < s.length(); i++) {
          vector<string> palindromes = expandAroundCentre (s, start, i);

          for (auto palindrome : palindromes) {
               CurrentString.push_back(palindrome);
               partition_2(s, i + 1, CurrentString, result);
               // Backtrack
               CurrentString.pop_back();
          }

     }


}







// Rat And Maze Problem
void findPaths (vector<vector<int>> &mat, int x, int y, int n, string path, vector<string> &paths) {

     // Base case: if the rat reaches the destination
     if (x == n-1 && y == n-1) {
          paths.push_back(path);
          return;
     }
     

     // Mark the current cell as visited
     // IMPORTANT STEP
     mat[x][y] = 0;
     


     // Moving UP
     if (x + 1 < n && mat[x+1][y] == 1){
          findPaths(mat, x+1, y, n, path + "D", paths);
     }
     
     // Moving UP
     if (x - 1 <= 0 && mat[x-1][y] == 1){
          findPaths(mat, x-1, y, n, path + "U", paths);
     }

     // Moving RIGHT
     if (y + 1 < n && mat[x][y+1] == 1){
          findPaths(mat, x, y+1, n, path + "R", paths);
     }
     
     // Moving LEFT
     if (y - 1 <= 0 && mat[x][y-1] == 1){
          findPaths(mat, x, y-1, n, path + "L", paths);
     }
     


     // IMPORTANT STEP
     // Backtrack: Unmark the current cell as visited
     mat[x][y] = 1;

}

vector<string> findAllPaths (vector<vector<int>> &mat, int n) {
     vector<string> paths;

     // Check if the starting point is blocked
     if (mat[0][0] == 0 || mat[n-1][n-1] == 0) {
          return paths;
     }
     
     findPaths(mat, 0, 0, n, "", paths);

     sort(paths.begin(), paths.end());
     
     return paths;
}







// LEETCODE : 51 (N-Queens I)
bool IsSafe(int row, int col, vector<string> &board, int n) {

     // Check the column LEFTWARDS
     for (int i = col - 1; i >= 0; i--) {
          if (board[row][i] == 'Q'){
               return false;
          }
     }
     
     // Check the left UPPER diagonal
     for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
          if (board[i][j] == 'Q'){
               return false;
          }
     }

     // Check the left LOWER diagonal
     for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
          if (board[i][j] == 'Q'){
               return false;
          }
     }

     return true;

}

void solve(int n, vector<string> &board, vector<vector<string>> &solutions, int col) { 
     if (col == n) {
          solutions.push_back(board);
          return;
     }

     for (int row = 0; row < n; row++) {
          // Check if the current position is safe
          if (IsSafe(row, col, board, n)){
               board[row][col] = 'Q';

               solve(n, board, solutions, col + 1);

               // Backtrack
               board[row][col] = '.';
          }
     }
}

vector<vector<string>> solveNQueens(int n) {

     vector<vector<string>> solutions;
     // Creating a 2D board of size 'n x n'

     vector<string> board (n, string(n, '.'));
     int col = 0;

     solve(n, board, solutions, col);

     return solutions;

}








// LEETCODE : 37 (Sudoku Solver)
bool isValid (vector<vector<char>>& board, int row, int col, char num) {

     for (int i = 0; i < 9; i++) {

          if (board[row][i] == num) return false;

          if (board[i][col] == num) return false;

          if ( board[3 * (row/3) + i / 3] [3 * (col/3) + i % 3] == num) return false;
     }
     
     return true;
}

bool solveSudoku (vector<vector<char>>& board) {

     for (int row = 0; row < 9 ; row++) {
          for (int col = 0; col < 9; col++) {
               if (board[row][col] == '.') {
                    for (char num = '1'; num <= '9'; num++){
                         if (isValid(board, row, col, num)){
                              board[row][col] = num;
                              if (solveSudoku(board) == true) {
                                   return true;
                              }
                              else {
                                   // Backtrack
                                   board[row][col] = '.';
                              }
                         }
                    }
                    return false;
               }
          }
     }
     // All Filled
     return true;
}







// LEETCODE : 17
void backtrack(string &digits, int index, string &current, vector<string> &result, vector<string> &letterMap) {
     // Base Case
     if (index == digits.length()) {
          result.push_back(current);
     }
     
     int number = digits[index] - '0';

     for (auto letter : letterMap[number]) {
          current.push_back(letter);
          backtrack(digits, index + 1, current, result, letterMap);
          current.pop_back();
     }

}

vector<string> letterCombinations(string &digits){
     
     vector<string> letterMap = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
     };

     int index = 0;
     vector<string> result;
     string current;
     backtrack(digits, index, current, result, letterMap);

     return result;

}






// RESTRICTED RECURSION

// LEETCODE : 22
void generateParenthesis (int n, int open, int close, string current, vector<string> &result) {
     // Base Case
     if (current.length() == n * 2) {
          result.push_back(current);
          return;
     }

     // If we can add an open parenthesis, do so
     if (open < n) {
          generateParenthesis(n, open + 1, close, current + "(", result);
     }
     

     // You can only add a closing parenthesis ')'
     // If there are unmatched opening parentheses '('
     // This prevents creating sequences like ' ()) '
     // Where the closing parenthesis would not have a matching opening parenthesis.

     if (close < open) {
          generateParenthesis(n, open, close + 1, current + ")", result);

     }

}

// Similarly
void generateBinaryStrings(int n, int zeros, int ones, string current, vector<string> &result) {
     // If the current string is a valid binary string, add it to the result
     if (current.length() == n * 2) {
        result.push_back(current);
        return;
     }

     // If we can add a zero, do so
     if (zeros < n) {
        generateBinaryStrings(n, zeros + 1, ones, current + "0", result);
     }


     // In a valid binary string with equal numbers of 0s and 1s, 
     // you can only add a '1' if there are more or an equal number of '0's already added. 
     // This prevents creating sequences like "1100", which is invalid 
     // because you can't have more 1s than 0s at any point.
     if (ones < zeros) {
        generateBinaryStrings(n, zeros, ones + 1, current + "1", result);
     }
}







// LEETCODE : 79 (Word Search)
// Using Depth-First Search (DFS) Algorithm

bool dfs (vector<vector<char>>& board, string &word, int row, int col, int index) {
     // Base Case I
     if (index == word.length()) {
          return true;
     }

     // Base Case II
     if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index]){
          return false;
     }


     // I've reached here means, current ith word char has matched
     char temp = board[row][col];
     board[row][col] = '#';     // mark as visited



     bool found = dfs(board, word, row + 1, col, index + 1) ||
                  dfs(board, word, row - 1, col, index + 1) ||
                  dfs(board, word, row, col + 1, index + 1) ||
                  dfs(board, word, row, col - 1, index + 1);



     board[row][col] = temp;  // unmark as visited     

     return found;

}

bool exist(vector<vector<char>>& board, string word) {

     int rows = board.size();
     int cols = board[0].size();

     for (int i = 0; i < rows; i++){
          for (int j = 0; j < cols; j++){
               if (dfs(board, word, i, j, 0)){
                    return true;
               }
          }
     }
     return false;
}






// LEETCODE : 473
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





// LEETCODE : 526 (Beautiful Arrangement)
void countArrangementHelper(vector<int>& result, int& n, int& count, int currentNum) {
     if (currentNum == n + 1){
          ++count;
          return;
     }
     
     for (int i = 1; i <= n; i++) {
          if (result[i] == 0 && (i % currentNum == 0 || currentNum % i == 0)){
               result[i] = currentNum;
               countArrangementHelper(result, n, count, currentNum + 1);
               result[i] = 0; // Backtracking
          }
     }
}

int countArrangement(int n){
     vector<int> result(n + 1, 0);
     int count = 0;
     countArrangementHelper(result, n, count, 1);

     return count;

}





// LEETCODE : 1655
bool canDistributeHelper(vector<int>& countItems, vector<int>& quantity, int currCustomer) {
     if (currCustomer == quantity.size()){
          return true;
     }

     for (int i = 0; i < countItems.size(); i++) {
          if (countItems[i] >= quantity[currCustomer]){
               countItems[i] -= quantity[currCustomer];
               if (canDistributeHelper(countItems, quantity, currCustomer + 1)){
                    return true;
               }
               countItems[i] += quantity[currCustomer];   // BACKTRACK
          }
     }

     return false;
}

bool canDistribute(vector<int>& nums, vector<int>& quantity){
     // Sort Desc to reduce T.L
     sort(quantity.rbegin(), quantity.rend());

     unordered_map<int,int> countItem;
     for (int i = 0; i < nums.size(); i++) {
          countItem[nums[i]]++;
     }

     vector<int> countItems;
     for (auto& it : countItem) {
          countItems.push_back(it.second);
     }

     return canDistributeHelper(countItems, quantity, 0);
}






int main() {
     vector<int> nums = {1,2,3,4};
     vector<int> quantity = {2};

     cout << boolalpha << canDistribute(nums, quantity) << endl;
    
    return 0;
}