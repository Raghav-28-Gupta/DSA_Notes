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



string reorganizeString (string s) { 

     unordered_map <char,int> CharCount;

     for ( auto c: s ) {
          CharCount[c]++;
     }

     int Max_Freq_Char ;
     int Max_Freq = INT_MIN;


     for ( auto c : CharCount ) {
          // Find the most frequent one
          if ( c.second > Max_Freq ) {
               Max_Freq = c.second;
               Max_Freq_Char = c.first;
          }
     }

     int Index = 0;
     // Place the most frequent character
     while ( Max_Freq > 0 && Index < s.size() ) {
          s[Index] = Max_Freq_Char;
          Index += 2;                        //       a _ a _ a    ---> Like this
          Max_Freq--;
     }


     if ( Max_Freq != 0 ) return "";

     // Place the rest of the characters

     CharCount[Max_Freq_Char] = 0;      //    ----> First make it zero as it is placed

     for ( int i=0; i<CharCount.size(); i++ ) {

          while ( CharCount[i] > 0 ) {
               Index = Index > s.size() ? 1 : Index;          //   ---> To check if Index didn't exceed the size
               s[Index] = i;
               Index += 2;
               CharCount[i]--;
          }
     }

     return s;
}



int main () {

     string s = "aaabbbcc";

     cout << reorganizeString (s) << endl;
}