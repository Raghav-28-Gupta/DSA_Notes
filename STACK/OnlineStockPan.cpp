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


class StockSpanner {
public:
     // Stack to store pairs of (price, span)
     stack<pair<int, int>> st;

     StockSpanner() {
        
     }
    
     int next(int price) {
        int span = 1;
        
        while (!st.empty() && st.top() <= price) {
          span = st.top().second;
          st.pop();
        }

        st.push({price,span});

        return span;
     }
};

