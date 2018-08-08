#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009;

long long a[MAXN],b[MAXN];
int n,q;
long long ans;

int main()
{
	freopen("2586.in","r",stdin);
	freopen("2586.out","w",stdout);
	int t,x,y,z;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[i]=a[i];
	for (int i=0;i<q;i++)
	{
		scanf("%d",&t);
		if (t==1)
		{
			ans=0;
			scanf("%d%d",&x,&y);
			for (int j=x;j<=y;j++)
				ans+=a[j];
			printf("%lld\n",ans);
		}
		if (t==2)
		{
			scanf("%d%d%d",&x,&y,&z);
			for (int j=x;j<=y;j++)
				a[j]=a[j-z];
		}
		if (t==3)
		{
			scanf("%d%d",&x,&y);
			for (int j=x;j<=y;j++)
				a[j]=b[j];
		}
	}
	return 0;
}