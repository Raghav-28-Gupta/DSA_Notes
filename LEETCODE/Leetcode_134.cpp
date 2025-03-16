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


// Gas Station Problem
int canCompleteCircuit_1(vector<int>& gas, vector<int>& cost) {
     int balance = 0;
     int deficit = 0;
     int start = 0;

     for (int i = 0; i < gas.size(); i++)  {
          balance = balance + gas[i] - cost[i];
          
          if (balance < 0) {
               deficit += abs(balance);
               // Since deficit appeard, wont move further
               // Have to update the start
               start = i + 1;
               balance = 0;
          }
     }
     
     if (balance - deficit >= 0) {
          return start;
     }
     else {
          return -1;
     }
}



int canCompleteCircuit_2(vector<int>& gas, vector<int>& cost) {
     int total_tank = 0;
     int curr_tank = 0;
     int start_tank = 0;
     
     for (int i = 0; i < gas.size(); i++) {
          total_tank += gas[i] - cost[i];    // Calculate total remaining gas
          curr_tank  += gas[i] - cost[i];    // Calculate current tank for the current trip
          
          // If current tank is negative, we can't start from the current start_station
          if (curr_tank < 0) {
               // Start from the next station
               start_tank = i + 1;
               // Reset current tank for the new starting point
               curr_tank = 0;
          }
     }


     return total_tank >= 0 ? start_tank : -1;
}



int main() {
     vector<int> gas = {1,2,3,4,5};
     vector<int> cost = {3,4,5,1,2};

     cout << "Starting Postion is: " << canCompleteCircuit_2(gas, cost) << endl;




     return 0;
}
