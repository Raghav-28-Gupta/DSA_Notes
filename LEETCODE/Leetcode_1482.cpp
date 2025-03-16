#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
using namespace std;


bool CanMakeBouquet ( vector <int> &bloomDay, int mid, int m, int k ) {
     int flowers = 0;
     int bouquets = 0;

     for ( int bloom: bloomDay ){
          if ( bloom <= mid){                        // Check if the flower can bloom by the given day
               flowers++;
               if ( flowers == k ){                  // If we have enough flowers to form a bouquet
                    bouquets++;                    
                    flowers = 0;                     // Reset the consecutive flowers count
                    if ( bouquets >= m ){            // Early exit if we have formed enough bouquets
                         return true;
                    }
               }
          } else {
               flowers = 0;
          }

     }
     return false;

}



int minDays( vector <int> &bloomDay, int m, int k ) {
    int n = bloomDay.size();
    if ( n < m*k ) return -1;

    int left = *min_element( bloomDay.begin(),bloomDay.end() );
    int right = *max_element ( bloomDay.begin(),bloomDay.end() );

    while ( left < right ){
      int mid = left + ( right - left )/2;

      if ( CanMakeBouquet (bloomDay, mid, m, k ) ){
        right = mid;     // Need less Days
      }
      else{
        left = mid + 1;  // Need more Days
      }
    }

    return left;

}


int main() {
    vector<int> bloomDay1 = {1, 10, 3, 10, 2};
    int m1 = 3;
    int k1 = 1;
    cout << minDays(bloomDay1, m1, k1) << endl;  // Output: 3

    vector<int> bloomDay2 = {1, 10, 3, 10, 2};
    int m2 = 3;
    int k2 = 2;
    cout << minDays(bloomDay2, m2, k2) << endl;  // Output: -1

    vector<int> bloomDay3 = {7, 7, 7, 7, 12, 7, 7};
    int m3 = 2;
    int k3 = 3;
    cout << minDays(bloomDay3, m3, k3) << endl;  // Output: 12

    vector<int> bloomDay4 = {1000000000, 1000000000};
    int m4 = 1;
    int k4 = 1;
    cout << minDays(bloomDay4, m4, k4) << endl;  // Output: 1000000000

    vector<int> bloomDay5 = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
    int m5 = 4;
    int k5 = 2;
    cout << minDays(bloomDay5, m5, k5) << endl;  // Output: 9

    return 0;
}


    