#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 53,
		  MAXM = (1<<7)+9,
		  INF = 0x7fffffff;

int ans1=INF,ans2=INF;
int f[MAXN][MAXM][MAXM],g[MAXN][MAXM][MAXM];
int n,m;
int v[MAXN][MAXN];

int main()
{
	int now,sum,cnt;
	memset(f,0x7f,sizeof f);
	memset(g,0x3f,sizeof g);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&v[i][j]);
	for (int i=0;i<(1<<m);i++)
	{
		now=0;
		f[1][0][i]=g[1][0][i]=0;
		for(int k=1;now<i;k++)
		{
			if((1<<(k-1))&i)
			{
				now|=(1<<(k-1));
				f[1][0][i]+=v[1][k];
				g[1][0][i]++;
			}
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=0;j<(1<<m);j++)
			for (int k=0;k<(1<<m);k++)
				for (int l=0;l<(1<<m);l++)
				{
					now=0,sum=0,cnt=0;
					for (int t=1;now<l;t++)
					{
						if((1<<(t-1))&l)
						{
							cnt++;
							now|=(1<<(t-1));
							sum+=v[i+1][t];
						}
					}
					if(((l|j|k|(k>>1)|(k<<1))&((1<<m)-1))==((1<<m)-1))
						if((f[i+1][k][l]>f[i][j][k]+sum)||(f[i][j][k]+sum==f[i+1][k][l]&&g[i+1][k][l]>g[i][j][k]+cnt))
							f[i+1][k][l]=f[i][j][k]+sum,g[i+1][k][l]=g[i][j][k]+cnt;
				}
	for(int i=0;i<(1<<m);i++)
		if(ans1>f[n+1][i][0] || (ans1==f[n+1][i][0] && ans2>g[n+1][i][0]) )
			ans1=f[n+1][i][0],ans2=g[n+1][i][0];
	printf("%d %d\n",ans2,ans1);
	return 0;
}