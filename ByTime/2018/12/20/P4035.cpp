// Date    : 2018-12-20 14:24:25
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 13;
const double eps=1e-9;

double a[MAXN][MAXN],f[MAXN][MAXN];
int n;

bool Gauss(double a[MAXN][MAXN],int n)
{
	int id;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (fabs(a[j][i])-fabs(a[id][i])>eps)
				id=j;
		if (id!=i)
			for (int j=1;j<=n+1;j++)
				std::swap(a[i][j],a[id][j]);
		if (fabs(a[i][i])<eps)
			return 0;
		for (int j=1;j<=n;j++)
		{
			if (i==j)
				continue;
			for (int k=n+1;k>=i;k--)
				a[j][k]-=a[i][k]*a[j][i]/a[i][i];
		}
	}
	for (int i=1;i<=n;i++)
		a[i][n+1]/=a[i][i];
	return 1;
}

int main()
{
//	freopen("P4035.in","r",stdin);
//	freopen("P4035.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n;j++)
			scanf("%lf",&a[i][j]);
	for (int i=2;i<=n+1;i++)
		for (int j=1;j<=n;j++)
		{
			f[i-1][j]=2*(a[i][j]-a[i-1][j]);
			f[i-1][n+1]+=(a[i][j]*a[i][j]-a[i-1][j]*a[i-1][j]);
		}
	Gauss(f,n);
	for (int i=1;i<=n;i++)
		printf("%.3lf ",f[i][n+1]);
	return 0;
}