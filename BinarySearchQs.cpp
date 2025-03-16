#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
using namespace std;




int FirstOccurence ( vector <int>&vec, int Target ){
    int low = 0;
    int high = vec.size()-1;
    int mid = 0;
    int ans;
    while (low <= high){
        mid = low + (high-low)/2;   // Better hai define krde

        if (vec[mid] == Target){
            ans = mid;
            // Left jaana hai kyunki first occurence nikalni hai 
            high = mid - 1;
        }

        if (vec[mid] > Target){
            // Left jaana hai 
            high = mid - 1;
        }

        
        if (vec[mid] < Target){
            // Left jaana hai 
            low = mid + 1;
        }
    }
    return ans;

}



int LastOccurence( vector <int>&vec, int Target ){
    int low = 0;
    int high = vec.size()-1;
    int mid = 0;
    int ans;
    while (low <= high){
        mid = low + (high-low)/2;   // Better hai define krde

        if (vec[mid] == Target){
            ans = mid;
            // Right jaana hai kyunki last occurence nikalni hai 
            low = mid + 1;
        }

        if (vec[mid] > Target){
            // Left jaana hai 
            high = mid - 1;
        }

        
        if (vec[mid] < Target){
            // Left jaana hai 
            low = mid + 1;
        }
    }

    return ans;

}




int MissingElementFromDuplArrayOToN ( vector <int> &vec, int Range ) {      // T.C -> O(n)
    std::map<int,int> table;
    for ( int i=0; i<Range; i++ ){
        table[vec[i]]++;
    }

    for ( int i=1; i<=Range; i++ ){
        if ( table.find(i) == table.end() || table[i]==0 ){
            return i;
        }
    }

    return -1;

}




int findPeakElement ( vector <int> &vec ) {             // T.C -> O(logn)
    int size = vec.size();

    if ( size == 1 ) return vec[0];                  // Assume -infinity at both ends of the array
    if ( vec[0] > vec[1] ) return vec[0];            // To control out of range situations

    int low = 1;
    int high = size-2;
    
    while ( low <= high ) {
        int mid = low + (high-low)/2;
        
        if ( ( vec[mid] > vec[mid+1] ) && ( vec[mid] > vec[mid-1] )) {
            return mid;         // Returning Index value
        }

        else if ( vec[mid] > vec[mid-1] ) {
            low = mid+1;
        }

        else if ( vec[mid] > vec[mid+1] ) {
            high = mid-1;
        }

        else {
            high = mid-1;             // For the situation in which both the elements are bigger than the mid element
        }                             // In this we have to ignore the right curves OR left curves
    }

    return -1;


}




int PivotIndex ( vector <int> &vec ) {                  // Using Binary Search 
    int size = vec.size();

    if ( size == 1 ) return -1; 

    if ( vec[0] > vec[1] ) return vec[0];

    int low = 1;
    int high = size-2;
    
    while ( low <= high ) {
        int mid = low + (high-low)/2;
        
        if (( vec[mid] > vec[mid+1] ) && ( vec[mid] > vec[mid-1] )) {
            return mid;         // Returning Index value
        }

        else if ( vec[mid] < vec[mid-1] ) {
            high = mid-1;
        }

        else if ( vec[mid] < vec[mid+1] ) {
            low = mid+1;
        }

    }

    return -1;

}
 



int mySqrt ( int n ) {                                  // Very fast approach using B.S
                                     
    if ( n == 0 ) return 0;
    if ( n == 1 ) return 1;

    int low = 0;
    int high = n;
    int ans = -1;

    while (low <= high) {
        long long int Mid = low + ( high - low )/2 ;      // To handle the cases 
        long long int MidSquare = Mid * Mid;              // of large product

        if ( MidSquare == n ) return Mid;

        if ( MidSquare < n ) {
            // First store and compute 
            ans = Mid;
            // Going right to the nearest answer
            low = Mid+1;
        } 
        
        else {
            // Going Left 
            high = Mid-1;
        }
    }
}




double PrecisionSqrt ( int n ) {                        // T.C -->  O(log (precision) * log(n) )

    double sqrt = mySqrt(n);
    int precision = 8;               // cout print till 5 precisions only
    double step = 0.1;               // So use -->    printf ( "Precision Sqrt: %.8f \n ", ans );

    while (precision--) {
        double prev = sqrt;

         while ( prev * prev <= n ){
            // Store and Compute
            sqrt = prev ;
            prev = prev + step;
        }

        step/=10;

    }

    return sqrt;
}




double BSPrecision ( int n ) {                          // Using Binary Search
    double ans = 0;
    double low = 0;
    double high = n;

    while ( (high - low ) >= 0.00001 ){                 //  --> When precision to be considered
        double mid = ( low + high ) /2 ;

        double sqrt = mid * mid;

        if ( sqrt <= n ){
            ans = mid;
            low = mid;
        }
        else{

            high = mid;
        }
    }

    return ans;

}




bool BinarySearchIn2dMatrix ( vector < vector<int> >& vec, int target ) {

    int row = vec.size();
    int col = vec[0].size();
    int n = row * col;

    int low = 0;
    int high = n-1;
 
    while ( low <= high ) {
        int mid = low + ( high-low )/2;
        // Finding RowIndex and Columnindex           //            2D -> 1D    ---->  [ column*i + j ]
        int ri = mid / col;                           //            iD -> 2D    ---->  i = mid/column       j = mid % column
        int ci = mid % col;                     

        if ( vec[ri][ci] == target ) return true;
        if ( vec[ri][ci] > target ) high = mid-1;
        else low = mid + 1;
        
    }
    return false;
}

bool searchMatrix_2(vector<vector<int>>& matrix, int target) {        // LEETCODE : 240

    if (matrix.size() == 0 || matrix[0].size() == 0) return false;

    int rows = matrix.size();
    int cols = matrix[0].size();

    // IMPORTANT STEP
    // Start from the TOP-RIGHT corner
    int row = 0;
    int col = cols - 1;

    while (row < rows && col >= 0) {

        if (matrix[row][col] == target){
            return true;
        }

        else if (matrix[row][col] > target){
            // Move left
            col--;
        }

        else {
            // Move down
            row++;
        }
    }

    // Target not found
    return false;
}




int GetQuotient ( int dividend, int divisor ) {        // without using / OR %
         
    if ( divisor == 0 ) return -1;                     // NOTE : Argument positive hee jaayenge
    int low = 0;                                       // Main function mein -ve krna hai ( if necessary )
    int high = dividend;
    int ans = -1;

    while ( low <= high ) {
        int mid = low + ( high-low )/2;
        long long int product = mid * divisor;

        if ( product == dividend ) {
            return mid;
        }

        if ( product < dividend ) {
            ans = mid;
            low = mid + 1;
        }

        else {
            high = mid - 1;
        }
    }
}








int main () {
    
    vector<vector<int>> Matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    int target = 10;
    
    cout << "Ans is: " << boolalpha << searchMatrix_2(Matrix, target);

    return 0;
}