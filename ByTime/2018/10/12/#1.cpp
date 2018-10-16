#include <iostream> 
using namespace std; 
int fun(int n, int fromPos, int toPos) { 
 int t, tot; 
    if (n == 0) 
     return 0; 
    for (t = 1; t <= 3; t++) 
        if (t != fromPos && t != toPos) 
            break; 
    tot = 0; 
    tot += fun(n - 1, fromPos, t); 
    tot++; 
    tot += fun(n - 1, t, toPos); 
    return tot; 
} 
 
int main() { 
    int n; 
    cin >> n; 
    cout << fun(n, 1, 3) << endl; 
    return 0; 
} 