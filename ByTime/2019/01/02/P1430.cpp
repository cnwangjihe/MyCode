// Date      : 2019-01-02 08:41:49
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P1430
// Algorithm : DP
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1009;

int a[MAXN];
long long f[MAXN][MAXN],g[2][MAXN][MAXN];
long long sum[MAXN];
int n;

int main()
{
//	freopen("P1430.in","r",stdin);
//	freopen("P1430.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			g[0][i][i]=g[1][i][i]=f[i][i]=a[i];
			sum[i]=sum[i-1]+a[i];
		}
		for (int i=1;i<n;i++)
		{
			for (int j=1;j+i<=n;j++)
			{
				f[j][j+i]=sum[j+i]-sum[j-1]-min(0ll,min(g[0][j+1][j+i],g[1][j][j+i-1]));
				g[0][j][j+i]=min(f[j][j+i],g[0][j+1][j+i]);
				g[1][j][j+i]=min(f[j][j+i],g[1][j][j+i-1]);
			}
		}
		printf("%lld\n",f[1][n]);
	}
	return 0;
}