// Date      : 2018-12-26 19:22:08
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#pragma GCC optimize(3)

#include <bits/stdc++.h>

using std::max;
using std::min;
using std::swap;
using std::cerr;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int dx[4] = {-1,0,1,0},
		  dy[4] = {0,1,0,-1};
const int MAXN = 109,
		  MAXK = 20000;

long long a[MAXN][MAXN];
long long f[2][MAXN][MAXN];
int n,m,x,y,k;
long long ans=-INF;

void force(int k)
{
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=m+1;j++)
			f[0][i][j]=-INF;
	f[0][x][y]=0;
	int p;
	for (int d=1;d<=k;d++)
	{
		p=(d&1);
		for (int i=0;i<=n+1;i++)
			for (int j=0;j<=m+1;j++)
				f[p][i][j]=-INF;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				for (int t=0;t<4;t++)
					f[p][i][j]=max(f[p][i][j],f[p^1][i+dx[t]][j+dy[t]]+a[i][j]);
	}
	return ;
}

int main()
{
	freopen("2738.in","r",stdin);
	freopen("2738.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	if (k<=20000)
	{
		force(k);
		return printf("%lld\n",f[0][x][y]),0;
	}
	force(10000);
	long long v;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (f[0][i][j]<0)
				continue;
			v=max(a[i-1][j],max(a[i+1][j],max(a[i][j-1],a[i][j+1])))+a[i][j];
			ans=max(ans,f[0][i][j]*2+a[x][y]-a[i][j]+v*(k-20000)/2);
		}
	printf("%lld\n",ans);
	return 0;
}