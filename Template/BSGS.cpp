#include <bits/stdc++.h>

using namespace std;

long long a,b,p,ans;

long long gcd(long long a,long long b)
{
	return a%b==0?b:gcd(b,a%b);
}

inline long long qpow(long long a,long long k)
{
	long long ans=1ll;
	for (long long i=0;(1ll<<i)<=k;i++,a=(a*a)%p)
		if (k&(1ll<<i))
			ans=(ans*a)%p;
	return ans;
}

long long ex_bsgs(long long a,long long b,long long p)
{
	map <long long,long long> mp;
	long long x=0,q=1,m,t;
	if (a == 0)
		return b > 1 ? -1 : b == 0 && p > 1;
	while ((t=gcd(a,p))!=1)
	{
		if (b==1)
			return x;
		if (b%t)
			return -1;
		b/=t;
		p/=t;
		x++;
		q=a/t*q%p;
	}
	m=sqrt(p);
	t=b*a%p;
	for (long long i=1;i<=m;i++,t=t*a%p)
		mp[t]=i;
	t=qpow(a,m);
	for (long long i=1;i<=p/m+1;i++)
	{
		q=q*t%p;
		if (mp.count(q))
			return x+i*m-mp[q];
	}
	return -1;
}

int main()
{
	while (scanf("%lld%lld%lld",&a,&p,&b) && (a+p+b))
	{
		ans=ex_bsgs(a%p,b%p,p);
		if (~ans)
			printf("%lld\n",ans);
		else
			printf("No Solution\n");
	}
	return 0;
}