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

// ISOMORPHIC STRING

string Normalise ( const string &str ) {

     unordered_map <char,char> charMap;
     char start = 'a';
     string Normalised = "";
     
     for ( auto i=0; i<str.size(); i++ ) {
          char strCharacter = str[i];

          if ( charMap.find(strCharacter) == charMap.end() ){
               charMap[strCharacter] = start;
               start++;
          }

          Normalised += charMap[strCharacter];
     }

     return Normalised;

}
  


vector <string> findAndReplacePattern ( vector <string> &words, const string &pattern ) {
     vector <string> result;

     string NormalisedPattern = Normalise ( pattern );

     for ( auto i=0; i<words.size(); i++ ) {
          string word = words[i];
          string NormalisedWord = Normalise(word);
          if ( NormalisedWord == NormalisedPattern ) {
               result.push_back(word);
          }
     }
     return result;
}


int main() {
    vector <string> words = {"abc", "deq", "mee", "aqq", "dkd", "ccc"};
    string pattern = "abb";

    vector <string> matchedWords = findAndReplacePattern(words, pattern);

    for (const string& word : matchedWords) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}