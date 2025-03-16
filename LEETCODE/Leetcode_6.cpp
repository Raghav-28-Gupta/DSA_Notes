#include <iostream>
#include<vector>
#include <string>
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

// ZIG-ZAG CONVERSION


string convert(string s, int numRows) {

     if ( numRows == 1 || numRows >= s.length()  ) return s;

     vector <string> pattern ( min( numRows, int(s.length()) ) );

     int currentRow = 0;
     bool goingDown = false;
    
    // Iterate over the characters in the string
    for (char c : s) {
        // CONCATINATION   NOT -->  PUSH_BACK
        pattern[currentRow] += c;
        // If we are at the first or last row, we change direction
        if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
        }
        // Move up or down
        currentRow += goingDown ? 1 : -1;
     }

     string result;

     for ( auto c : pattern ) {
          // CONCATINATION   NOT -->  PUSH_BACK
          result += c;           
     }

     return result;
     
}



int main() {
    // Test cases
    std::string s1 = "PAYPALISHIRING";
    int numRows1 = 3;
    std::cout << "Converted string for \"" << s1 << "\" with " << numRows1 << " rows: " << convert(s1, numRows1) << std::endl;
    
    std::string s2 = "PAYPALISHIRING";
    int numRows2 = 4;
    std::cout << "Converted string for \"" << s2 << "\" with " << numRows2 << " rows: " << convert(s2, numRows2) << std::endl;
    
    std::string s3 = "A";
    int numRows3 = 1;
    std::cout << "Converted string for \"" << s3 << "\" with " << numRows3 << " rows: " << convert(s3, numRows3) << std::endl;
    
    return 0;
}