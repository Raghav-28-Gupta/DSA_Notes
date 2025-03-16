#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
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


// LEETCODE : 649
string predictPartyVictory(string senate) {
     queue<int> radientQ;
     queue<int> direQ;
     
     int position = 0;
     for(; position < senate.length(); position++) {
          if (senate[position] == 'R') radientQ.push(position);
          else direQ.push(position);
     }

     while(!radientQ.empty() && !direQ.empty()) {
          int rFront = radientQ.front();
          radientQ.pop();
          int dFront = direQ.front();
          direQ.pop();
          
          // The senator with the smaller index bans the other one
          if (rFront < dFront) {
               // Radiant bans Dire, Radiant gets to rejoin in the next round
               radientQ.push(position++);
          }

          else {
               // Dire bans Radiant, Dire gets to rejoin in the next round
               direQ.push(position++);
          }
     }
     
     return radientQ.empty() ? "Dire" : "Radiant";
}


int main() {
     string senate = {"RRDDD"};
     
     cout << "Output: " << predictPartyVictory(senate) << endl; 

     return 0;
}