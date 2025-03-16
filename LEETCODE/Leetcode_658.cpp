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
using namespace std;


vector<int> findClosestElements_1 ( vector<int>& arr, int k, int x ) {           // T.C --> O( logn + klogk )

  int index = lower_bound( arr.begin(), arr.end(), x) - arr.begin() ; 
  // By subtracting arr.begin(), we get the zero-based index of that iterator

  int left = index - 1;
  int right = index;

  vector <int> result;

  while ( k-- ) {

    if ( left < 0 ) {
      result.push_back( arr[right++] );
    } else if ( right >= arr.size() ){
      result.push_back( arr[left--] );
    }

    else {
      if ( abs( x-arr[left] ) <= abs( arr[right]-x ) ) {
        result.push_back(arr[left]);
        left--;                                                  // Moving towards smaller difference
      } else {
        result.push_back(arr[right]);
        right++;
      }
    }
  }

  sort( result.begin(), result.end() );

  return result;

}


vector<int> findClosestElements_2 ( vector<int>& arr, int k, int x ) {           // T.C --> O(n)

  int left = 0;
  int right = arr.size() - 1;

  while ( right - left >= k ) {

    if ( abs( x-arr[left] )  > abs( arr[right]-x ) ) {
      left++;
    }
    else {
      right--;
    }
  }

  vector <int> ans;

  for ( int i=left; i<=right; i++ ) {
    ans.push_back( arr[i] );
  }

  sort(ans.begin(), ans.end());

  return ans;


}




int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 4;
    int x = 3;

    vector<int> result = findClosestElements_2(arr, k, x);

    cout << "Output: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i != result.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    return 0;
}








