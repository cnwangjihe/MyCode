#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 1009,
		  INF  = 0x7fffffff;
const double eps = 1e-7;

int vis[MAXN],x[MAXN],y[MAXN],z[MAXN],pre[MAXN];
double dis[MAXN],cost[MAXN][MAXN],dist[MAXN][MAXN];
int n;

double _check(double x)
{
	double sum = 0.0;
	for (int i=1;i<=n;i++)
		pre[i]=1;
	dis[1]=0;
	memset(vis,0,sizeof vis);
	vis[1]=1;
	for (int i=2;i<=n;i++)
		dis[i] = cost[1][i] - dist[1][i] * x;
	int k;
	for (int i=2;i<=n;i++)
	{
		double minCost=INF;
		for (int j=2;j<=n;j++)
			if (!vis[j] && dis[j]<minCost)
				minCost = dis[j],k=j;
		vis[k]=1;
		sum+=minCost;
		for (int j = 1; j <= n; j++)
			if (!vis[j] && dis[j] > cost[k][j] - dist[k][j] * x)
				dis[j] = cost[k][j] - dist[k][j] * x,pre[j] = k;
	}
	return sum;
}
int main()
{
	double tmp;
	while (scanf("%d",&n) && n)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d%d",&x[i],&y[i],&z[i]);
			for (int j = 1; j < i; j++)
			{
				tmp = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
				cost[i][j] = cost[j][i] = abs(z[i] - z[j]);
				dist[i][j] = dist[j][i] = sqrt(tmp);
			}
		}
		double l=0,r=100000.0,mid;
		while (l+eps<r)
		{
			mid=(l+r)/2;
			if (_check(mid) < eps)
				r=mid;
			else
				l=mid;
		}
		printf("%.3f\n",r);
	}
	return 0;
}