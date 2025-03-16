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


// Expand Around Center Method


int ExpandAroundCenter ( string s, int i, int j ) {
     int count = 0;
     while ( i >= 0 && j < s.length() && s[i] == s[j] ){
          count += 1;
          i--;
          j++;
     }

     return count;
}


int CountSubstring ( string s ) {                              

     int TotalCount = 0;

     for ( int centre=0; centre<s.length(); centre++ ) {
          // First checking odd substrings
          int i = centre;
          int j = centre;
          int CountOddSubStr = ExpandAroundCenter ( s, i, j );
          // Now checking Even substring
          i = centre;
          j = centre+1;
          int CountEvenSubStr = ExpandAroundCenter ( s, i, j );

          TotalCount += CountOddSubStr + CountEvenSubStr;  
     }

     return TotalCount;
}




int main () {

     string s = "abc";
     cout << CountSubstring ( s ) << endl;         // Output ---> 3

     return 0;
}