#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 109;

int n,m,sr,sb,sg;
long long MOD,ans=1;
long long f[MAXN];

long long qpow(long long a,long long n)
{
    long long ans=1,k=a;
    for (long long i=0;(1ll<<i)<=n;i++,k*=k,k%=MOD)
        if ((1ll<<i)&n) ans*=k,ans%=MOD;
    return ans;
}

long long getC(int n,int m)
{
    return f[n]*qpow((f[m]*f[n-m])%MOD,MOD-2);
}

int main()
{
    scanf("%d%d%d%d%lld",&sr,&sb,&sg,&m,&MOD);
    n=sr+sb+sg;
    f[1]=1;
    for (int i=2;i<=n;i++)
        f[i]=f[i-1]*i,f[i]%=MOD;
    ans=getC(n,sr)*getC(n-sr,sb);
    ans%=MOD;
    ans=ans*qpow(m+1,MOD-2);
    ans%=MOD;
    printf("%lld\n",ans);
    return 0;
}