#include <iostream>
using namespace std;

/* 
    *
   * *
  *   *
 *     *
*********

*/

int main() {
    int rows;
    cout << "Enter the number of rows for the pyramid: ";
    cin >> rows;

    // Outer loop for the number of rows
    for (int i = 0; i < rows; i++) {
        // Inner loop for spaces
        for (int j = 0; j < rows - i - 1; j++) {
            
            cout << " ";
        }
        // Inner loop for stars
        for (int k = 0; k < 2 * i + 1; k++) {
            if( i == rows - 1 || k == 2*i || k == 0|| i == 0){
                cout << "*";
            }
            else{
                cout<<" ";
            }
            
        }
        cout << endl;
    }

    return 0;
}
