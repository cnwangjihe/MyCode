#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30;

bool flag=0;
int n,m,Max,ans,sum;
int v[MAXN],d[MAXN],w[MAXN];

int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	for (int i=0;i<(1<<n);i++)
	{
		sum=0,ans=0,flag=1;
		for (int j=1;j<=n;j++)
			if (i&(1<<(j-1)))
			{
				sum+=w[j];
				ans+=v[j];
				if ((d[j]!=0 && !(i&(1<<(d[j]-1)))) || sum>m)
				{
					flag=0;
					break;
				}
			}
		if (flag)
			Max=max(Max,ans);
	}
	printf("%d\n",Max);
}