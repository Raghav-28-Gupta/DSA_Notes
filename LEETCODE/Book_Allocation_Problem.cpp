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

bool IsPossibleSoln ( int A[], int N, int M , int sol ){

     int PageSum = 0;
     int count = 1;                          // Atleast 1 child
     
     for ( int i=0; i<N; i++ ){

          if ( A[i] > sol ) return false;

          if ( PageSum + A[i] > sol ){
               count++;                    // First Count that student
               PageSum = A[i];             // Then assigning the next bunch of pages to the other student
               if ( count > M ) {
                    return false;
               }
          }
          else {
               PageSum += A[i];           // Keep counting until the TotalPagesSum 
          }                               // Become just greater than the sol
     }

     return true;
}


int FindMinPages ( int A[], int N, int M ) {
     
     if ( M > N ) return -1;

     int low = 0;
     int high = accumulate( A, A+N, 0 );
     int ans = -1;

     while ( low <= high ) {
          int mid = low + ( high - low )/2;

          if ( IsPossibleSoln( A, N, M, mid ) ) {
               // I have got that MAXIMUM number of pages assigned to a student that is to be minimized
               ans = mid;
               // Getting closer to the answer       
               high = mid - 1;          
          } else {
               // Students are more than required so MORE pages to be alloted
               low = mid + 1;  
          }
     }

     return ans;

}






int main() {
     int A[] = { 12, 34, 67, 90 };
     int N = sizeof(A) / sizeof(A[0]);
     int M = 2;
     
     cout << "Minimum Pages are: " << FindMinPages ( A, N, M ) << endl;

   
}