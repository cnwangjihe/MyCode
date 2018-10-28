#include <bits/stdc++.h>

using namespace std;

const long long INF = 10000000000000000ll;

long long n,m,k,ans=INF;

long long calc(long long a,long long b)
{
	if (b>k)
		return INF;
	return b-1+(a%2?a:a/2);
}

int main()
{
	freopen("bread.in","r",stdin);
	freopen("bread.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	n+=m;
	for (long long i=1;i*i<=n;i++)
	{
		if (n%i)
			continue;
		ans=min(ans,min(calc(i,n/i),calc(n/i,i)));
	}
	printf("%lld\n",ans);
	return 0;
}