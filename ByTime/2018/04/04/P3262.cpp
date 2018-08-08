#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 12,
		  MAXM = (1<<MAXN);

int w[MAXM][MAXM],f[MAXM][MAXM];
int n,m,p,m0,ans;
int g[MAXM][MAXM];

void dp(int x,int h,int sta)
{
	if (h==n)
	{
		g[x][0]=g[x][1]=0;
		for (int i=h-1,y=x>>1;i>=1;i--,y>>=1)
		{
			g[x][1]+=((sta>>i-1)&1)*w[y][x];
			g[x][0]+=(((sta>>i-1)&1)^1)*f[y][x];
		}
		return;
	}
	dp(x<<1,h+1,sta),dp(x<<1|1,h+1,sta);
	int size=1<<n+1-h;
	for (int i=0;i<=size;i++)
	{
		g[x][i]=0;
		for (int j=0;j<=i;j++)
			g[x][i]=max(g[x][i],g[x<<1][j]+g[x<<1|1][i-j]);
	}
	sta|=1<<h-1;
	dp(x<<1,h+1,sta),dp(x<<1|1,h+1,sta);
	for (int i=0;i<=size;i++)
		for (int j=0;j<=i;j++)
			g[x][i]=max(g[x][i],g[x<<1][j]+g[x<<1|1][i-j]);
}

int main()
{
	scanf("%d%d",&n,&m);
	p=1<<n+1,m0=1<<n-1;
	for (int i=1;i<=m0;i++)
		for (int x=(i+m0-1)/2;x;x>>=1)
			scanf("%d",&w[x][i+m0-1]);
	for (int i=1;i<=m0;i++)
		for (int x=(i+m0-1)/2;x;x>>=1)
			scanf("%d",&f[x][i+m0-1]); 
	dp(1,1,0);
	ans=0;
	for (int i=0;i<=m;i++)
		ans=max(ans,g[1][i]);
	printf("%d\n",ans);
	return 0;
}