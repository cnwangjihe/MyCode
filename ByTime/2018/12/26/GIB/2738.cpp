// Date      : 2018-12-26 19:22:08
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::max;
using std::min;
using std::swap;
using std::cerr;

const long long INF = 2000000000000000000ll;
const int dx[4] = {-1,0,1,0},
		  dy[4] = {0,1,0,-1};
const int MAXN = 109,
		  MAXK = 1000000000;

long long f[MAXN][MAXN],a[MAXN][MAXN],g[MAXN][MAXN];
int n,m,x,y,k;
long long ans=-INF;

int main()
{
	freopen("2738.in","r",stdin);
	freopen("2738.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=m+1;j++)
			f[i][j]=-INF;
	f[x][y]=0;
	for (int i=x-1;i;i--)
		f[i][y]=f[i+1][y]+a[i][y];
	for (int i=x+1;i<=n;i++)
		f[i][y]=f[i-1][y]+a[i][y];

	for (int i=y-1;i;i--)
		f[x][i]=f[x][i+1]+a[x][i];
	for (int i=y+1;i<=m;i++)
		f[x][i]=f[x][i-1]+a[x][i];

	for (int i=x-1;i;i--)
		for (int j=y-1;j;j--)
			f[i][j]=max(f[i+1][j],f[i][j+1])+a[i][j];
	for (int i=x+1;i<=n;i++)
		for (int j=y-1;j;j--)
			f[i][j]=max(f[i-1][j],f[i][j+1])+a[i][j];

	for (int i=x-1;i;i--)
		for (int j=y+1;j<=m;j++)
			f[i][j]=max(f[i+1][j],f[i][j-1])+a[i][j];
	for (int i=x+1;i<=n;i++)
		for (int j=y+1;j<=m;j++)
			f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];

	g[x][y]=0;
	for (int i=x-1;i;i--)
		g[i][y]=g[i+1][y]+a[i+1][y];
	for (int i=x+1;i<=n;i++)
		g[i][y]=g[i-1][y]+a[i-1][y];

	for (int i=y-1;i;i--)
		g[x][i]=g[x][i+1]+a[x][i+1];
	for (int i=y+1;i<=m;i++)
		g[x][i]=g[x][i-1]+a[x][i-1];

	for (int i=x-1;i;i--)
		for (int j=y-1;j;j--)
			g[i][j]=max(g[i+1][j]+a[i+1][j],g[i][j+1]+a[i][j+1]);
	for (int i=x+1;i<=n;i++)
		for (int j=y-1;j;j--)
			g[i][j]=max(g[i-1][j]+a[i-1][j],g[i][j+1]+a[i][j+1]);

	for (int i=x-1;i;i--)
		for (int j=y+1;j<=m;j++)
			g[i][j]=max(g[i+1][j]+a[i+1][j],g[i][j-1]+a[i][j-1]);
	for (int i=x+1;i<=n;i++)
		for (int j=y+1;j<=m;j++)
			g[i][j]=max(g[i-1][j]+a[i-1][j],g[i][j-1]+a[i][j-1]);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cerr << f[i][j] << ' ';
		cerr << '\n';
	}
	cerr << '\n';
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cerr << g[i][j] << ' ';
		cerr << '\n';
	}
	int step;
	long long v;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			v=-INF;
			for (int t=0;t<4;t++)
				v=max(v,a[i+dx[t]][j+dy[t]]);
			v+=a[i][j];
			step=abs(i-x)+abs(j-y);
			if (step*2>k)
				continue;
			ans=max(ans,f[i][j]+g[i][j]+v*(k-2*step)/2);
		}
	printf("%lld\n",ans);
	return 0;
}