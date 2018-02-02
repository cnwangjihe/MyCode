#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int INF = 1000000007,
		  MAXN= 22;
const int fx[4]={0,1,0,-1},
		  fy[4]={1,0,-1,0};

int n,m,k,ans,rrr;

int mp[MAXN][MAXN],a[MAXN][MAXN],c[5][MAXN];
bool use[MAXN][MAXN];

bool ok(int x,int y) {return (x>=1 && x<=n && y>=1 && y<=m && (mp[x][y]!=-1));}

void dfs(int x,int y,int used,int s,int sum)
{
	if (sum>=k)
		ans=min(ans,s);
	int p;
	for (int i=0;i<4;i++)
	{
		int nx=x+fx[i],ny=y+fy[i];
		if (ok(nx,ny) && (!use[nx][ny]))
		{
			p=((used&(1<<mp[nx][ny]))==0);
			use[nx][ny]=1;
			dfs(nx,ny,used|(1<<mp[nx][ny]),s+a[nx][ny],sum+p);
			use[nx][ny]=0;
		}
	}
	return ;
}

/*
void _check()
{
	cerr << ans << endl;
}
*/

void update()
{
	int sum=0,used=0,cnt=0;
	for (int i=1;i<m;i++)
	{
		if (c[1][i] || c[1][i+1])
			continue;
		for (int j=i+2;j<=m;j++)
		{
			if (!c[1][j]) continue;
			for (int k=i;k<=j;k++)
				c[2][k]=1;
			break;
		}
	}
	for (int j=1;j<=2;j++)
		for (int i=1;i<=m;i++)
		{
			if (c[j][i])
			{
				if (!(~mp[j][i]))
					return;
				sum+=a[j][i];
				
				cnt+=(((1<<mp[j][i])&used)==0);
				used|=(1<<mp[j][i]);
			}
		}
	if (cnt>=k)
		ans=min(ans,sum);
	return ;
}

void solve()
{
	int used=(1<<(m+1))-1;
	for (int i=1;i<=used;i++)
	{
		for (int j=i;j;j=i&(j-1))
		{
			for (int k=1;k<=m;k++)
				c[1][k]=c[2][k]=0;
			for (int k=0;k<m;k++)
					c[1][k+1]=(((1<<k)&i)!=0),
					c[2][k+1]=(((1<<k)&j)!=0);
			update();
		//	_check();
		}
	}
}

int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&mp[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	
	ans = INF;
	if (n<=4 && m<=4 && k<=4)
	{
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (mp[i][j]==-1)
					continue;
				use[i][j]=1;
				dfs(i,j,1<<mp[i][j],a[i][j],1);
				use[i][j]=0;
			}
	}
	else
	if (n==2 && m<=15)
	{
		solve();
		for (int i=1;i<=m;i++)
			swap(mp[1][i],mp[2][i]),swap(a[1][i],a[2][i]);
		solve();
	}
	else
	if (n==1 && m<=15)
	{
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (mp[i][j]==-1)
					continue;
				use[i][j]=1;
				dfs(i,j,1<<mp[i][j],a[i][j],1);
				use[i][j]=0;
			}
	}
	printf("%d\n",ans);
	return 0;
}
