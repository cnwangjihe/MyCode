// Date      : 2018-12-26 19:10:12
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
		  MAXK = 1002;

long long f[2][MAXN][MAXN];
long long a[MAXN][MAXN];
int n,m,x,y,k;

bool ok(int x,int y){return x>0 && x<=n && y>0 && y<=m;}

int main()
{
	freopen("2738.in","r",stdin);
	freopen("2738_force.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
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
					if (ok(i+dx[t],j+dy[t]))
						f[p][i][j]=max(f[p][i][j],f[p^1][i+dx[t]][j+dy[t]]+a[i][j]);

	}
	printf("%lld\n",f[k&1][x][y]);
	return 0;
}