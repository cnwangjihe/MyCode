#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 3000009;

long long n,MOD;
long long a[MAXN],b[MAXN],inv[MAXN];

long long qpow(long long a,long long k)
{
	long long ans=1;
	for (long long i=0;(1ll<<i)<=k;i++,a=(a*a)%MOD)
		if ((1ll<<i)&k)
			ans=(ans*a)%MOD;
	return ans;
}

int main()
{
	scanf("%lld%lld",&n,&MOD);
	a[1]=1;
	for (int i=2;i<=n;i++)
		a[i]=(a[i-1]*i)%MOD;
	b[n]=qpow(a[n],MOD-2);
	for (int i=n-1;i>1;i--)
		b[i]=(b[i+1]*(i+1))%MOD;
	for (int i=n;i>1;i--)
		inv[i]=(b[i]*a[i-1])%MOD;
	inv[1]=1ll;
	for (int i=1;i<=n;i++)
		printf("%lld\n",inv[i]);
	return 0;
}