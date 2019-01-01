// Date      : 2018-12-28 14:38:57
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 1009,
		  MAXC = 1009,
		  MOD  = 998244353;

long long f[MAXN][MAXC];
int n,m,c;

int main()
{
//	freopen("chocolate.in","r",stdin);
//	freopen("chocolate.out","w",stdout);
	scanf("%d%d%d",&n,&c,&m);
	f[0][0]=1;
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=c;j++)
		{
			cerr << f[i][j] <<' ';
			if (j)
				f[i+1][j-1]+=f[i][j]*j;
			if (j!=c)
				f[i+1][j+1]+=f[i][j]*(c-j);
		}
		cerr << '\n';
	}
	printf("%d\n",f[n][m]);
	return 0;
}