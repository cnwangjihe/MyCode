#include <bits/stdc++.h>

using namespace std;

const int MAXN = 109,
		  INF = 100000009;

int f[MAXN][MAXN],g[1009][1009];
int a[MAXN];
int n;

int main()
{
	freopen("2573.in","r",stdin);
	freopen("2573.out","w",stdout);
	for (int i=1;i<=1000;i++)
		for (int j=i;j<=1000;j++)
			g[i][j]=g[j][i]=__gcd(i,j);
	while(scanf("%d",&n)==1 && n)
	{
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		if (n==2)
		{
			printf("%d\n",g[a[0]][a[1]]);
			continue;
		}
		memset(f,0,sizeof f);
		for (int l=1;l<n-1;l++)
			for (int i=0;i<n;i++)
			{
				int j=i+l-1;
				for (int k=i;k<=j;k++)
					if (!f[i][j%n])
						f[i][j%n]=f[i][(k+n-1)%n]+f[(k+1)%n][j%n]+g[a[(i+n-1)%n]][a[(j+1)%n]];
					else
						f[i][j%n]=min(f[i][j%n],f[i][(k+n-1)%n]+f[(k+1)%n][j%n]+g[a[(i+n-1)%n]][a[(j+1)%n]]);
			}
		int ans=INF;
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				ans=min(ans,f[(i+1)%n][(j+n-1)%n]+f[(j+1)%n][(i+n-1)%n]+g[a[i]][a[j]]);
		printf("%d\n",ans);
	}
	return 0;
}