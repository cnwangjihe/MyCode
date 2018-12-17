// Date    : 2018-12-17 11:34:56
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 230,
		  MAXR = 150;

int n,r;
double ans;
double f[MAXN][MAXR],q[MAXN][MAXR],g[MAXN];
double p[MAXN];
int d[MAXN];

template <typename T> inline T qpow(T a,int k)
{
	T ans=1;
	for (int i=0;(1<<i)<=k;i++,a*=a)
		if ((1<<i)&k)
			ans=ans*a;
	return ans;
}

int main()
{
//	freopen("P3239.in","r",stdin);
//	freopen("P3239.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		memset(f,0,sizeof f);
		ans=0;
		scanf("%d%d",&n,&r);
		for (int i=1;i<=n;i++)
			scanf("%lf%d",&p[i],&d[i]);
		for (int i=1;i<=n;i++)
		{
			q[i][0]=1;
			for (int j=1;j<=r;j++)
				q[i][j]=q[i][j-1]*(1-p[i]);
		}
		f[0][0]=1;
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<i;j++)
			{
				f[i][j]+=f[i-1][j]*q[i][r-j];
				f[i][j+1]+=f[i-1][j]*(1-q[i][r-j]);
			}
		}
		for (int i=1;i<=n;i++)
		{
			g[i]=0;
			for (int j=0;j<i;j++)
				g[i]+=f[i-1][j]*(1-q[i][r-j]);
			ans+=g[i]*d[i];
		}
		printf("%.10f\n",ans);
	}
	return 0;
}