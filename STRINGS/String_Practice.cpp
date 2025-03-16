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




bool CheckPlaindrome ( string s, int i, int j ) {      // ------            

     while ( i <= j ) {
          if ( s[i] != s[j] ) return false;
          else i++; j--;
     }

     return true;
}
                                                       //      |----->  LEETCODE ---> 680
int ValidPalindrome ( string s ) {                     // ------            

     int i = 0;
     int j = s.length() - 1;

     while ( i<=j ) {

          if ( s[i] == s[j] ){
               i++; j--;
          }

          else {
               // Checking by deleting ith character
               bool Possibility_1 = CheckPlaindrome ( s, i+1, j );  
               // Checking by deleting jth character        
               bool Possibility_2 = CheckPlaindrome ( s, i, j-1 );
               return Possibility_1 || Possibility_2;
          }
     }
}




string DecodeMessage ( string key, string message ) {                // LEETCODE ---> 2325
 
     unordered_map <char,char> mapping ;
     char space = ' ';                                         // IMPORTANT
     mapping [space] = space;

     char start = 'a';
     int index = 0;

     while ( index < key.length() && start <= 'z' ) {

          char IndexCharacter = key[index];

          if ( mapping.find( IndexCharacter ) != mapping.end() ){               // To check the repeatition 
               index++;
          } 

          else {
               mapping [IndexCharacter] = start;
               index++;
               start++;
          }   
     }

     string ans = "";

     for ( int i=0; i<message.length(); i++ ){

          char ch = message[i];

          ans.push_back( mapping[ch] );
     }
     
     return ans;
}




string customSortString_1(const string& order, const string& s) {
    string sortedString = s;

    // Lambda function to compare two characters based on their order in the 'order' string
    
    auto cmp = [&order] (char a, char b) {
        return order.find(a) < order.find(b);
    };

    sort(sortedString.begin(), sortedString.end(), cmp);

    return sortedString;
}

string customSortString_2(const string& order, const string& s) {

     unordered_map <char,int> CharCount;
     string result = "";

     for ( auto i : s ) {
          CharCount[i]++;
     }

     for ( auto i : order ){

          if ( CharCount.find(i) != CharCount.end() ) {
               result.push_back(i);
               CharCount.erase(i);
          }
     }

     for ( auto i : CharCount ) {
          result.push_back(i.first);
     }

     return result;

}



string longestCommonPrefix ( vector<string>& strs ) {                // LEETCODE ---> 14

     if ( strs.size() == 0 ) return "";
     // Initialize the prefix as the first string in the vector
     string prefix = strs[0];

     for ( auto c : strs ) {
          // While the current string doesn't start with the prefix
          while ( c.find(prefix) != 0 ) {
               // Shorten the prefix by removing the last character
               prefix = prefix.substr( 0, prefix.length()-1 );
               
               // If the prefix becomes empty, there is no common prefix
               if ( prefix.empty() ) return "";
          }
     }

     return prefix;
}



vector<vector<string>> GroupAnagrams( vector<string> & strs ) {      // LEETCODE ---> 49
    
     unordered_map <string, vector<string>> Group;

     for ( auto c : strs ) {
          string key = c;
          sort ( key.begin(), key.end() );
          Group[key].push_back(c);
     }

     vector<vector<string>> ans;

     for ( auto s : Group ) {
          ans.push_back(s.second);
     }

     return ans;

}





int ExpandAroundCentre(const std::string& s, int left, int right) {

    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;     // Gives the size of the string
}

string longestPalindrome(string s) {

    int n = s.length();
    if (n < 2) return s;

    int start = 0, maxLength = 1;

    for (int centre = 0; centre < n; ++centre) {
        // Check for odd-length palindromes
        int len1 = ExpandAroundCentre(s, centre, centre);
        // Check for even-length palindromes
        int len2 = ExpandAroundCentre(s, centre, centre + 1);

        int len = max(len1, len2);

        if (len > maxLength) {
            maxLength = len;
            start = centre - (len - 1) / 2;          // -----> To find starting point using length of the string
        }
    }

    return s.substr(start, maxLength);
}





int first_Occurrence_String_1 (string haystack, string needle) {       // LEETCODE ---> 28    
     if (needle.length() == 0) return 0;

     int h = haystack.length();
     int n = needle.length();

     for ( int i=0; i <= h-n; i++ ) {        //  (h-n) ---> The last valid starting position for a potential match
          int j ;
          for ( j=0; j<n; j++ ) {
               if ( haystack[i+j] != needle[j] ) {
                    break;
               }

               if ( j == n-1 ) return i;
          }
     }

     return -1; 
}

int first_Occurrence_String_2 (string haystack, string needle) {       // --> SLIDING WINDOW 
     if (needle.length() == 0) return 0;                               

     int h = haystack.length();
     int n = needle.length();
     
     // Sliding window
     for ( int i=0; i <= h-n; i++ ) {           //  (h-n) ---> The last valid starting position for a potential match
          // Check if the window matches the needle
          if ( haystack.substr(i,n) == needle ) {
               return i;
          }
     }

     return -1; 
}

void removeOCCRE (string &s, string &part){                            // LEETCODE --> 1910

     int found = s.find(part);

     if (found != string::npos){
          // s.erase(found, part.length());
          //                        OR
          string left_part = s.substr(0,found);
          string right_part = s.substr(found+part.length(), s.length());
          s = left_part + right_part;

          removeOCCRE(s, part);
     }
     else {
          // Base Case
          // All the occurences have been removed
          return;
     }
}

   



