#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
using namespace std;




int CanFinish( vector <int> &piles, int mid, int h ) {
  int hours = 0;

  for (int i = 0; i < piles.size(); i++) {
    hours += ceil((double)piles[i] / mid);        // Calculating time taken to finish 1 pile ( having some bananas )
  }                                               // by iterating to every pile and dividing by the  
  return hours;                                   // average speed -> mid ( i.e No. of bananas eaten in "hour" time )
} 





int minEatingSpeed ( vector <int> &piles, int h ) {          // Constraint : piles <= h
  int left = 1;
  int right = *max( piles.begin(), piles.end() );

  while ( left < right ) {
    int mid = left + ( right - left )/2 ;

    if ( CanFinish( piles, mid, h ) <=h ){
      right = mid;     // lower the speed
    }
    else {
      left = mid + 1;  // Increase Speed
    }
  }

  return left;         // Minimum Speed

}


int main() {

  vector<int> piles1 = {3, 6, 7, 11};
    int h1 = 8;
    cout << minEatingSpeed(piles1, h1) << endl;  // Output: 4

    vector<int> piles2 = {30, 11, 23, 4, 20};
    int h2 = 5;
    cout << minEatingSpeed(piles2, h2) << endl;  // Output: 30

    vector<int> piles3 = {30, 11, 23, 4, 20};
    int h3 = 6;
    cout << minEatingSpeed(piles3, h3) << endl;  // Output: 23

  return 0;
}