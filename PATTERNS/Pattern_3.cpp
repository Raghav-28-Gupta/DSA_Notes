#include <iostream>
#include <algorithm>

/* 

1 
2 3 
4 5 6                   ------> [ PATTERN ]
7 8 9 10 
11 12 13 14 15

*/



using namespace std;



int main() {
    int n;
    cout<<"Enter the number of rows: ";
    cin>>n;
    int a=1;
    for (int i = 1; i <= n; i++) {
        for (int j=1; j<=i; j++){
            cout<<a++<<" ";
        }
        cout<<endl;
    }
  
    return 0;
}