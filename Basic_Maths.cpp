#include <iostream>
#include<vector>
#include <string>
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



int countPrimes_1 (int n) {       // ------
     // Sieve of Eratosthenes : T.C --> O ( n*log(logn) )

     if ( n==0 ) return 0;

     vector <bool> prime(n, true);
     prime[0]=prime[1]= false;

     int ans = 0;

     for ( int i=2; i<n; i++ ) {

          if ( prime[i] ){
               ans++;

               int j=2*i;
               while ( j < n ){
                    prime[j] = false;
                    j += i;
               }
          }
     }

     return ans;

    }
                                  //      |
int countPrimes_2 (int n) {       //      |
     // Sieve of Eratosthenes : T.C --> O ( n*log(logn) )

     if ( n==0 ) return 0;

     vector <bool> is_prime( n, true );
     is_prime[0]=is_prime[1]= false;

     for ( int i=2; i<=sqrt(n); i++ ) {
          if ( is_prime[i]) {                // Hoga hee kyunki sabhi True set kar rkhe hai
                             
               for ( int j= i*i; j<n; j += i ) {
                    is_prime[j] = false;
               }
          }
     } 

     int Prime_Count = 0;

     for ( int i=2; i<n; i++ ){
          if( is_prime[i] ) {
               Prime_Count++;
          }
     }

     return Prime_Count;



        
    }
                                  //      |------->   LEETCODE : 204
bool isPrime (int num) {          //      |      
     // Handle small cases directly
     if (num <= 1) return false;
     if (num == 2 || num == 3) return true;
     if (num % 2 == 0 || num % 3 == 0) return false;

     // Check for factors from 5 upwards, skipping multiples of 2 and 3

     for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
     }

     return true;
}
                                  //      |         
int countPrimes_3 (int n) {       // ------
     
     // Segmented Sieve Algorithm : Both the isPrime and countPrimes functions is T.C -->  O ( n^3/2 )
     int prime_count = 0;
     for (int i = 2; i < n; ++i) {
          if (isPrime(i)) {
            ++prime_count;
          }
     }
    return prime_count;
}
                                  





int FastPower ( int num, int power ) {

     if ( power == 0 ) return 1;

     int half = FastPower (num, power/2);
     if (power % 2 == 0){
          return half * half;
     }
     else{
          return half * half * num;
     }
}


int GCD ( int a, int b ) {
     //  LCM(a,b) * GCD(a,b) = a*b
     //  LCM(a,b) = (a*b)/GCD(a,b)
     if ( a == 0 ) return b;
     if ( b == 0 ) return a;

     while (a > 0 && b > 0) {
          if (a > b) {
               a = a - b;
          }
          if (b > a) {
               b = b - a;
          }
     }

     return a == 0 ? b : a;

}







// Assuming Individual Digits in Array
vector<int> addNumbers(vector<int> num1, vector<int> num2) {
     int n1 = num1.size();
     int n2 = num2.size();
     int carry = 0;
     vector<int> result;

     // Iterate through both arrays simultaneously, handling different lengths
     for (int i = n1 - 1, j = n2 - 1; i >= 0 || j >= 0 || carry > 0; i--, j--) {
        int x = (i >= 0) ? num1[i] : 0;
        int y = (j >= 0) ? num2[j] : 0;
        int sum = x + y + carry;
        carry = sum / 10;
        result.push_back(sum % 10);
     }

     reverse(result.begin(), result.end());
     return result;
}


// LEETCODE : 415 ( Using Recursion )
void addStrings(string &num1, int n1, string &num2, int n2, int carry, string &ans) {
     // Base Case
     if ( n1 < 0 && n2 < 0){
          if (carry != 0){
               ans.push_back(carry + '0');
          }
          return;
     }

     int digit1 = (n1 >= 0 ? num1[n1] : '0') - '0';
     int digit2 = (n2 >= 0 ? num2[n2] : '0') - '0';
     int sum = digit1 + digit2 + carry;
     carry = sum / 10;
     int number = sum % 10;
     ans.push_back(number + '0');

     addStrings(num1, n1 - 1, num2, n2 - 1, carry, ans);

}








int main() {
    string num1 = "243";
    string num2 = "564";
    string ans = "";
    int carry = 0;
    addStrings(num1, num1.size() - 1, num2, num2.size() - 1, carry, ans);
    
    reverse(ans.begin(), ans.end());

    cout << "The sum is: " << ans << endl;
    
    return 0;
}