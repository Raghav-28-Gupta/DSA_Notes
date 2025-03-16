#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
using namespace std;



void Shifting( int arr[], int n, int shift ){

    int Finalshift = shift % n ;

    int tempArr[1000];
    int index = 0;

    for ( int i = n - Finalshift ; i < n ; i++ ) {
        tempArr[index] = arr[i];
        index++;
    }   

    for ( int j = n-1 ; j >=0 ; j-- ) {
        arr[j] = arr[j-Finalshift] ;
    }

    for ( int i = 0 ; i < Finalshift ; i++ ) {
        arr[i] = tempArr[i];
    }

}

void PivotIndex ( int arr[], int n) {
    vector<int> Lsum(n, 0);
    vector<int> Rsum(n, 0);

    for ( int i=1; i<n; i++ ){
        Lsum[i] = Lsum[i-1] + arr[i-1];
    }

    for ( int j=n-2; j>=0; j-- ){
        Rsum[j] = Rsum[j+1] + arr[j+1];
    }

    for ( int k=0; k<n; k++ ){
        if ( Lsum[k] == Rsum[k] ){
            cout<<" Number at Pivoted index is: " << arr[k];
        }
    }

}

int RemoveDuplicate( vector <int>&vec ) {
    int i = 1, j = 0;
    int size = vec.size();

    while( i<size ){
        if ( vec[i] == vec[j] ) ++i;
        else vec[++j] = vec[i++];    
    }
    return j+1;

}

double MaxAverageSubarray ( vector <int> &vec, int n) {
    int size = vec.size();
    int i=0, j=n-1;

    int Max = INT_MIN;

    while ( j<size ) {
        int sum = 0;
        for ( int a=i; a<=j; a++ ) {
            sum += vec[a];
        }
        Max = max( Max,sum);
        i++; j++;
    }
    double MaxAverage = Max / (double) n;    // Wrna integer answer aayega
    return MaxAverage;
}

double Slidingwindow ( vector <int> &vec, int n ){
    int size = vec.size();
    int i=0, j=n-1;
    int sum = 0;

    for ( i=0; i<=j; i++ ) {
        sum += vec[i];
    }
    j++;

    int MaxSum = sum;
    
    while ( j<size ) {
        sum = sum - vec[i++] + vec[j++];
        MaxSum = max( MaxSum, sum );
    }  

    int MaxAverageSubarray = MaxSum / (double)n;

    return MaxAverageSubarray;

}

void NiggativeLeftSide( vector <int> &vec ) {
    int size = vec.size();
    int i=0, j=1;

    while ( j<size ){
        if ( vec[i] > 0 && vec[j] < 0 ) {
            swap( vec[i], vec[j] );
            i++; 
        }
        j++;
        
    }

    for ( int k=0; k<size; k++ ){
        cout << vec[k] << " ";
    }

}

vector <int> CommonElementsIn3Array ( int a[], int b[], int c[], int n1, int n2, int n3 ) {
    vector <int> ans;
    set <int> st;
    int i=0, j=0, k=0;
    while ( i<n1 && j<n2 && k<n3 ) {
        if ( a[i] == b[j] && b[j] == c[k] ) {
            st.insert( a[i] );
            i++; j++; k++;
        }
        else if ( a[i] < b[j] ) {
            i++;
        }
        else if ( b[j] < c[k] ) {
            j++;
        }
        else{
            k++;
        }

    }

    for ( auto i:st ) {
        ans.push_back(i);
    }

    return ans;


}

vector <int> SpiralOrder ( vector< vector <int> > &vec ) {
    vector <int> ans;
    int rows = vec.size();
    int columns = vec[0].size();
    int TotalElements = rows * columns;

    int StartingRow = 0;
    int EndingColumn = columns-1 ;
    int EndingRow = rows-1 ;
    int StartingColumn = 0;

    int count = 0;
    while ( count < TotalElements ) {
        for ( int i=StartingColumn; i<=EndingColumn && count < TotalElements; i++ ){
            ans.push_back( vec[StartingRow][i] );
            count++;
        }
        StartingRow++;
        for ( int i=StartingRow; i<=EndingRow && count < TotalElements; i++ ){
            ans.push_back( vec[i][EndingColumn] );
            count++;
        }
        EndingColumn--;
        for ( int i=EndingColumn; i>=StartingColumn && count < TotalElements; i-- ){
            ans.push_back( vec[EndingRow][i] );
            count++;
        }
        EndingRow--;
        for ( int i=EndingRow; i>=StartingRow && count < TotalElements; i-- ){
            ans.push_back( vec[i][StartingColumn] );
            count++;
        }
        StartingColumn++;

    }
    return ans;

}

int KedaneAlgo ( vector <int>&vec ) {           // IMPORTANT ALGORITHM
    int ans = INT_MIN;
    int sum = 0;

    for ( int i = 0; i < vec.size(); i++ ) {
        sum += vec[i];
        ans = max ( sum, ans);
        if (sum < 0) sum=0;
    }

    return ans;
}





int main() {
    vector < vector <int> > vec = { {1,2,3}, {4,5,6}, {7,8,9} };

    vector <int> SpiralMatrix = SpiralOrder( vec );
    
     
    return 0;
}
