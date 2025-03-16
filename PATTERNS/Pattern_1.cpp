#include <iostream>
#include <algorithm>
using namespace std;

/*  1
    AB
    123          ------> [ PATTERN ]
    ABCD
    12345
*/



int main() {
    int n;
    cin>> n;

    for( int i=1; i<=n; i++) {

        for(int j = 1; j<i; j++){
            if( i%2 == 0 ){
                cout<<j;
            }
            else{
                cout<< char(j + 64);
            }
        }
        /*
        if ( i%2!=0) {
            for ( int j=1; j<=i; j++){
                cout<<j;
            }
        }else {
            for ( char k=65; k<=64+i; k++) {
                cout<<k;
            }
        }
        */
        cout<<endl;
    }
    
    return 0;
}
