#include <stdio.h>  
using namespace std; 
#define p 100003  
   
long long n,m,ans;  
   
long long power(long long t,long long k){  
    if (t==1) return k%p;  
    long long x=power(t>>1,k);  
    x=x*x%p;  
    if ((t>>1)*2!=t) x=x*k%p;  
    return x;  
}  
   
int main(){  
    scanf("%lld %lld",&m,&n);  
    ans=(power(n,m)%p-m%p*power(n-1,m-1)%p)%p;  
    while (ans<0) ans+=p;  
    printf("%lld\n",ans);  
    return 0;  
}  