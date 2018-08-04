#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15;

int g[MAXN][MAXN];
int a[MAXN],t[MAXN];
int pre[MAXN],nxt[MAXN];
int ans,sum,c,n;

int main()
{
	freopen("2573.in","r",stdin);
	freopen("2573.out","w",stdout);
	for (int i=1;i<=10;i++)
		for (int j=i+1;j<=10;j++)
			g[i][j]=g[j][i]=__gcd(i,j);
	while (scanf("%d",&n)==1 && n!=0)
	{
		ans=1000*1000;
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]),t[i]=i;
		c=1;
		for (int i=2;i<=n;i++)
			c*=i;
		for (int i=0;i<c;i++)
		{
			for (int i=2;i<n;i++)
				nxt[i]=i+1,pre[i]=i-1;
			nxt[1]=2,nxt[n]=1;
			pre[1]=n,pre[n]=n-1;
			sum=0;
			for (int i=1;i<=n-2;i++)
			{
				sum+=g[a[t[nxt[i]]]][a[t[pre[i]]]];
				pre[nxt[i]]=pre[i];
				nxt[pre[i]]=nxt[i];
			}
			ans=min(ans,sum+g[a[t[n-1]]][a[t[n]]]);
			next_permutation(t+1,t+n+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}