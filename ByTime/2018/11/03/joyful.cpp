#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16,
		  MAXK = 109,
		  MAXS = (1<<MAXN);

double f[2][MAXS];
bool vis[2][MAXS];
int need[MAXN];
int c[MAXN];
int k,n,cnt;
double ans=0;

int main()
{
	int v,w;
	scanf("%d%d",&k,&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&c[i]);
		while (scanf("%d",&v)==1 && v)
			need[i]|=(1<<(v-1));
	}
	cnt=(1<<n);
	f[0][0]=0;
	vis[0][0]=1;
	for (int i=1;i<=k;i++)
	{
		w=(i&1);
		for (int j=0;j<cnt;j++)
			f[w][j]=0,vis[w][j]=0;
		for (int j=0;j<cnt;j++)
		{
			if (!vis[w^1][j])
				continue;
			for (int t=0;t<n;t++)
			{
				vis[w][j]=1;
				f[w][j]=max(f[w][j],1.0*(f[w^1][j])/n);
				if ((j&need[t])^need[t])
					continue;
				vis[w][j|(1<<t)]=1;
				f[w][j|(1<<t)]=max(f[w][j|(1<<t)],1.0*(f[w^1][j]+c[t])/n);
			}
		}
	}
	for (int i=0;i<cnt;i++)
		ans+=f[k&1][i];
	printf("%.6f\n",ans);
	return 0;
}