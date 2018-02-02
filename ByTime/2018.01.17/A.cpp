#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 309;

int f[MAXN],g[MAXN][MAXN];
int a[MAXN],d[MAXN];
bool c[MAXN][MAXN];
int n,m;

int solve()
{
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	for (int k=2;k<=n;k++)
	{
		for (int i=1;i<=n-k+1;i++)
		{
			int j=i+k-1;
			if (k==2 && c[i][i+1])
				g[i][j]=1;
			else
				if (k==3 && c[i][i+1] && a[i+1]*2-a[i]==a[i+2])
					g[i][j]=1;
				else
				{
					if (c[i][j] && g[i+1][j-1])
						g[i][j]=1;
					for (int p=i+1;p<j;p++)
						g[i][j]|=(g[i][p]&g[p+1][j]);
				}
		}
	}
	for (int j=1;j<=n;j++)
	{
		f[j]=f[j-1];
		for (int i=1;i<=j;i++)
			if (g[i][j])
				f[j]=max(f[j],f[i-1]+j-i+1);
	}
	return f[n];
}

int main()
{
	int ttt;
	scanf("%d",&ttt);
	while (ttt--)
	{
		memset(c,0,sizeof c);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=1;i<=m;i++)
			scanf("%d",&d[i]);
		for (int i=1;i<n;i++)
			for (int j=i+1;j<=n;j++)
				for (int k=1;k<=m && (!c[i][j]);k++)
					if (a[j]-a[i]==d[k])
						c[i][j]=1;
		printf("%d\n",solve());
	}
}

