#include <bits/stdc++.h>

using namespace std;

long long n,ans;


int main()
{
	freopen("2667.in","r",stdin);
	freopen("2667.out","w",stdout);

	while (scanf("%lld",&n) && n)
	{
		ans=0ll;
		for (long long l=1,r=0;l<=n;l=r+1)
		{
			r=n/(n/l);
			ans+=(r+l)*(r-l+1)/2*(n/l);
		}
		printf("%lld\n",ans-1);
	}
	return 0;
}