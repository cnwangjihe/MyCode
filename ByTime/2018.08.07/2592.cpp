#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

long long a[MAXN];
long long sum,t;
int ans,n;

int main()
{
	freopen("2592.in","r",stdin);
	freopen("2592.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		ans=0;
		scanf("%d",&n);
		for (int i=0;i<n;i++)
			scanf("%lld",&a[i]);
		for (int i=1;i<(1<<n);i++)
		{
			sum=1;
			for (int j=0;j<n;j++)
				if (i&(1<<j))
				{
					t=__gcd(sum,a[j]);
					sum=sum/t*a[j]/t;
				}
		//	cerr << sum << ' ' << i << endl;
			t=sqrt(sum);
			if (sum==t*t)
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}