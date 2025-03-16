#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <stack>
#include <math.h>
#include <limits.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;


class Queue {
private:
     int *arr;
     int n;
     int front;
     int rear;

public:

     Queue(int size) {
          this->n = size;
          arr = new int[size];
          front = -1;
          rear = -1; 
     }

     void push(int val) {
          // OverFlow
          if (front == 0 && rear == n-1) {
               cout << "Queue is full" << endl;
          }
          
          if (front == -1 && rear == -1) {
               front++;
               rear++;
               arr[front] = val;
          }
          
          // General Cases
          else {
               rear++;
               arr[rear] == val;
          }


     }

     void pop() {  
          // Underflow
          if (front == -1 && rear == -1) {
               cout << "Queue is empty" << endl;
          }
          
          if (front == rear) {
               arr[rear] = -1;
               rear = -1;
               front = -1;
          }

          else {
               arr[front] = -1;
               front++;
          }

     }

     int getFront() {
          if (front == -1) {
               cout << "Queue is empty" << endl;
          }
          else return arr[front];

     }
     
     int getRear() {
          if (rear == -1) {
               cout << "Queue is empty" << endl;
          }
          else return arr[rear];

     }
     
     int getSize() {
          if (front == -1 && rear == -1) {
               return 0;
          }
          else return rear - front + 1;
     }
     
     bool isEmpty() {
          if (front == -1 && rear == -1) {
               return true;
          }
          else {
               return false;
          }

     }

     void printAll() {
          for (int i = 0; i < n; i++) {
               cout << arr[i] << " ";
          }
          cout << endl;
     }

};




class Deque {
private:
     int *arr;
     int n;
     int front;
     int rear;
            
public:

     Deque(int size) {
          this->n = size;
          arr = new int[size];
          front = -1;
          rear = -1;
     }

     bool isEmpty() {
          return front == -1;
     }


     void pushFront(int val) {
          if ((front == 0 && rear == n-1) || (front == rear + 1)) {
               cout << "Deque is full" << endl;
               return;
          }

          else if (front == -1 && rear == -1) {
               front = 0;
               rear = 0;
               arr[front] = val;
          }
          
          // Circular wrap when front is at 0 but space is available at the end
          else if (front == 0) {
          front = n - 1;
          arr[front] = val;
          }


          else {
               front--;
               arr[front] = val;
          }
     }

     void pushBack(int val) {
          if (rear == n-1) {
               cout << "Deque is full" << endl;
          }

          else if (front == -1 && rear == -1) {
               rear = 0;
               front = 0;
               arr[rear] = val;
          }

          else {
               rear++;
               arr[rear] = val;
          }

     }
      

     void popFront() {
          if (front == -1 && rear == -1) {
               cout << "Deque is empty" << endl;
          }
          
          else if (front == rear) {
               front = -1;
               rear = -1;
          }

          else {
               arr[front] = -1;
               front++;
          }
     }


     void popBack() {
          if (front == -1 && rear == -1) {
               cout << "Deque is empty" << endl;
          }
          
          else if (front == rear) {
               front = -1;
               rear = -1;
          }

          else {
               arr[rear] = -1;
               rear--;
          }
     }


     void printAll() {
          if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
          }

          int i = front;
          while (true) {
               cout << arr[i] << " ";
               if (i == rear) {
                    break;
               }
               i = (i + 1) % n;  // Circular increment
          }
          cout << endl;
    }


};




class CircularQueue {
public:
     int n;
     int *arr;
     int front;
     int rear;

     CircularQueue(int size) {
          this->n = size;
          arr = new int[size];
          front = -1;
          rear = -1;
     }


     void push(int val) {
          if((front == 0 && rear == -1) || (rear = front - 1)) {
               cout << "Queue is full" << endl;
          }
          
          else if (front == -1 && rear == -1) {
               front++;
               rear++;
               arr[rear] = val;
          }

          else if (rear == n-1 && front != 0) {
               rear = 0;
               arr[rear] = val;
          }

          else {
               rear++;
               arr[rear] = val;
          }
     }

     void pop() {
          if (front == -1 && rear == -1){
               cout << "Queue is empty" << endl;
          }

          else if (front == rear) {
               arr[front] = -1;
               front = -1;
               rear = -1;
          }

          else if (front = n-1) {
               front = 0;
               arr[front] = -1;
          }

          else {
               arr[front] = -1;
               front++;
          }
     }
     

     int getFront() {
          if (front == -1) {
               cout << "Queue is empty" << endl;
          }
          else {
               return arr[front];
          }
     }


     int getSize() {
          if (front == -1)  {
               return 0;
          }

          else if (rear >= front){
               return rear - front + 1;
          }
          
          // Important
          else {
               return n-front+rear+1;
          }
     }

     bool isEmpty() {
          if (front == -1 && rear == -1) {
               return true;
          } 
          else {
               return false;
          }
     }


     void printAll() {
          if (isEmpty()) {
            cout << "CircularQueue is empty" << endl;
            return;
          }

          int i = front;
          while (true) {
               cout << arr[i] << " ";
               if (i == rear) {
                    break;
               }
               i = (i + 1) % n;  // Circular increment
          }
          cout << endl;
     }


};




class DeCircularQueue {
public:
     int n;
     int *arr;
     int front;
     int rear;

     DeCircularQueue(int size) {
          this->n = size;
          arr = new int[size];
          front = -1;
          rear = -1;
     }

     void pushBack(int val) {
          if((front == 0 && rear == -1) || (rear = front - 1)) {
               cout << "Queue is full" << endl;
          }
          
          else if (front == -1 && rear == -1) {
               front++;
               rear++;
               arr[rear] = val;
          }

          else if (rear == n-1 && front != 0) {
               rear = 0;
               arr[rear] = val;
          }

          else {
               rear++;
               arr[rear] = val;
          }
     }

     
     void pushFront(int val){
          if((front == 0 && rear == -1) || (rear = front - 1)) {
               cout << "Queue is full" << endl;
          }
          
          else if (front == -1 && rear == -1) {
               front++;
               rear++;
               arr[rear] = val;
          }

          else if (front = 0 && rear != n-1) {
               front = n-1;
               arr[front] = val;
          }

          else {
               front--;
               arr[front] = val;
          }


     }



     void popFront() {
          if (front == -1 && rear == -1){
               cout << "Queue is empty" << endl;
          }

          else if (front == rear) {
               arr[front] = -1;
               front = -1;
               rear = -1;
          }

          else if (front = n-1) {
               front = 0;
               arr[front] = -1;
          }

          else {
               arr[front] = -1;
               front++;
          }

     }
    

     
     void popBack() {
          if (front == -1 && rear == -1){
               cout << "Queue is empty" << endl;
          }

          else if (front == rear) {
               arr[front] = -1;
               front = -1;
               rear = -1;
          }

          else if (rear == 0) {
               arr[rear] = -1;
               rear = n-1;
          }

          else {
               arr[rear] = -1;
               rear--;
          }

     }




};









int main() {
     Deque q(5);
     q.pushFront(10);
     q.printAll();
     q.pushFront(20);
     q.printAll();
     q.pushFront(30);
     q.printAll();
     q.pushFront(40);
     q.printAll();
     q.pushFront(50);
     q.printAll();
     q.popFront();
     q.printAll();
     
     
     // cout << q.getSize() << endl;

     // q.pop();
     // cout << q.getSize() << endl;

     // cout << q.getFront() << endl;
     // cout << q.getRear() << endl;




}