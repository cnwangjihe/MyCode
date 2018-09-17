#include <bits/stdc++.h>

using namespace std;

long long a,b,p,ans;

inline long long mul(long long a,long long b)
{
	return (__int128)a * b % p;
}

long long gcd(long long a,long long b)
{
	return a%b==0?b:gcd(b,a%b);
}

inline long long qpow(long long a,long long k)
{
	long long ans=1ll;
	for (long long i=0;(1ll<<i)<=k;i++,a=mul(a,a))
		if (k&(1ll<<i))
			ans=mul(ans,a);
	return ans;
}

long long ex_bsgs(long long a,long long b,long long p)
{
	map <long long,long long> mp;
	long long x=0,q=1,m,t;
	if (a == 0)
		return b > 1 ? -1 : b == 0 && p > 1;
	while ((t=gcd(a,p))!=1ll)
	{
		if (b==1)
			return x;
		if (b%t)
			return -1;
		b/=t;
		p/=t;
		x++;
		q=mul(a/t,q);
	}
	m=sqrt(p);
	t=mul(b,a);
	for (long long i=1;i<=m;i++,t=mul(t,a))
		mp[t]=i;
	t=qpow(a,m);
	for (long long i=1;i<=p/m+1;i++)
	{
		q=mul(q,t);
		if (mp.count(q))
			return (x+mul(i,m)-mp[q]+p)%p;
	}
	return -1;
}

int main()
{
	scanf("%lld%lld",&b,&p);
	printf("%lld\n",ex_bsgs(10ll,(mul(9ll,b)+1ll)%p,p));
	return 0;
}