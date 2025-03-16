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

class TrieNode {
public:
     char data;
     unordered_map<char, TrieNode*> children;
     bool isTerminal;

     TrieNode(char ch) : data(ch), isTerminal(false) {}
};

class Trie {
     TrieNode* root;

     void insertUtil(TrieNode* root, string &s, int i = 0) {
          // Base Case
          if (s.length() == 0) {
               root->isTerminal = true;
               return;
          }

          char ch = s[i];
          TrieNode* child;

          if (root->children.find(ch) != root->children.end()) {
               // Present
               child = root->children[ch];
          } else {
               // Absent
               child = new TrieNode(ch);
               root->children[ch] = child;
          }

          insertUtil(child, s, i + 1);
     }

     bool searchUtil(TrieNode* root, string &s, int i = 0) {
          // Base Case
          if (s.length() == 0) {
               return root->isTerminal;
          }

          char ch = s[i];
          bool matched = false;

          if (ch == '.') {
               // '.' can be matched to any child of current root Trie node
               for (auto &child : root->children) {
                    matched = matched || searchUtil(root->children[ch.first], s, i + 1);
               }
          } else {
               if (root->children.find(ch) != root->children.end()) {
                    matched = searchUtil(root->children[ch], s, i + 1);
               }
          }

          return matched;
     }

public:
     Trie() {
          root = new TrieNode('\0');
     }

     void add(string word) {
          insertUtil(root, word);
     }

     bool search(string word) {
          return searchUtil(root, word);
     }
};

class WordDictionary {
     Trie trie;
public:
     WordDictionary() {}

     void addWord(string word) {
          trie.add(word);
     }

     bool search(string word) {
          return trie.search(word);
     }
};

int main() {
     WordDictionary wordDictionary;
     wordDictionary.addWord("bad");
     wordDictionary.addWord("dad");
     wordDictionary.addWord("mad");

     cout << boolalpha; // Print true/false instead of 1/0
     cout << wordDictionary.search("pad") << endl; // false
     cout << wordDictionary.search("bad") << endl; // true
     cout << wordDictionary.search(".ad") << endl; // true
     cout << wordDictionary.search("b..") << endl; // true

     return 0;
}
