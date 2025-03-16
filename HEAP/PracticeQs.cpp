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




// LEETCODE : 215 (Kth largest element)

// Approach - 1 : EFFICIENT -->     T.C [O(nlogk)] ; S.C [O(k)]
int findKthLargest_1(vector<int>& nums, int k) {
     // Min-heap to store the k largest elements

     priority_queue<int, vector<int>, greater<int>> minHeap;
     // greater<int> is the comparator that arranges elements in ascending order.
     
     for(auto num : nums) {
          // Add elements to the heap
          minHeap.push(num);     // The push operation has a time complexity of O(logk)
          // If the heap size exceeds k, remove the smallest element
          if(minHeap.size() > k) {
               minHeap.pop();
          }
     }
     
     // The root of the min-heap is the kth largest element
     return minHeap.top();
}

// Approach - 2 : T.C [O(n + klogn)]; S.C[O(n)]
int findKthLargest_2(vector<int>& nums, int k) {
     // Max-heap to store all elements
     priority_queue<int> maxHeap(nums.begin(), nums.end());

     // Remove the largest element (k-1) times
     for(int i = 0; i < k - 1; i++) {
          maxHeap.pop();
     }

     // Note : Popping k elements from the max-heap has a time complexity of O(klogn)
     // as each pop operation takes O(logn).


     // The top element is now the kth largest element
     return maxHeap.top();
}






// Minimum Cost Of Ropes
long long minCost(vector<long long> &arr) {
     priority_queue<long long, vector<long long>, greater<long long>> pq;

     for(auto num : arr) {
          pq.push(num);
     }
     
     int cost = 0;
     while(pq.size() != 1) {
          long long first = pq.top();
          pq.pop();

          long long second = pq.top();
          pq.pop();

          long long sum = first + second;
          cost = cost + sum;

          pq.push(sum);
     }

     return cost;
}







// IMPORTANT *****************************

// Merge K sorted Arrays
struct Element{
     int value;     // value of the element
     int row;       // row index of the element
     int col;       // column index of the element

     Element(int x, int y, int z) {
          this->value = x;
          this->row = y;
          this->col = z;
     }
};

// Comparison operator for min-Heap
struct Compare{
     bool operator()(Element& a, Element& b) {
          return a.value > b.value;
     }
};

vector<int> mergeKSortedArrays(vector<vector<int>>& arr, int k) {
     // Min-heap (priority queue) to store the smallest elements from each array
     priority_queue<Element, vector<Element>, Compare> minHeap;

     // Initialize the heap with the first element of each row
     for(int i = 0; i < k; i++) {
          if(!arr[i].empty()) {
               minHeap.push(Element(arr[i][0], i, 0));
          }
     }

     vector<int> result;

     while(!minHeap.empty()) {
          Element current = minHeap.top();
          minHeap.pop();
          
          // Add the smallest element to the result array
          if(current.col + 1 < arr[current.row].size()) {
               minHeap.push(Element(arr[current.row][current.col], current.row, current.col + 1));
          }
     }
     
     return result;
}







// IMPORTANT *****************************

// LEETCODE : 23 (Merge K Sorted Lists)
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct Comparison{
     bool operator()(ListNode* a, ListNode* b) {
          return a->val > b->val;
     }
};

ListNode* mergeKLists(vector<ListNode*>& lists){
     priority_queue<ListNode*, vector<ListNode*>, Comparison> pq;
     ListNode* head = NULL;
     ListNode* tail = NULL;

     for(int row = 0; row < lists.size(); row++) {
          ListNode* temp = lists[row];
          if(temp != NULL) {
               pq.push(temp);
          }
     }

     while(!pq.empty()) {
          ListNode* current = pq.top();
          pq.pop();

          if(head == NULL && tail == NULL) {
               // it is First Node
               head = current;
               tail = current;
          }

          else {
               // Not the first Node
               tail->next = current;
               tail = current;
          }

          if(tail->next != NULL) {
               pq.push(tail->next);
          }

     }

     return head;

}








// LEETCODE : 632 (Smallest Range Covering Elements from K Lists)
class Info{
public:
     int val;
     int rIndex;
     int cIndex;

     Info(int a, int b, int c) {
          this->val = a;
          this->rIndex = b;
          this->cIndex = c;
     }
};

class Comparee{
public:
     bool operator()(Info* a, Info* b) {
          return a->val > b->val;
     }
};

