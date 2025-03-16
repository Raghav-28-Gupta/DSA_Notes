#include <iostream>
#include <algorithm>
using namespace std;

/* 

        * * * * * 
      * * * * * 
    * * * * *          -----> [ RHOMBUS ]
  * * * * * 
* * * * *

*/




int main() {
    int n;
    cout << "Enter the number of rows: ";
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        // Print spaces
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        
        // Print asterisks
        for (int k = 1; k <= n; k++) {
            cout << "* ";
        }
        
        cout << endl;
    }
    
    return 0;
}
