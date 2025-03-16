#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
#include <unordered_map>
#include <utility>
using namespace std;



int findPairs_1(vector<int>& nums, int k) {           // Method 1
 
  if ( k<0 ){
    return -1;
  }
  
  unordered_map <int,int> numcount;
  for ( auto num:nums ){
    numcount[num]++;
  }

  int count = 0;

  for ( auto &Pair: numcount ) {
    int num = Pair.first;

    if ( k==0 ){
      
      if ( Pair.second > 0 ){
        count++;
      }

    } else{
      // For k > 0, check if the counterpart (num + k) exists
      if ( numcount.find(num + k )!= numcount.end() ){
        count++;
      }
    }
  }
  return count;
}


int findPairs_2(vector<int>& nums, int k) {           // Method 2

     if ( k<0 ) return -1;

     sort( nums.begin(), nums.end() );               // first sorting is done

     set <pair <int,int>> Pair;
     int i=0, j=1;

     while ( j<nums.size() ){                       // Two Pointer Method ( After sorting )

          int diff = nums[j] - nums[i];

          if ( diff == k ){
               Pair.insert( {nums[i],nums[j]} );
               i++;
               j++;
          }
          else if ( diff < k ){
               j++;
          }
          else {
               i++;
          }
          if ( i == j ){
               j++;
          }
          
     }

     return Pair.size();

}




int main() {
    vector<int> nums1 = {3, 1, 4, 1, 5};
    int k1 = 2;
    cout << findPairs_2(nums1, k1) << endl; // Output: 2

    vector<int> nums2 = {1, 2, 3, 4, 5};
    int k2 = 1;
    cout << findPairs_2(nums2, k2) << endl; // Output: 4

    return 0;
}