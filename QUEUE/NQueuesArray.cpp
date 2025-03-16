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



class KQueue {
public:
     int n, k, freespot;
     int *arr, *front, *rear, *next;

     KQueue(int _n, int _k) : n(_n), k(_k), freespot(0) {
		
		arr = new int[n];
		front = new int[k];
		rear = new int[k];
		next = new int[n];
          
          for (int i = 0; i < k; i++) {
			front[i] = rear[i] = -1;
		}


		for (int i = 0; i < n; i++) {
			next[i] = i + 1;
		}
          next[n - 1] = -1;
	}


     // push x into qith Queue
	bool push(int x, int qi) {
		// Overflow
		if (freespot == -1) {
			return false;
		}
          

		// Find first free index
		int index = freespot;
		// Update freespot
		freespot = next[index];



		// if first element in qi
		if (front[qi] == -1) {
			front[qi] = index;
		} 
		else {
			// Link the new element to Q's rearest element
			next[rear[qi]] = index;
		}



          // update next
		next[index] = -1;

		// update rear
		rear[qi] = index;
		arr[index] = x;

		return true;
	}
    

     int pop (int q1) {

		// underflow
		if (front[q1] ==  -1) {
			return -1;
		}

		// Find index to pop
		int index = front[q1];   

		// Front update
		front[q1] = next[index];
          
		// Update freespots
		next[index] = freespot;
		freespot = index;

		return arr[index];
	}



     ~KQueue() {
		delete[] arr;
		delete[] front;
		delete[] rear;
		delete[] next;
	}
};


int main() {
	KQueue kq(8,3);

	cout << boolalpha << kq.push(1, 0) << endl;
	cout << boolalpha << kq.push(2, 0) << endl;
	cout << boolalpha << kq.push(5, 1) << endl;
	cout << boolalpha << kq.push(3, 0) << endl;
     cout << kq.pop(0) << endl;



	return 0;
}