// Date    : 2018-12-25 13:16:29
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXM = 1005;

long long p[MAXM];
long long n,m=0,MOD;

long long qpow(long long a,long long k)
{
	long long ans=1;
	for (long long i=0;(1ll<<i)<=k;i++,a=a*a%MOD)
		if (k&(1ll<<i))
			ans=ans*a%MOD;
	return ans;
}

int main()
{
//	freopen("51nod1135.in","r",stdin);
//	freopen("51nod1135.out","w",stdout);
	scanf("%lld",&MOD);
	n=MOD-1;
	for (long long i=2;i*i<=n;i++)
	{
		if (n%i)
			continue;
		p[m++]=i;
		while (n%i==0)
			n/=i;
	}
	if (n!=1)
		p[m++]=n;
	bool flag;
	for (long long i=1;i<=MOD;i++)
	{
		flag=1;
		for (long long j=0;j<m && flag;j++)
			if (qpow(i,(MOD-1)/p[j])==1)
				flag=0;
		if (flag)
		{
			printf("%lld\n",i);
			break;
		}
	}
	return 0;
}