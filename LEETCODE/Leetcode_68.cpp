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


//  TEXT JUSTIFICATION
// IMPORTAN ***********************************************************************************************************

vector<string> fullJustify(vector<string>& words, int maxWidth) {

     vector<string> ans;
     vector<string> currentLine;
     int CurrentLineTotalChars = 0;

     for(int i = 0; i < words.size(); i++){
          string &currentWord = words[i];
          int SpacesNeeded = currentLine.size();
          
          if (SpacesNeeded + CurrentLineTotalChars + currentWord.size() > maxWidth) {
          // Exceeding!!! i.e CurrentLine is completed without CurrentWord
          int extraSpaces = maxWidth - CurrentLineTotalChars;
          int spacesInBetween = extraSpaces / max(1, (int)currentLine.size()-1);
          int remainder = extraSpaces % ((int)currentLine.size() - 1);
          
          // We don't want spaces after the last word
          for (int j = 0; j < currentLine.size() - 1; j++){
               // Adding even spaces
               for (int k = 0; k < spacesInBetween; k++){
                    currentLine[j] += " ";            
               }

               if (remainder > 0){
                    currentLine[j] += " ";
                    remainder--;
               }
          }
          // Left Justified case coz only 1 word is present in the line
          if (currentLine.size() == 1) {
               while(extraSpaces--){
                    currentLine[0] += " ";
               }
          }

          //  Preparing final Line
          string finalLine = "";
          for (auto wordWithSpaces : currentLine){
               finalLine += wordWithSpaces;
          }

          ans.push_back(finalLine);
          currentLine.clear();
          CurrentLineTotalChars = 0;
  
          }



          // Current line is not completed
          currentLine.push_back(currentWord);
          CurrentLineTotalChars += currentWord.size();
     }
     
     // Handling Last line
     string finalLine = "";
     for (auto wordWithSpaces : currentLine){
          finalLine += wordWithSpaces + " ";
     }

     finalLine.pop_back();   // Remove extra added space
     
     int leftSpaces = maxWidth - finalLine.size();

     while (leftSpaces--){
          finalLine += " ";
     }
     
     ans.push_back(finalLine);
     return ans;
}





int main() {
    vector<string> words1 = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth1 = 16;
    vector<string> result1 = fullJustify(words1, maxWidth1);
    
    for (auto str : result1) {
     cout << str << endl;
    }

    return 0;
}