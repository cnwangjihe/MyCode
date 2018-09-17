#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int a,b;

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

int main()
{
	int n=32767;
	for (int i=1;i<=n;i++)
		printf("%d:%d\n",i,1ll*qpow(i,MOD-2)%MOD);
	return 0;
}