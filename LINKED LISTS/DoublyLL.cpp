#include <iostream>
#include <vector>
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
     Node *back;

     Node (int data) {
          this->data = data;
          this->next = NULL;
          this->back = NULL;
     }

     Node (int data1, Node *next1, Node *back1) {
          this->data = data1;
          this->next = next1;
          this->back = back1;
     }
};


Node* convertArrToLL(vector<int> &arr) {
     Node *head = new Node(arr[0]);
     Node *prev = head;

     for (int i = 1; i < arr.size(); i++){
          Node *new_Node = new Node(arr[i], NULL, prev);
          prev->next = new_Node;
          prev = new_Node;
     }

     return head;
}

void printLL(Node *head) {
     while(head){
          cout << head->data << " ";
          head = head->next;     
     }
     cout << endl;
}




// Deletion 
Node* deleteHead(Node *head){
     // Edge Case
     if (head == NULL || head->next == NULL){
          return NULL;
     }
     
     Node *prev = head;
     head = head->next;
     prev->next = NULL;
     head->back = NULL;
     delete prev;

     return head;
}

Node* deleteTail(Node *head){
     // Edge Case
     if (head == NULL || head->next == NULL){
          return NULL;
     }

     Node *Tail = head;
     while(Tail->next != NULL) {
          Tail = Tail->next;
     }
     
     Node *new_Tail = Tail->back;
     new_Tail->next = NULL;
     Tail->back = NULL;
     delete(Tail);

     return head;
}

Node* removeKthElement(Node *head, int k){
     if (head == NULL){
          return NULL;
     }
     
     Node *temp = head;
     int count = 0;

     while(temp){
          count++;

          if (count == k) break;
          else temp = temp->next;  
     }
     
     Node *prev = temp->back;
     Node *front = temp->next;

     if (prev == NULL && front == NULL){
          return NULL;
     }
     
     else if (prev == NULL){
          return deleteHead(head);
     }

     else if (front == NULL){
          return deleteTail(head);
     }
     
     prev->next = front;
     front->back = prev;
     temp->next = NULL;
     temp->back = NULL;

     return head;
}

void deleteNode(Node *temp){
     Node *prev = temp->back;
     Node *front = temp->next;
     
     if (front == NULL){
          prev->next = NULL;
          temp->back = NULL;
          free(temp);
          return;
     }
     
     prev->next = front;
     front->back = prev;
     
     temp->next = temp->back = NULL;
     free(temp);
}


// Insertion
Node* insertBeforeHead(Node *head, int val){
     Node *newHead = new Node(val, head, NULL);
     head->back = newHead;

     return newHead;
}

Node* insertBeforeTail(Node *head, int val){
     // Edge Case
     if (head->next == NULL){
          return insertBeforeHead(head,val);
     }

     Node *tail = head;
     while(tail->next != NULL){
          tail = tail->next;
     }
     
     Node *prev = tail->back;
     Node *newNode = new Node(val, tail, prev);
     prev->next = newNode;
     tail->back = newNode;
     
     return head;
}

Node* insertBeforeKthElement(Node *head, int k, int val){
     if (k == 1){
          return insertBeforeHead(head,val);
     }

     Node *temp = head;
     int cnt = 0;
     while(temp->next != NULL){
          cnt++;

          if (cnt == k) break;
          temp = temp->next;
     }

     Node *prev = temp->back;
     Node *newNode = new Node(val, temp, prev);
     prev->next = newNode;
     temp->back = newNode;

     return head;
}

void insertBeforeNode(Node *temp, int val){
     Node *prev = temp->back;
     Node *newNode = new Node(val,temp, prev);
     prev->next = newNode;
     temp->back = newNode;
}





int main() {
     vector<int> arr = {100,23,46,7,89};
     Node *head = convertArrToLL(arr);
     cout << "Before: ";
     printLL(head);
     
     cout << "After:  ";
     
     // head = deleteHead(head);
     // printLL(head);
     
     // head = deleteTail(head);
     // printLL(head);
     
     // head = removeKthElement(head, 2);
     // printLL(head);
     
     // deleteNode(head->next->next);
     // printLL(head);

     // head = insertBeforeHead(head, 295);
     // printLL(head);
    
     // head = insertBeforeTail(head, 295);
     // printLL(head);

     // head = insertBeforeKthElement(head, 3, 295);
     // printLL(head);
     
     insertBeforeNode(head->next->next, 295);
     printLL(head);

     
     return 0;
}     
