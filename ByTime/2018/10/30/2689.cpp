#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[MAXN];
int n,q;
long long ans;

int main()
{
	freopen("2689.in","r",stdin);
	freopen("2689.out","w",stdout);
	char opt[10];
	int x,y;
	while (scanf("%d%d",&n,&q)==2 && (n || q))
	{
		memset(a,0,sizeof a);
		for (int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		for (int i=0;i<q;i++)
		{
			scanf("%s%d%d",opt,&x,&y);
		//	cerr << opt << endl;
			if (opt[0]=='a')
			{
				for (int j=x;j<=y;j++)
					a[j]++;
			}
			else
			{
				ans=0;
				for (int j=x;j<=y;j++)
					ans+=a[j]/b[j];
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}