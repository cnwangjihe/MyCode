#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 22,
		  MAXM = (1<<20)+9,
		  INF  = 100000009;

int n,s,m;
int g[MAXM],f[MAXM];
int a[MAXN];

int main()
{
	freopen("bag.in","r",stdin);
	freopen("bag.out","w",stdout);
	scanf("%d%d",&n,&s);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	fill(f,f+MAXM,INF);
	memset(g,0,sizeof g);
	m=(1<<n)-1;
	int k;
	f[0]=0;
	for (int i=0;i<m;i++)
		for (int j=1;j<=n;j++)
		{
			k=i|(1<<(j-1));
			if (i&(1<<(j-1)))
				continue;
			if (g[i]>=a[j] && f[i]<=f[k])
			{
				if (f[i]==f[k])
					g[k]=max(g[k],g[i]-a[j]);
				else
					g[k]=g[i]-a[j],f[k]=f[i];
			}
			if (g[i]<a[j] && f[i]<f[k])
			{
				if (f[i]+1==f[k])
					g[k]=max(g[k],s-a[j]);
				else
					g[k]=s-a[j],f[k]=f[i]+1;
			}
		}
	printf("%d\n",f[m]);
    return 0;
}

