#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <unordered_set>
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


class Heap{
public:
     int *arr;
     int capacity;
     int index;

     Heap(int n) {
          this->capacity = n;
          this->arr = new int[n];
          this->index = 0;
     }
     
     // PRINT
     void printHeap() {
          for(int i = 0; i < capacity; i++) {
               cout << arr[i] << " ";
          }
          cout << endl;
     }
     

     // INSERT
     void insert(int val) {
          if(index == capacity - 1) {
               cout << "Heap is full" << endl;
               return;
          }

          index++;
          arr[index] = val;

          int i = index;
          
          // Comparing Parent
          while(i > 1) {
               int currIndex = i;
               int parentIndex = i/2;

               if(arr[parentIndex] < arr[currIndex]) {
                    swap(arr[currIndex], arr[parentIndex]);
                    i = parentIndex;    // Move UP the heap
               }

               else {
                    // Parent is already bigger
                    // No need to swap
                    break;
               }
          }
     }
     

     // Delete from  Heap
     void deleteFromHeap() {
          if(index == 0) {
               cout << " Heap is Empty!" << endl;
          }
          
          // Replace root with the last element
          arr[1] = arr[index];
          // And decrease the size
          index--;

          // Heapify DOWN from the root
          heapify(arr, index, 1);
     }
     

     // Heapify function 
     void heapify(int *arr, int n, int currIndex){
          int largest = currIndex;    // Assume for Now
          int leftChild = 2 * currIndex;
          int rightChild = 2 * currIndex + 1;
          
          // Check if left child exists and is greater than current largest
          if(leftChild < n && arr[largest] < arr[leftChild]) {
               largest = leftChild;
          }
          
          // Check if right child exists and is greater than current largest
          if(rightChild < n && arr[largest] < arr[rightChild]) {
               largest = rightChild;
          }
          
          // If largest is not the current index, swap and continue heapifying
          if(largest != currIndex) {
               swap(arr[largest], arr[currIndex]);
               heapify(arr, n, largest);
          }
     }
     

     // Building Heap from Array
     void buildHeap(int *inputArray, int n) {
          // Copy input array to heap array
          for(int i = 0; i < n; i++) {
               arr[i+1] = inputArray[i];
          }
          index = n;

          // Heapify from the last non-leaf node down to the root
          for(int i = index / 2; i >= 1; i--) {
               heapify(arr, n, i);
          }
     }


     // Heap Sort
     void heapSort() {
          // Build the Heap
          for(int i = index / 2; i >= 1; i--) {
               heapify(arr, index, i);
          }

          // Extract elements from the heap one by one
          for(int i = index; i > 1; i--) {
               // Perform deleteHeap operation
               
               // Move current root to end
               swap(arr[1], arr[i]);

               // Decrease the size
               index--;

               // Heapify the root element to maintain the heap property
               heapify(arr, index, 1);
          }
     }
};



int main() {
     Heap h(6);

     h.insert(50);
     h.insert(30);
     h.insert(20);
     h.insert(10);
     h.insert(40);

     cout << "Heap after insertions: ";
     h.printHeap();

     // h.deleteFromHeap();
     // cout << "Heap after deleting root: ";
     // h.printHeap();

     // int inputArray[] = {-1, 10, 20, 30, 40, 50};
     // int n = sizeof(inputArray) / sizeof(inputArray[0]);

     // Heap h2(n);
     // h2.buildHeap(inputArray, n);

     // cout << "Heap built from array: ";
     // h2.printHeap();

     h.heapSort();
     cout << "Array after heap sort: ";
     h.printHeap();


     return 0;
}











