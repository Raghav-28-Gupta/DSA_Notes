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



int beautySum(string s) {                         // LEETCODE --> 1781

     int n = s.size();
     int TotalBeautySum = 0;

     for (int i = 0; i < n; i++) {
          unordered_map <char,int> CharCount;

          for (int j = i; j < n; j++) {
               char &ch = s[j];
               CharCount[ch]++;

               int maxCount = INT_MIN;
               int minCount = INT_MAX;

               for (auto &c : CharCount) {
               maxCount = max(maxCount, c.second);
               minCount = min(minCount, c.second); 
               }
          
               int Beauty = maxCount - minCount;
               TotalBeautySum += Beauty;
          }
     }

     return TotalBeautySum;

}



int Sherlock_And_Anagrams (string s) {

     int n = s.length();

     vector <string> subStrings;

     for (int i = 0; i<n; i++) {
          for (int j = i; j<n; j++) {
               string sub = s.substr(i,j-i+1);
               subStrings.push_back(sub);
          }
     }

     unordered_map <string,int> group;

     for (auto ch : subStrings) {
          string key = ch;
          sort(key.begin(),key.end());
          group[key]++;
     }

     int count = 0;


     for (auto &c : group) {
          if ( c.second > 1 ) {
               // Combination nC2
               count += (c.second * (c.second - 1)) / 2;          
          }
          
     }
     
     return count;
}



string reverseWords (string s) {                  // LEETCODE --> 151

     vector <string> words;
     string word;

     int n = s.size();
     int i = 0;
     while( i < n ) {
          // Skipping Spaces
          while ( i < n && isspace(s[i]) ) {
               i++;
          }
          
          word.clear();            // IMPORTANT

          while ( i < n && !isspace(s[i]) ) {
               word += s[i];
               i++;
          }

          if ( !word.empty() ){
               words.push_back(word);
          }
     }

     reverse( words.begin(), words.end() );

     string result;
     for (int i = 0; i < words.size(); i++){
          result += words[i];
          // Putting Spaces
          if (i < words.size()-1){
               result += " ";
          }
     }

     return result;
     
}



string numberToWords(int num) {                   // LEETCODE --> 273

     vector<pair<int, string>> numberWordsPairs = {
        {1000000000, "Billion"}, {1000000, "Million"}, {1000, "Thousand"}, {100, "Hundred"},
        {90, "Ninety"}, {80, "Eighty"}, {70, "Seventy"}, {60, "Sixty"}, {50, "Fifty"},
        {40, "Forty"}, {30, "Thirty"}, {20, "Twenty"}, {19, "Nineteen"}, {18, "Eighteen"}, 
        {17, "Seventeen"}, {16, "Sixteen"}, {15, "Fifteen"}, {14, "Fourteen"}, 
        {13, "Thirteen"}, {12, "Twelve"}, {11, "Eleven"}, {10, "Ten"}, {9, "Nine"},
        {8, "Eight"}, {7, "Seven"}, {6, "Six"}, {5, "Five"}, {4, "Four"}, {3, "Three"},
        {2, "Two"}, {1, "One"}
     };

    // Base Case 
    if (num == 0) return "zero" ;

    for (auto &pair : numberWordsPairs){

     if (num >= pair.first){
          string a = "";

          if (num >= 100){
               a = numberToWords(num / pair.first) + " ";
          }
          
          string b = pair.second;

          string c = "";
          if (num % pair.first != 0){
               // First add space
               c = " " + numberToWords(num % pair.first);
          }

          return a + b + c;
     }
    }

    return "";
}




int main() {
     int num1 = 123;
     int num2 = 359;
     cout << "Number: " << numberToWords(num1) << endl;
     cout << "Number: " << numberToWords(num2) << endl;

     return 0;
}