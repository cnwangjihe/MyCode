#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 110;

int n,m,c;
int L[MAXN],R[MAXN],len[MAXN];
double f[MAXN][MAXN],g[MAXN][MAXN];

int main()
{
	freopen("2467.in","r",stdin);
	freopen("2467.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&c);
	for (int i=1;i<=c;i++)
		scanf("%d%d",&L[i],&R[i]),len[i]=R[i]-L[i]+1;
	for (int i=1;i<=n;i++)
		f[i][1]=1.0;
	
	for (int t=1;t<=c;t++)
	{
		for (int i=L[t];i<=R[t];i++)
		{
			for (int lc=0;lc<m;lc++)
			{
				double tmp=0.5;
				g[i][lc]+=f[i][lc]*(1.0-tmp);
				for (int nc=0;nc<m;nc++)
					g[i][lc*nc%m]+=f[i][lc]*tmp/double(m);
			}
			for (int lc=0;lc<m;lc++)
				f[i][lc]=g[i][lc],g[i][lc]=0.0;
		}
	}
	
	double ans=0.0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<m;j++)
			ans+=f[i][j]*double(j);
	printf("%.3lf\n",ans);
	return 0;
}