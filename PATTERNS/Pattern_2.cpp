#include <iostream>
#include <algorithm>

/*

****** 
*    *      ----> [PATTERN]
*    *     
******    
 
*/



using namespace std;



int main() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 6; j++) {
            // Check if current position is inside the hollow area
            if ((i == 1 || i == 4 || j == 1 || j == 6)) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}