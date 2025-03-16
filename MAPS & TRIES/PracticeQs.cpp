#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <unordered_set>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <math.h>
#include <limits.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;

// LEETCODE : 1 (Two Sum)
vector<int> twoSum(vector<int>& nums, int target) {
     // map to store numbers and their indices
     unordered_map<int,int> hashMap;

     for(int i = 0; i < nums.size(); i++) {
          int element = nums[i];
          int required = target - element;
          
          // Check if complement exists in map
          if(hashMap.find(required) != hashMap.end()) {
               return{hashMap[required], i};    // Return indices if complement is found
          }
          
          // Insert the element, otherwise
          hashMap[element] = i;
     }
     return{-1,-1};
}





// LEETCODE : 49 (Group Anagrams)
vector<vector<string>> groupAnagrams(vector<string>& strs) {
     // Map to store grp Anagrams
     unordered_map<string, vector<string>> Anagram;

     for(int i = 0 ; i < strs.size(); i++) {
          string original = strs[i];
          string copy = original;
          sort(original.begin(), original.end());

          Anagram[original].push_back(copy);
     }

     vector<vector<string>> result;
     for(auto ch : Anagram) {
          result.push_back(ch.second);
     }
     
     return result;
}






// IMPORTANT

// LEECODE 30 (Substring with Concatenation of All Words)
vector<int> findSubstring(string s, vector<string>& words) {
     unordered_map<string,int> map;
     vector<int> ans;

     for(int i = 0; i < words.size(); i++){
          map[words[i]]++;
     }

     int wordsLength = words[0].length();

     for(int offset = 0; offset < wordsLength; offset++){
          unordered_map<string, int> visited;
          int count = 0;

          for(int i = offset; i + wordsLength <= s.length(); i += wordsLength) {
               string subStr = s.substr(i, wordsLength);

               if(map.find(subStr) == map.end()) {
                    visited.clear();
                    count = 0;
               }

               else {
                    visited[subStr]++;
                    count++;

                    while(visited[subStr] > map[subStr]) {
                         string temp = s.substr(i - (count - 1) * wordsLength, wordsLength);
                         visited[temp]--;
                         count--;
                    }  

                    if(count == words.size()){
                         ans.push_back(i - (count - 1) * wordsLength);
                    }   
               }
          }       
     }

     return ans;
}







// LEETCODE : 187 (Repeated DNA Sequences)
vector<string> findRepeatedDnaSequences_1(string s) {
     //  result vector and the unordered map for frequency counting
     unordered_map<string, int> subStringCount;
     vector<string> result;

     for (int i = 0; i <= s.length() - 10; i++) {
          string subStringOf10size = s.substr(1,10);
          subStringCount[subStringOf10size]++;
     }

     for(auto ch : subStringCount) {
          if (ch.second > 1) {
               result.push_back(ch.first);
          }
     }



     return result;


}

// Alternative (Without unordered_map)
vector<string> findRepeatedDnaSequences_2(string s) {
     vector<string> result;
     vector<string> subString;

     for(int i = 0; i < s.length(); i++) {
          subString.push_back(s.substr(i,10));
     }
     
     // Sort the substrings
     sort(subString.begin(), subString.end());
     
     // Identify repeated substrings
     for(int i = 1; i < subString.size(); i++){
          if(subString[i] == subString[i-1]) {
               // Avoid adding duplicates to the result
               if (result.empty() || result.back() != subString[i]) {
                    result.push_back(subString[i]);
               }
          }
     }

     return result;
}














int main() {
     string s1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
     vector<string> output1 = findRepeatedDnaSequences_2(s1);

     cout << "Output for \"" << s1 << "\": ";
     for (const auto &sequence : output1) {
          std::cout << sequence << " ";
     }
     cout << endl;

     string s2 = "AAAAAAAAAAAAA";
     vector<string> output2 = findRepeatedDnaSequences_2(s2);

     cout << "Output for \"" << s2 << "\": ";
     for (const auto &sequence : output2) {
          cout << sequence << " ";
     }
     cout << endl;
     
     return 0;
}