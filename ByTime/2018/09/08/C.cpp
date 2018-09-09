#include <bits/stdc++.h>

using namespace std;

const int MAXN = 49;
const long long MOD = 1000000007;

long long ans=1,k=0;
int a[MAXN];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
		ans=ans*i%MOD;
	for (int i=1;i<n-1;i++)
		ans=ans*n%MOD;
//	cerr << ans << endl;
	for (int i=1,p=1;i<=n*(n-1)/2;i++,k--)
	{
		if (i==a[p])
			k+=p++;
		else
			ans=ans*k%MOD;
//		cerr << k-1 << endl;
	}
	printf("%lld\n",ans);
	return 0;
}