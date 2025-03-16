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


class TrieNode{
public:
     char value;
     unordered_map<char, TrieNode*> children;
     bool isTerminal;

     TrieNode(char data) {
          this->value = data;
          isTerminal = false;
     }
};


void insertIntoTrie(TrieNode* root, string word) {
     // Base Case
     if(word.length() == 0) {
          root->isTerminal = true;
          return;
     }
     

     char ch = word[0];
     TrieNode* child;
     
     // Check, if present
     if(root->children.count(ch) == 1) {
          child = root->children[ch];
     }
     // if absent
     else {
          // Create a new node
          child = new TrieNode(ch);
          // Connect to its root
          root->children[ch] = child;
     }
     
     // pass the string from next index
     insertIntoTrie(child, word.substr(1));
}


bool searchTrie(TrieNode* root, string word){
     // Base Case
     if(word.length() == 0) {
          return root->isTerminal;
     }

     char ch = word[0];
     TrieNode* child;
     
     // Checking
     if(root->children.find(ch) != root->children.end()) {
          // Present
          child = root->children[ch];
     }
     else {
          return false;
     }
     
     // Recursion
     return searchTrie(child, word.substr(1));
}


void deleteWord(TrieNode* root, string word) {
     // Main case
     // Just set the terminal of the given word FALSE
     if(word.length() == 0) {
          root->isTerminal = false;
          return;
     }

     char ch = word[0];
     TrieNode* child;

     // Checking
     if(root->children.find(ch) != root->children.end()){
          // Present
          child = root->children[ch];
     }

     else {
          // Not present
          return;
     }

     return deleteWord(child, word.substr(1));
}






// LEETCODE : 14
void lcpHelper(TrieNode* root, string &ans) {
     // Base Case
     if(root->isTerminal == true) {
          return;
     }

     TrieNode* child;
     if(root->children.size() == 1) {
          // only ONE child present
          for(auto i : root->children){
               char ch = i.first;
               ans.push_back(ch);
               child = i.second;
          }
     }
     else{
          // Multiple children found
          return;
     }
     
     // Recursion
     lcpHelper(child, ans);
}

string longestCommonPrefix(vector<string>& strs) {
     if(strs.empty()) return "";

     TrieNode* root;

     for(auto ch : strs) {
          insertIntoTrie(root, ch);
     }

     string ans = "";
     lcpHelper(root, ans);
     return ans;
}





// Find similar words with prefix
void storeString(TrieNode* root, string output, vector<string> &ans) {
     // Base case
     if(root->isTerminal == true) {
          ans.push_back(output);
     }

     for(auto i : root->children) {
          char ch = i.first;
          TrieNode* child = i.second;
          output.push_back(ch);
          // call Recursion
          storeString(child, output, ans);
          // Backtracking
          ans.pop_back();
     }
}



void findWordsWithPrefix(TrieNode* root, string prefix, vector<string> &ans){
     // Traverse the Trie to reach the end node of the given prefix
     for (char ch : prefix) {
          // If the character is not found in the Trie, return early
          if(root->children.find(ch) == root->children.end()) {
               return;
          }
          root = root->children[ch]; // Move root to the child corresponding to the character
     }

     // We have reached the end node of the prefix, collect all words from here
     storeString(root, prefix, ans);
}


vector<vector<string>> getSuggestions(TrieNode* root, string prefix) {
     vector<vector<string>> ans;
     vector<string> tempAns;
     string temp = "";

     for(int i = 0; i < prefix.length(); i++) {
          char currChar = prefix[i];
          temp.push_back(currChar);
          findWordsWithPrefix(root, temp, tempAns);
          for(int j = 0; j < tempAns.size(); j++) {
               tempAns[j] = temp + tempAns[j]; 
          }
          ans.push_back(tempAns);
     }

     return ans;
}



int main() {
     TrieNode* root = new TrieNode('-');
     
     insertIntoTrie(root, "cover");
     insertIntoTrie(root, "car");
     insertIntoTrie(root, "coat");
     insertIntoTrie(root, "cake");
     insertIntoTrie(root, "cook");

     insertIntoTrie(root, "snake");
     insertIntoTrie(root, "snack");
     insertIntoTrie(root, "spain");
     insertIntoTrie(root, "steel");
     insertIntoTrie(root, "still");
     insertIntoTrie(root, "shake");
     insertIntoTrie(root, "stake");

     insertIntoTrie(root, "tree");
     insertIntoTrie(root, "tall");
     insertIntoTrie(root, "tea");
     insertIntoTrie(root, "tag");
     insertIntoTrie(root, "tap");
     insertIntoTrie(root, "talent");
     insertIntoTrie(root, "top");
     insertIntoTrie(root, "tail");
     insertIntoTrie(root, "trunk");

     // cout << boolalpha << searchTrie(root, "spain") << endl;
     // deleteWord(root, "spain");
     // cout << boolalpha << searchTrie(root, "spain") << endl;

     vector<string> ans;
     string prefix = "take";
     findWordsWithPrefix(root, prefix, ans);

     for(auto ch : ans) {
          string str = prefix + ch;
          ch = str;
          cout << ch << " " << endl;
     }

     return 0;
} 