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

long long f[MAXK][MAXN][MAXN];
long long a[MAXN][MAXN];
int fx[MAXK][MAXN][MAXN],fy[MAXK][MAXN][MAXN];
int n,m,x,y,k;

int main()
{
//	freopen("2738.in","r",stdin);
//	freopen("2738_force.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&k);
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=m+1;j++)
			for (int d=0;d<=k;d++)
				f[d][i][j]=-INF;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	f[0][x][y]=0;
	for (int d=1;d<=k;d++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				for (int t=0;t<4;t++)
					if (f[d-1][i+dx[t]][j+dy[t]]+a[i][j]>f[d][i][j])
					{
						f[d][i][j]=f[d-1][i+dx[t]][j+dy[t]]+a[i][j];
						fx[d][i][j]=i+dx[t];
						fy[d][i][j]=j+dy[t];
					}
	printf("%lld\n",f[k][x][y]);
	int ttx,tty,tx=x,ty=y;
	for (int i=k;i;i--)
	{
		cerr << tx << ' ' << ty << ' ' << f[i][tx][ty] << '\n';
		ttx=fx[i][tx][ty],tty=fy[i][tx][ty];
		tx=ttx,ty=tty;
	}
	return 0;
}