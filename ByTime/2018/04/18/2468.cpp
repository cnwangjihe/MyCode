#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int INF  = 1000000009,
		  MAXN = 22,
		  MAXM = (1<<18)+9;

int n,m,ans,sum;
int dis[MAXN][MAXN];
int f[MAXN][MAXM],g[MAXN][MAXM];

int main()
{
	freopen("2468.in","r",stdin);
	freopen("2468.out","w",stdout);
	int a,b,v,tot;
	fill(f[0],f[0]+(MAXN*MAXM),INF);
	fill(dis[0],dis[0]+(MAXN*MAXM),INF);
	fill(g[0],g[0]+(MAXN*MAXM),INF);
	ans=INF;
	scanf("%d%d",&n,&m);

	sum=(n-2)/2;
	if (!sum)
		sum=n-2;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&v);
		dis[a][b]=dis[b][a]=min(dis[a][b],v);
	}
	for(int i=0;i<n;i++)	
		dis[i][i]=0;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

	if (n==3)
		return printf("%d\n",(dis[0][1]+dis[1][2])*2)&0;
	
	for(int i=1;i<n-1;i++)
	{
		f[i][0]=g[i][0]=0;
		f[i][1<<(i-1)]=dis[0][i];
		g[i][1<<(i-1)]=dis[i][n-1];
	}

	for(int k=0;k<(1<<(n-2));k++)
		for(int i=1;i<n-1;i++)
			if (k&(1<<(i-1)))
				for(int j=1;j<n-1;j++)
					f[j][k|(1<<(j-1))]=min(f[j][k|(1<<(j-1))],f[i][k]+dis[i][j]),
					g[j][k|(1<<(j-1))]=min(g[j][k|(1<<(j-1))],g[i][k]+dis[j][i]);
	

	for(int k=0;k<(1<<(n-2));k++)
	{
		tot=0;
		for(int i=1;i<n-1;i++)
			if (k&(1<<(i-1)))
				++tot;
		if (tot!=sum)
			continue;
		
		tot=INF;
		for(int i=1;i<n-1;i++)
			if (k&(1<<(i-1)))
			{
				int s=k^((1<<(n-2))-1);
				if (!s)
					ans=min(ans,f[i][k]+g[i][k]);
				for(int j=1;j<n-1;j++)
					tot=min(tot,f[i][k]+dis[i][j]+g[j][s]);
			}
		for(int i=1;i<n-1;i++)
			if (k&(1<<(i-1)))
			{
				int s=k^((1<<(n-2))-1);
				for(int j=1;j<n-1;j++)
					ans=min(ans,g[i][k]+dis[j][i]+f[j][s]+tot);
			}
	}
	printf("%d\n",ans);
	return 0; 
}