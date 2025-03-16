#include <iostream>
#include<vector>
#include <algorithm> 
#include <climits>
#include <set>
#include <list>
#include <map>
#include <math.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <numeric>
using namespace std;


class Node {
public:
     int data;
     Node *next;
     
     Node (int value, Node *next1) {
          this->data = value;
          this->next = next1;
     }

     Node (int value) {
          this->data = value;
          this->next = NULL;
     }
};


Node* convertArrToLL(vector<int> &arr) {
     Node* head = new Node(arr[0]);
     Node* mover = head;

     for (int i = 1; i < arr.size(); i++){
          mover->next = new Node(arr[i]);
          mover = mover->next;
     }
     
     return head;
}

void printLL(Node *head){
     while(head) {
          cout << head-> data << " -> ";
          head = head->next;
     }
     cout << "NULL" << endl;
}



int lengthLL(Node *head) {
     Node *temp = head;
     int cnt = 0;

     while(temp){
          temp = temp->next;
          cnt++;
     }
     return cnt;
}

bool searchInLL(Node *head, int k) {
     Node *temp = head;
     
     while(temp){
          if (temp->data == k) return true;
          temp = temp->next;
     }

     return false;
}




// REMOVE

Node* removeHead(Node *head) {
     // Edge Case
     if (head == NULL) return head;

     Node *temp = head;
     head = head->next;
     delete(temp);
     return head;
}

Node* removeTail(Node *head) {
     // Edge Case
     if (head == NULL || head->next == NULL) return NULL;
     
     Node *temp = head;
     while(temp->next->next) {
          temp = temp->next;
     }

     delete(temp->next);
     temp->next = NULL;

     return head;
}

Node* removeKthElement(Node *head, int k){
     // Edge Case
     if (head == NULL) return head;
     if (k == 1) {
          Node* temp = head;
          head = head->next;
          delete(temp);
          return head;
     }

     int count = 0;
     Node *temp = head;
     Node *prev = NULL;

     while (temp){
          count++;
          if (count == k) {
               prev->next = prev->next->next;
               delete(temp);
               break;
          }
          prev = temp;
          temp = temp->next;
     }
     
     return head;
}

Node* removeEl(Node *head, int element){
     // Edge Case
     if (head == NULL) return head;
     if (head->data == element) {
          Node* temp = head;
          head = head->next;
          delete(temp);
          return head;
     }

     Node *temp = head;
     Node *prev = NULL;

     while (temp){
          if (temp->data == element) {
               prev->next = prev->next->next;
               delete(temp);
               break;
          }
          prev = temp;
          temp = temp->next;
     }
     
     return head;
}



// INSERT

Node* insertHead(Node *head, int value) {
     Node *temp = new Node(value,head);
     return temp;
}

Node* insertTail(Node *head, int value) {
     // Edge Case
     if (head == NULL){
          return new Node(value);
     }

     Node *temp = head;
     while (temp){
          temp = temp->next;
     }

     Node *newNode = new Node(value);
     temp->next = newNode;

     return head; 
}

Node* insertPosition(Node *head, int element, int k) {
     // Edge Case
     if (head == NULL){
          if (k == 1){
               return new Node(element);
          }
          else {
               return head;
          }
     }
     
     if (k == 1) {
          return new Node(element, head);
     }
     
     int count = 0;
     Node *temp = head;

     while (temp) {
          count++;

          if (count == k-1) {
               Node *newNode = new Node(element, temp->next);
               temp->next = newNode;
               break;
          }

          temp = temp->next;
     }

     return head;
}

Node* insertBeforeValue(Node *head, int element, int value) {
     // Edge Case
     if (head == NULL){
          return NULL;
     }
     
     if (head->data == value) {
          return new Node(element, head);
     }
     
     Node *temp = head;

     while (temp) {

          if (temp->next->data == value) {
               Node *newNode = new Node(element, temp->next);
               temp->next = newNode;
               break;
          }

          temp = temp->next;
     }

     return head;
}




int main() {
     vector<int> arr = {100,23,46,7,89};
     Node *head = convertArrToLL(arr);
     cout << "Before: ";
     printLL(head);
     
     cout << "After:  ";

     // cout << head->data << endl;
     // cout << lengthLL(head) << endl;
     // cout << boolalpha << searchInLL(head, 89) << endl;

     // head = removeHead(head);
     // printLL(head);

     // head = removeTail(head);
     // printLL(head);

     // head = removeKthElement(head,5);
     // printLL(head);

     // head = removeEl(head,46);
     // printLL(head);

     // head = insertHead(head,99);
     // printLL(head);
     
     // head = insertPosition(head, 56, 6);
     // printLL(head);
     
     head = insertBeforeValue(head, 99, 46);
     printLL(head);



     return 0;

}