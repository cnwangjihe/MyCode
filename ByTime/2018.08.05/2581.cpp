#include<bits/stdc++.h>

using namespace std;

long long n,l,r;

int main()
{
	freopen("2581.in", "r", stdin);
	freopen("2581.out","w",stdout);
	scanf("%lld",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",(r-l+1)*(r-l)/2);
	}
	return 0;
}