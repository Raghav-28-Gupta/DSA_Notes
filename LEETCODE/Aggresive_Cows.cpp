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


//  Similar to ------>   Book Allocation Mathod




bool IsPossibleSoln ( vector<int> &stalls, int n , int k, int min ) {

     int cows = 1;
     int StartCow = stalls[0];

     for ( int i=1; i<n; i++ ) {
          if ( stalls[i] - StartCow >= min ) {
               cows++;                         // Increasing the cow count
               StartCow = stalls[i];           // replacing the value of the variable to next cow
          }

          if ( cows == k ) return true;
     }

     return false;

}




int AggresiveCows( vector<int> &stalls, int n , int k ) {

     sort(stalls.begin(),stalls.end());         // First sort to use binary search

     int low = 0;
     int high = stalls[n-1] - stalls[0];        // high --> Maximum stall position
     int ans = -1;

     while ( low<= high ){
          int mid = low + ( high - low )/2;

          if ( IsPossibleSoln ( stalls, n, k, mid ) ) {
               ans = mid;               // Mid --> Minimum distance 
               low = mid + 1;           // Getting closer to the real answer
          } 
          else {
               high = mid - 1;          // Neglecting all the elements right to the mid
          }                             // because mid is the MINIMUM which didn't satisfy the condition
     }

     return ans;

}



int main() {

     vector <int> stalls = { 10, 1, 2, 7, 5 };
     int n = stalls.size();
     int k = 3;

     cout << "The Minimum distance between the cows is: " << AggresiveCows( stalls, n , k ) << endl;

}