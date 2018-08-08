#include <bits/stdc++.h>

using namespace std;

const int MAXN = 12,
		  INF  = 109*1009;

int a[MAXN];
bool vis[MAXN];
int g[MAXN][MAXN];
int tmp[11][MAXN];
int ans;
int n;

void dfs(int k,int cost)
{
	int cnt=0;
	for (int i=1;i<=n;i++)
		if (!vis[i])
			tmp[k][cnt++]=i;
//	cerr << cnt << endl;
	if (k==n-2)
	{
		ans=min(ans,cost+g[a[tmp[k][0]]][a[tmp[k][1]]]);
		return ;
	}
	for (int i=0;i<cnt;i++)
	{
		vis[tmp[k][i]]=1;
		dfs(k+1,cost+g[a[tmp[k][(i+cnt-1)%cnt]]][a[tmp[k][(i+1)%cnt]]]);
		vis[tmp[k][i]]=0;
	}
	return ;
}

int main()
{
	freopen("2573.in","r",stdin);
	freopen("2573.out","w",stdout);
	for (int i=1;i<=10;i++)
		for (int j=i+1;j<=10;j++)
			g[i][j]=g[j][i]=__gcd(i,j);
//	cerr << g[3][5] << g[2][5];
	while (scanf("%d",&n)==1 && n!=0)
	{
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		ans=INF;
		dfs(0,0);
		printf("%d\n",ans);
	}
	return 0;
}