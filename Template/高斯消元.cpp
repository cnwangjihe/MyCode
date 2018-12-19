// Date    : 2018-12-18 18:56:57
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 109;
const double eps = 1e-9;

double a[MAXN][MAXN];
int n;

bool Gauss(double a[MAXN][MAXN],int n)
{
	int id;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (abs(a[j][i])-abs(a[id][i])>eps)
				id=j;
		if (id!=i)
			for (int j=1;j<=n+1;j++)
				swap(a[i][j],a[id][j]);
		if (abs(a[i][i])<eps)
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
//	freopen("P3389.in","r",stdin);
//	freopen("P3389.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++)
			scanf("%lf",&a[i][j]);
	if (!Gauss(a,n))
		return printf("No Solution\n"),0;
/*	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			cerr << a[i][j] << ' ';
		cerr << '\n';
	}*/
	for (int i=1;i<=n;i++)
		printf("%.2lf\n",a[i][n+1]);
	return 0;
}