vector<int> smallestRange(vector<vector<int>>& nums) {
     priority_queue<Info*, vector<Info*>, Comparee> pq;

     vector<int> ans;

     int mini = INT_MAX;
     int maxi = INT_MIN;

     for(int row = 0; row < nums.size(); row++) {
          int element = nums[row][0];
          Info* temp = new Info(element, row, 0);
          mini = min(element, mini);
          pq.push(temp);
     }

     int ans_start = mini;
     int ans_end = maxi;

     while(!pq.empty()) {
          Info* front = pq.top();
          pq.pop();

          int frontData = front->val;
          int front_rowIn = front->rIndex;
          int front_colIn = front->cIndex;
          
          // Remember
          mini = frontData;
          
          // ans update
          if((maxi - mini) < (ans_end - ans_start)) {
               ans_start = mini;
               ans_end = maxi;
          }

          // Insert further elements
          if(front_colIn + 1 < nums[front_rowIn].size()) {
               int element = nums[front_rowIn][front_colIn + 1];
               Info* temp = new Info(element, front_rowIn, front_colIn + 1);
               maxi = max(maxi, element);
               pq.push(temp);
          }

          else {
               break;
          }
     }

     ans.push_back(ans_start);
     ans.push_back(ans_end);
}







// LEETCODE : 647 (Top K Frequent Elements)
vector<int> topKFrequent(vector<int>& nums, int k) {
     
     unordered_map<int, int> freqMap;
     for(int num : nums) {
          freqMap[num]++;
     }
     
     // Min heap that stores pairs of (frequency, number)
     priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>>> minHeap;
     
     for(auto entry : freqMap) {
          minHeap.push({entry.second, entry.first});
          if(minHeap.size() > k) {
               minHeap.pop();    // Remove the least frequent element
          }
     }
     
     vector<int> ans;

     // Extract the elements from the min heap
     while(!minHeap.empty()) {
          ans.push_back(minHeap.top().second);
          minHeap.pop();
     }
     
     return ans;
}





// LEETCODE : 1753 (Maximum Score From Removing Stones)
int maximumScore(int a, int b, int c) {
     priority_queue<int,vector<int>> maxHeap;
     maxHeap.push(a);
     maxHeap.push(b);
     maxHeap.push(c);
     
     int score = 0;

     while(maxHeap.size() > 1){
          int pile1 = maxHeap.top(); maxHeap.pop();
          int pile2 = maxHeap.top(); maxHeap.pop();
          
          score++;
          pile1--; pile2--;

          if(pile1 > 0) maxHeap.push(pile1);
          if(pile2 > 0) maxHeap.push(pile2);
     }
     
     return score;
}






// LEETCOOE : 973 (K Closest Points to Origin)
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
     // Max-heap to store the closest points, ordered by distance
     priority_queue<pair<int, vector<int>>> maxHeap;

     for(auto &point : points){
          int x = point[0];
          int y = point[1];
          // Calculate squared distance from the origin
          int distance = x*x + y*y;    // Avoid computing the square root for simplicity and efficiency.

          // Push current point with its distance to the max-heap
          maxHeap.push({distance, point});

          if(maxHeap.size() > k) {
               maxHeap.pop();

          }
     }

     vector<vector<int>> result;
     while(!maxHeap.empty()){
          auto point = maxHeap.top(); maxHeap.pop();
          result.push_back(point.second);
     }
     
     return result;
}






// LEETCODE : 239 (Sliding Window Maximum)
vector<int> maxSlidingWindow(vector<int>& nums, int k){
     // Max heap to store pairs of (value, index)
     priority_queue<pair<int,int>> maxHeap;
     vector<int> result;

     for(int i = 0; i < nums.size(); i++) {
          // Add current element to the max heap
          maxHeap.push({nums[i], i});
          
          // Check if we have filled the window (i >= k - 1)
          if(i >= k - 1) {
               // Remove elements out of the current window range
               while(!maxHeap.empty() && maxHeap.top().second <= i - k) {
                    maxHeap.pop();
               }
               
               // The top element is the maximum in the current window
               result.push_back(maxHeap.top().first);
          }
     }

     return result;
}







int main() {
     // vector<int> nums1 = {1, 1, 1, 2, 2, 3};
     // int k1 = 2;
     // vector<int> result1 = topKFrequent(nums1, k1);
     // cout << "Test case 1: [ ";
     // for (int num : result1) {
     //      cout << num << " ";
     // }
     // cout << "]" << endl;
     // cout << endl;

     vector<vector<int>> points1 = {{1, 3}, {-2, 2}};
     int k1 = 1;
     auto result1 = kClosest(points1, k1);
     cout << "Result 1:\n";
     for (const auto& point : result1) {
          cout << "[" << point[0] << ", " << point[1] << "] ";
     }
     cout << endl;

     vector<vector<int>> points2 = {{3, 3}, {5, -1}, {-2, 4}};
     int k2 = 2;
     auto result2 = kClosest(points2, k2);
     cout << "Result 2:\n";
     for (const auto& point : result2) {
          cout << "[" << point[0] << ", " << point[1] << "] ";
     }
     cout << endl;

     return 0;
}