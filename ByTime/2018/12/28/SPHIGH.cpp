// Date      : 2018-12-28 10:40:02
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.spoj.com/problems/HIGH/
// Algorithm : Matrix-Tree
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 20;
const double eps = 1e-8;

double a[MAXN][MAXN];
bool mp[MAXN][MAXN];
int n,m;

double DTMGauss(double (*a)[MAXN],int n)
{
	double ans=1;
	int id,cnt=0;
	for (int i=1;i<=n;i++)
	{
		id=i;
		for (int j=i+1;j<=n;j++)
			if (fabs(a[j][i])-fabs(a[id][i])>eps)
				id=j;
		if (id!=i)
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
		ans=ans*a[i][i];
	return ans*((cnt&1)?-1:1);
}

int main()
{
//	freopen("SPHIGH.in","r",stdin);
//	freopen("SPHIGH.out","w",stdout);
	int T;
	scanf("%d",&T);
	int x,y;
	for (int cn=1;cn<=T;cn++)
	{
		memset(a,0,sizeof a);
		scanf("%d%d",&n,&m);
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			if (x==y)
				continue;
			a[x][x]++,a[y][y]++;
			a[x][y]--,a[y][x]--;
		}
		printf("%.0lf\n",DTMGauss(a,n-1));
	}
	return 0;
}