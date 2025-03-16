#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <math.h>
#include <limits.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;

struct Position {
    int x, y;
};



bool isValid(int x, int y, int N, vector<vector<bool>>& visited) {
     if (x >= 0 && y >= 0 && x < N && y < N && !visited[x][y]) {
          return true;
     }

     return false;

}


int findMinSteps(Position knightPos, Position targetPos, int N, vector<vector<bool>>& visited, int steps) {
     // Base case: Knight reached the target position
     if (knightPos.x == targetPos.x && knightPos.y == targetPos.y) {
          return steps;
     }

     visited[knightPos.x][knightPos.y] = true;

     int minSteps = INT_MAX;
     
     // Explore all 8 possible moves using arithmetic calculations (without a move vector)
     for (int dx = -2; dx <= 2; dx++) {
          for (int dy = -2; dy <= 2; dy++) {
               if (dx != 0 && dy != 0 && abs(dx) != abs(dy)) {
                    int newX = knightPos.x + dx;
                    int newY = knightPos.y + dy;

                    if (isValid(newX, newY, N, visited)) {
                         minSteps = min(minSteps, findMinSteps({newX, newY}, targetPos, N, visited, steps + 1));
                    }
               }
          }
     }

     visited[knightPos.x][knightPos.y] = false;    // Backtrack

     return minSteps;
}


int minStepsToTarget(Position knightPos, Position targetPos, int N) {
    // Create a visited matrix to track visited positions
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    
    // Call the recursive function
    return findMinSteps(knightPos, targetPos, N, visited, 0);
}



int main() {
     int N = 8;  // Example for an 8x8 chessboard
     Position knightPos = {1, 3};  // Knight's position
     Position targetPos = {5, 0};  // Target position
    
     // Find the minimum steps to reach the target
     int steps = minStepsToTarget(knightPos, targetPos, N);
    
     // Output the result
     if (steps != INT_MAX) {
        cout << "Minimum steps: " << steps << endl;
     } else {
        cout << "Target cannot be reached." << endl;
     }

     return 0;
}