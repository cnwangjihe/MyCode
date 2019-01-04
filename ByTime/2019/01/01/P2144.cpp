// Date      : 2019-01-01 20:06:42
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P2144
// Algorithm : Matric-Tree
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 109;
const double eps = 1e-9;

double DTMGauss(double a[MAXN][MAXN],int n)
{
	int id,cnt=0;
	double ans=1;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (fabs(a[j][i])-fabs(a[id][i])>eps)
				id=j;
		if (i!=id)
		{
			cnt++;
			for (int j=1;j<=n;j++)
				swap(a[id][j],a[i][j]);
		}
		if (fabs(a[i][i])<eps)
			return 0;
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			for (int k=n;k>=i;k--)
				a[j][k]-=a[i][k]*a[j][i]/a[i][i];
		}
	}
	for (int i=1;i<=n;i++)
		ans*=a[i][i];
	return (cnt&1?-ans:ans);
}

int n;
double a[MAXN][MAXN];

int main()
{
//	freopen("P2144.in","r",stdin);
//	freopen("P2144.out","w",stdout);
	for (int n=2;n<=20;n++)
	{
		memset(a,0,sizeof a);
		for (int i=1;i<=n;i++) 
		{
			if (i==n)
			{
				a[i][1]=-1;
				a[1][i]=-1;
			}
			else
			{
				a[i][i+1]=-1;
				a[i+1][i]=-1;
			}
			a[i][i]=3;
			a[i][n+1]=-1;
			a[n+1][i]=-1;
		}
		a[n+1][n+1]=n;
		printf("%.0lf\n",DTMGauss(a,n));
	}
	return 0;
}