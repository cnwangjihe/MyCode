#include <iostream> 
#include <string> 
using namespace std; 
int main() { 
 int len, maxlen; 
 string s, ss; 
 maxlen = 0; 
 do { 
     cin >> ss; 
     len = ss.length(); 
     if (ss[0] == '#') 
   break; 
     if (len > maxlen) { 
      s = ss; 
      maxlen = len; 
     } 
 } while (true); 
 cout << s << endl; 
    return 0; 
} 