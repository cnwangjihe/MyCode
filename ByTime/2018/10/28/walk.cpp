#include <bits/stdc++.h>

using namespace std;

const int MAXN = 22;

map<pair<int,int>,int> mp;
long long ans=0;
int a[MAXN][MAXN];
int n,m,k,lim;

void dfs1(int x,int y,int step,int cnt,int sum)
{
	sum^=a[x][y];
	if (step==lim)
	{
	//	cerr << x << y << step << ' ' << sum << '\n';
		mp[make_pair(cnt,sum)]++;
		return ;
	}
	if (x+1<=n)
		dfs1(x+1,y,step+1,cnt+0,sum);
	if (y+1<=m)
		dfs1(x,y+1,step+1,cnt+1,sum);
	return ;
}

void dfs2(int x,int y,int step,int cnt,int sum)
{
	if (step+lim==n-1+m-1)
	{
	//	cerr << x << y << step << ' ' << sum << '\n';
		ans+=1ll*mp[make_pair(m-1-cnt,k^sum)];
		return ;
	}
	sum^=a[x][y];
	if (x-1>0)
		dfs2(x-1,y,step+1,cnt+0,sum);
	if (y-1>0)
		dfs2(x,y-1,step+1,cnt+1,sum);
	return ;
}
int main()
{
//	int start = clock(), end;
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	lim=(n-1+m-1)/2;
	dfs1(1,1,0,0,0);
//	cerr << '\n';
	dfs2(n,m,0,0,0);
	printf("%lld\n",ans);
//	end = clock();
//	cerr << (end - start) / (CLOCKS_PER_SEC / 1000); 
	return 0;
}