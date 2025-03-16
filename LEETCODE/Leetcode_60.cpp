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



// PERMUTATION SEQUENCE


string getPermutation(int n, int k) {

     vector<int> factorial(n, 1);
     vector<int> numbers;
     
     // Fill numbers with [1, 2, ..., n]
     for (int i = 1; i <= n; i++) {
          numbers.push_back(i);
     }
     
     // Precompute the factorials
     for (int i = 1; i < n; i++) {
          factorial[i] = factorial[i-1] * i;
     }

     // Convert k to zero-indexed
     k--;


     // IMPORTANT STEP
     string result;

     for (int i = n; i > 0; i--) {
          int idx = k / factorial[i-1];
          result += to_string(numbers[idx]);
          numbers.erase(numbers.begin() + idx);
          k %= factorial[i-1];
     }

     return result;

}



int main() {
    int n = 4;
    int k = 9;
    cout << getPermutation(n, k) << endl;  // Output: "2314"
    return 0;
}