#include <iostream>
using namespace std;

/*
        1
      1 2 1 
    1 2 3 2 1 
  1 2 3 4 3 2 1 
1 2 3 4 5 4 3 2 1

*/



int main() {
    int rows;

    cout << "Enter the number of rows: ";
    cin >> rows;

    for (int i = 1; i <= rows; i++) {
        // Print spaces before the numbers
        for (int space = 1; space <= rows - i; space++) {
            cout << "  ";
        }

        // Print numbers in ascending order
        for (int num = 1; num <= i; num++) {
            cout << num << " ";
        }

        // Print numbers in descending order
        for (int num = i - 1; num >= 1; num--) {
            cout << num << " ";
        }

        cout << endl;
    }

    return 0;
}