int myAtoi (string s) {                                                // LEETCODE --> 8

     int n = s.length();
     int i = 0;

     while ( i < n && i == ' ') i++;

     int sign = 1;

     if (i<n &&  ( ( s[i] == '+') || ( s[i] == '-') )) {
          sign = s[i] = '+'? 1: -1;
          i++;
     }
     
     int long long result = 0;
     while ( i<n && ( isdigit(s[i]) ) ) {
          long long result = result + ( s[i] - '0');
          // Step 4: Check for overflow/underflow
          if ( result*sign > INT_MAX ) return INT_MAX;
          if ( result*sign < INT_MIN ) return INT_MIN;

          i++;

     }

     return result;
}





string intToRoman (int num) {                                          // LEETCODE --> 12

     // Define the values and their corresponding Roman numeral symbols
     vector<pair<int,string>> valueSymbols = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, 
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, 
        {5, "V"}, {4, "IV"}, {1, "I"}
     };
     
     string roman;

     for ( const auto &pair : valueSymbols ) {
          int value = pair.first;
          const string symbol = pair.second;

          while ( num >= value ) {
               roman += symbol;
               num -= value;
          }

     }

     return roman;

}
// Similar in String_Practice_2




int compare ( string &a, string &b ) {

// EXAMPLE : { 3, 30 }   ---->   LARGEST NO. IS : 330   NOT   303
     return a+b > b+a;
}

string largestNumber (vector<int>& nums) {

     vector <string> numStr;

     for ( int i : nums ) {
          numStr.push_back( to_string(i) );
     }

     sort ( numStr.begin(), numStr.end(), compare );

     if ( numStr[0] == "0" ) return "0";


     string result;
     for ( auto c : numStr ) {
          result += c;
     }

     return result;

}






int convertToMinutes ( string &time ){                        // -----

     int hours = stoi( time.substr(0,2) );  // The first parameter is the starting position of the substring.
     int minutes = stoi( time.substr(3,2) );  // The second parameter is the length of the substring.
     return 60*hours + minutes;
}
                                                              //      |-->  LEETCODE : 539
int findMinDifference (vector<string> &timePoints) {          // -----

     vector <int> minutes;

     for ( string time : timePoints) {
          minutes.push_back( convertToMinutes(time) );
     }           
     
     sort( minutes.begin(), minutes.end() );

     int MinDiff = INT_MAX;
     for ( int i=1; i<minutes.size(); i++ ) {
          MinDiff = min ( MinDiff, minutes[i]-minutes[i-1] );
     }

     // Circular difference between the first and last time points
     int CircularTimeDiff = 1440 - minutes.back() + minutes [0];
     
     MinDiff = min ( MinDiff, CircularTimeDiff );
     
     return MinDiff;

    }





string RemoveAdjacentDuplicates_1 (string s, int k) {         // ------
     // TWO POINTER METHOD 

     vector<int> count(s.size(), 1);

     int i = 0;   // i is the index for the final result string
     for ( int j=0; j< s.length(); i++, j++) {

          s[i] = s[j];     // Move the current character to the 'result' position

          if ( i>0 && s[i] == s[i-1] ) {
               count[i] = count[i-1] + 1;    // Increment the count of the current character
          }
          else {
               count[i] = 1;  // Reset the count for a new character
          }

          if ( count[i] == k ){
               i -= k;       // If the count reaches k, remove the last k characters
          }
     }

     return s.substr(0,i);    // The resulting string is the first i characters of s
        
}
                                                              //      |---> LEETCODE : 1209
string RemoveAdjacentDuplicates_2 (string s, int k) {         // ------

     vector<pair<char,int>> count;

     for ( auto c : s ) {

          if ( !count.empty() && count.back() == c ) {
               // If the last character in the vector is the same as the current one
               // Increment the count
               count.back().second++;
               // If the count reaches k, pop the last element
               if ( count.back().second == k ) {
                    count.back().pop;
               }    
          }

          else {
               // Otherwise, push the current character with a count of 1
               count.push_back({c,1});
          }
     }
     
     // Reconstruct the string from the count vector
     string result;

     for ( auto &c : count ) {
          // This line appends the character p.first to the result string p.second times.
          result.append( c.first, c.second )
     }
     
     return result;
}





/*
int NumberOfBeams ( const vector<string> &bank ) {            // LEETCODE ---> 2125

     vector <int> DeviceCount;

     for ( const string &row : bank ) {
          int Count = count (row.begin(), row.end(), '1');
          DeviceCount.push_back(Count);
     }

     int Totalbeams = 0;

     for ( int i=0; i<DeviceCount.size(); i++ ) {
          int j = i+1;

          if ( j < DeviceCount.size() ) {
               Totalbeams += DeviceCount[i] * DeviceCount[j];
               if ( DeviceCount[j] == 0 ) {
                    j++;
               }
               else {
                    break;
               }
          }
     }

     return Totalbeams;
}


*/





int main() {
     int num1 = 123;
     int num2 = 359;
     cout << "Numeber: " << numberToWords(num1) << endl;
     cout << "Numeber: " << numberToWords(num2) << endl;

     return 0;
}